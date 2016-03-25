#include <SDL/SDL.h>
#include <iostream>
#include "Player.h"
#include "Tile.h"
#include "Item.h"
#include "Inventory.h"
#include "npc.h"
#include "listManager.h"
#include "ParticleEngine.h"
#include "luaCalls.h"
#include "SDL_ttf.h"
#include "LuaPrompt.h"

extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
    
}
SDL_Event event;

bool running = true;
SDL_Surface *screen,*background;
SDL_Surface *tiles[5];
SDL_Rect camera;
TTF_Font *font;

vector<cNpc*>npc;

lua_State *L;

using namespace std;

int main(int argc,char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    
    LuaPrompt prompt;
    prompt.PromptActive = true;
    screen = SDL_SetVideoMode(640,480,32,SDL_INIT_JOYSTICK|SDL_OPENGLBLIT);
    
    SDL_Joystick *joystick;
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);
    
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L,"setNpc",setNpc);
    
    cTile map1;
    map1.LoadMap("/Users/martindionisi/Desktop/openworld/openworld/map.txt");
    tiles[0] = SDL_LoadBMP("/Users/martindionisi/Desktop/openworld/openworld/tile1.bmp");
    tiles[1] = SDL_LoadBMP("/Users/martindionisi/Desktop/openworld/openworld/tile2.bmp");
    tiles[2] = SDL_LoadBMP("/Users/martindionisi/Desktop/openworld/openworld/tile3.bmp");
    tiles[3] = NULL;
    
    vec2d l1 = {1.5,0};
    vec2d l2 = {0,1.5};
    vec2d pos = {320,240};
    
    ParticleEngine par(4000,l1,l2,pos);
    
    cPlayer player(0,100,20,40,2,2,2,"/Users/martindionisi/Desktop/openworld/openworld/mario.bmp",3);
    
    LoadNpcList(&npc,"/Users/martindionisi/Desktop/openworld/openworld/npcl.txt");
    
    vector<cItem*>items;
    LoadItemList(&items,"/Users/martindionisi/Desktop/openworld/openworld/iteml.txt");

    
    printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    printf("The names of the joysticks are:\n");
    
    for(int i=0; i < SDL_NumJoysticks(); i++ )
    {
        printf("    - %s\n", SDL_JoystickName(i));
    }
    printf("\n-*-*-*-*-*-*-*-*-*-");
    
    Inventory inv;
    while(running)
    {
        
        player.Interact(npc);
        while(SDL_PollEvent(&event))
        {
            for(int i = 0;i< items.size();i++)
            {
                items.at(i)->Interact(event,player,&inv);
            }
            inv.HandleInput(event,player,items);
            player.HandleInput(event);
            prompt.handle_input();
        }
        
        for(int i = 0;i<npc.size();i++)
        {
            npc.at(i)->runPath();
            npc.at(i)->Interact(player);
            npc.at(i)->Interact(npc);
            
        }
        player.Move();
        camera = player.SetCamera(camera);
        map1.RenderLayer(tiles,0);
        for(int i = 0;i<npc.size();i++)
        {
            npc.at(i)->Render();
        }
        for(int j = 0;j<items.size();j++)
        {
            items.at(j)->Render();
        }
        player.Render(camera);
        par.SetPos(player.getBox()->x-camera.x,player.getBox()->y-camera.y);
        //par.Run();
        par.Render();
        map1.RenderLayer(tiles,1);
        inv.Render();
        
        prompt.update(screen);
        
        SDL_GL_SwapBuffers();
        SDL_Flip(screen);
    }

    SDL_Quit();
    return 0;
}
