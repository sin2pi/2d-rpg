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
#include "LuaBridge.h"

extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
    
}

int amb = 0.6;

vector<cNpc*>npc;
vector<cItem*>items;
SDL_Surface *screen;
SDL_Rect camera;

using namespace std;
using namespace luabridge;

int main(int argc,char* argv[])
{
    SDL_Event event;
    
    bool running = true;
    
    
    lua_State *L;
    
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    
    LuaPrompt prompt;
    
    window = SDL_CreateWindow("openworld", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_RESIZABLE);
    // Setup renderer
    
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Joystick *joystick;
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);
    
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    
    cPlayer player(400,100,48,72,3,3,0.2,"chrono.bmp",4);
    
    
    //RegisterCalls(L);
    
    cTile map1(30,30);
    map1.LoadMap("map.txt");
    map1.LoadSheet("sheet.bmp");
    
    vec2d l1 = {1.5,0};
    vec2d l2 = {0,1.5};
    vec2d pos = {320,240};
    
    ParticleEngine par(2000,l1,l2,pos);
    
    //lua_pushcclosure(3, std::bind(&cPlayer::setPos, &player, std::placeholders::_2), 0);

    //lua_setglobal(L, "blah");
    
    LoadNpcList(&npc,"npcl.txt");
    LoadItemList(&items,"iteml.txt");
    
    getGlobalNamespace (L)
     .beginNamespace ("test")
     .addVariable("camera",&camera)
     .beginClass <cPlayer> ("cPlayer")
        .addConstructor <void (*) (float,float,int,int,float,float,float)> ()
        .addFunction ("setPos", &cPlayer::setPos)
        .addFunction ("setVel", &cPlayer::setVel)
        .addFunction ("getPos", &cPlayer::getVel)
        .addData("xvel", &cPlayer::xVel,true)
     .endClass ()
     .beginClass <cNpc> ("cNpc")
        .addFunction ("setPos", &cNpc::setPos)
        .addFunction ("setVel", &cNpc::setSpeed)
        //.addFunction ("getPos", &cNpc::getVel)
        //.addData("xvel", &cNpc::xVel,true)
     .endClass ()
     .beginClass <cItem> ("cItem")
        .addFunction ("setPos", &cItem::setPos)
        .addFunction ("setVel", &cItem::setVel)
        //.addFunction ("getPos", &cNpc::getVel)
        //.addData("xvel", &cNpc::xVel,true)
     .endClass ()
    .endNamespace();
    
    push (L, &player); //Register player object
    lua_setglobal (L, "player");

    int t=1; //Register npcVector as npc+id
    for(int i=0;i<npc.size();i++){
        string n = "npc";
        n += to_string(t);
        const char*c = n.c_str();
        push(L,npc.at(i));
        lua_setglobal (L,c);
        t++;
    }
    
    t=1; //Register itemVector as item+id
    for(int i=0;i<items.size();i++){
        string n = "item";
        n += to_string(t);
        const char*c = n.c_str();
        push(L,items.at(i));
        lua_setglobal (L,c);
        t++;
    }
    
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
    
    Uint32 start;
    
    while(running)
    {
        start = SDL_GetTicks();
        SDL_RenderClear(renderer);
        player.Interact(npc);
        player.Interact(items);
        while(SDL_PollEvent(&event))
        {
            inv.HandleInput(event,player,items);
            player.HandleInput(event,items,&inv);
            prompt.HandleInput(event,L);
        }
        
        for(int i = 0;i<npc.size();i++)
        {
            //npc.at(i)->runPath();
            npc.at(i)->Interact(player);
            npc.at(i)->Interact(npc);
            
        }
        //npc.at(1)->runRandPath();
        player.Move();
        player.Interact(npc);
        camera = player.SetCamera(camera);
        map1.RenderLayer(0);
        for(int j = 0;j<items.size();j++)
        {
            items.at(j)->Interact(items);
            items.at(j)->Render();
        }
        for(int i = 0;i<npc.size();i++)
        {
            npc.at(i)->Render(camera);
        }
        player.Render(camera);
        int px,py;
        SDL_GetMouseState(&px,&py);
        par.SetPos(px,py);
        //par.Run();
        //par.Render();
        //map1.RenderLayer(ttiles,1);
        //map1.RenderLayer(ttiles,2);
        inv.Render();
        
        prompt.update(screen);
        
        SDL_RenderPresent(renderer);
        if (1000/60>SDL_GetTicks()-start)
        {
            SDL_Delay(1000/60-(SDL_GetTicks()-start));
        }
    }

    SDL_Quit();
    return 0;
}
