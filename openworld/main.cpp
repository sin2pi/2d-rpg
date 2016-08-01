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
#include "light.h"

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
vec2d vcam;
vec2d mvec;

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
    
    light w(1500);
    
    cPlayer player(400,100,48,72,2.5,2.5,0.2,"chrono.bmp",4);
    
    RegisterCalls(L);
    
    cTile map1(30,30);
    map1.LoadMap("map.txt");
    map1.LoadSheet("sheet.bmp");
    
    vec2d dir = {0,-1};
    vec2d pos = {320,240};
    ParticleEngine par(5000,30,7,dir,pos);
    
    //lua_pushcclosure(3, std::bind(&cPlayer::setPos, &player, std::placeholders::_2), 0);

    //lua_setglobal(L, "blah");
    
    LoadNpcList(&npc,"npcl.txt");
    LoadItemList(&items,"iteml.txt");
    
    getGlobalNamespace (L)
     .beginNamespace ("test")
     .addVariable("camera",&camera)
     .beginClass<ParticleEngine>("parEngine")
        .addConstructor <void (*) (int,int,int,vec2d,vec2d)> ()
        .addFunction ("state", &ParticleEngine::changeState)
        .addFunction("run",&ParticleEngine::Run)
        .addFunction("setPos",&ParticleEngine::SetPos)
        .addFunction("render",&ParticleEngine::Render)
     .endClass()
    
     .beginClass <vec2d> ("vec2d")
        .addConstructor <void (*) (void)> ()
        .addData("x", &vec2d::x,true)
        .addData("y",&vec2d::y,true)
     .endClass ()
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
        .addFunction ("setRep", &cNpc::setRep)
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
    
    push (L, &player); //Register player objectt      lua_setglobal(L, "player");
    lua_setglobal(L, "pEngine");
    push (L, &vcam); //Register player object
    lua_setglobal(L, "camera");
    push(L,&mvec);
    lua_setglobal(L, "mouse");

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
    
    luaL_dofile(L,"openworld/set.lua");
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
        w.startLapse();
        start = SDL_GetTicks();
        SDL_RenderClear(renderer);
        player.Interact(npc);
        player.Interact(items);
        while(SDL_PollEvent(&event))
        {
            inv.HandleInput(event,player,items);
            player.HandleInput(event,items,&inv,running);
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
        vcam = {static_cast<float>(camera.x),static_cast<float>(camera.y)};
        map1.RenderLayer(0,w.getAmb(),w);
        for(int j = 0;j<items.size();j++)
        {
            items.at(j)->Interact(items);
            items.at(j)->Render(w);
        }
        for(int i = 0;i<npc.size();i++)
        {
            npc.at(i)->Render(camera,w);
        }
        player.Render(camera,w);
        
        int px,py;
        SDL_GetMouseState(&px,&py);
        float x = px;
        float y = py;
        mvec.x = px;
        mvec.y = py;
        /*
        
        
        float xp = player.getBox()->x-camera.x;
        float yp = player.getBox()->y-camera.y;
        //items[1]->setPos(px,py);
        
        x -= 320; // to normal coords
        y = -240+y;
        xp-= 320; // to normal coords
        yp = -240+yp;
        
        float dx = x-xp;
        float dy = y-yp;
        
        x-=xp;
        y-=yp;
  
        float xx = dx;
        dx = dx/(float)sqrt((dx*dx)+(dy*dy));//unitary vector
        dy = dy/(float)sqrt((xx*xx)+(dy*dy));
        
        
        par.SetDir(dx,dy);
        par.SetPos(player.getBox()->x-camera.x+player.getBox()->w/2,player.getBox()->y-camera.y);
        par.Run();
        par.Render(w.getAmb());
        
        */
         
        if(luaL_dofile(L,"openworld/test.lua")==1){
            cout << "error loading script" << endl;
            const char *out = lua_tostring(L,-1);
            std::cout << out << std::endl;
            lua_pop(L,1);
        };
        
        map1.RenderLayer(1,w.getAmb(),w);
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
