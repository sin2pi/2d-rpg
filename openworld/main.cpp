#include <SDL2/SDL.h>
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
SDL_Rect camera;
TTF_Font *font;

vector<cNpc*>npc;
vector<cItem*>items;

lua_State *L;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

using namespace std;

int main(int argc,char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    
    LuaPrompt prompt;
    prompt.PromptActive = true;
    
    window = SDL_CreateWindow
    ("openworld", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,
     SDL_WINDOW_RESIZABLE
     );
    
    // Setup renderer
    
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Joystick *joystick;
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);
    
    L = luaL_newstate();
    luaL_openlibs(L);
    //*static_cast<cPlayer**>(lua_getextraspace(L)) = &distance;
    RegisterCalls(L);
    
    cTile map1;
    map1.LoadMap("/Users/martindionisi/Desktop/openworld/openworld/map.txt");
    
    SDL_Surface *tiles[5];
    tiles[0] = SDL_LoadBMP("/Users/martindionisi/Desktop/openworld/openworld/tile1.bmp");
    tiles[1] = SDL_LoadBMP("/Users/martindionisi/Desktop/openworld/openworld/tile2.bmp");
    tiles[2] = SDL_LoadBMP("/Users/martindionisi/Desktop/openworld/openworld/tile3.bmp");
    tiles[3] = NULL;
    SDL_Texture *ttiles[5];
    ttiles[0] = SDL_CreateTextureFromSurface(renderer,tiles[0]);
    ttiles[1] = SDL_CreateTextureFromSurface(renderer,tiles[1]);
    ttiles[2] = SDL_CreateTextureFromSurface(renderer,tiles[2]);
    ttiles[3] = SDL_CreateTextureFromSurface(renderer,tiles[3]);
    
    vec2d l1 = {1.5,0};
    vec2d l2 = {0,1.5};
    vec2d pos = {320,240};
    
    ParticleEngine par(4000,l1,l2,pos);
    
    cPlayer player(0,100,20,40,2,2,2,"/Users/martindionisi/Desktop/openworld/openworld/mario.bmp",3);
    
    LoadNpcList(&npc,"/Users/martindionisi/Desktop/openworld/openworld/npcl.txt");
    LoadItemList(&items,"/Users/martindionisi/Desktop/openworld/openworld/iteml.txt");
    
    //items.at(5)->setVel(-5,0);
    npc.at(1)->setRandPath(npc.at(1)->getBox()->x, npc.at(1)->getBox()->y,200, 200, 5);
    
    printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    printf("The names of the joysticks are:\n");
    
    for(int i=0; i < SDL_NumJoysticks(); i++ )
    {
        //printf("    - %s\n", SDL_JoystickName(i));
    }
    printf("\n-*-*-*-*-*-*-*-*-*-");
    
    Inventory inv;
    
    int numFrames = 0;
    Uint32 start;
    Uint32 startTime = SDL_GetTicks();
    while(running)
    {
        start = SDL_GetTicks();
        SDL_RenderClear(renderer);
        player.Interact(npc);
        player.Interact(items);
        while(SDL_PollEvent(&event))
        {
            for(int i = 0;i< items.size();i++)
            {
                //items.at(i)->Interact(event,player,&inv);
            }
            inv.HandleInput(event,player,items);
            player.HandleInput(event,items,&inv);
            prompt.handle_input();
        }
        
        for(int i = 0;i<npc.size();i++)
        {
            //npc.at(i)->runPath();
            npc.at(i)->Interact(player);
            npc.at(i)->Interact(npc);
            
        }
        //npc.at(1)->runRandPath();
        player.Move();
        camera = player.SetCamera(camera);
        map1.RenderLayer(ttiles,0);
        for(int j = 0;j<items.size();j++)
        {
            items.at(j)->Interact(items);
            items.at(j)->Render();
        }
        for(int i = 0;i<npc.size();i++)
        {
            npc.at(i)->Render();
        }
        player.Render(camera);
        par.SetPos(player.getBox()->x-camera.x,player.getBox()->y-camera.y);
        //par.Run();
        //par.Render();
        map1.RenderLayer(ttiles,1);
        inv.Render();
        
        prompt.update(screen);
        
        numFrames++;
        //int fps = (numFrames/(float)(SDL_GetTicks() - startTime) )*1000;
        //cout << "fps: " << fps;
        //SDL_GL_SwapBuffers();
        
        SDL_RenderPresent(renderer);
        if (1000/60>SDL_GetTicks()-start)
        {
            SDL_Delay(1000/60-(SDL_GetTicks()-start));
        }
    }

    SDL_Quit();
    return 0;
}
