#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Physics.h"
#include "npc.h"
#include "Item.h"
#include "Inventory.h"
#include "Animation.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace std;
class cNpc;
class cItem;
class Inventory;
class cPlayer
{
    private:
    
    SDL_Surface *image;
    SDL_Texture *txt;
    float acceleration;
    bool grabing = false;
    int count = 0;
    bool coliding = false;
    bool moving = false;
    int movId;
    float xpos,ypos;
    
    SDL_Rect box;
    vector<Animation*>idle;
    Animation *ranim;
    Animation *lanim;
    Animation *uanim;
    Animation *danim;
    int idleframe;
    int dir[4] = {0,0,0,0};
    
    public:
    float xSpeed,ySpeed;
    float xVel,yVel;
    void setPos(int x,int y){xpos = x;ypos = y;};
    void setVel(int xV,int yV){xVel = xV;yVel = yV;xSpeed=xV;ySpeed=yV;};
    int getpos()const{return box.x;}
    bool isGrabbing(){return grabing;}
    bool &isMoving(){return moving;}
    float getVel(int a){if(a==1)return xVel;else return yVel;}
    SDL_Rect *getBox(){ return &box;}
    cPlayer(float x,float y,int w,int h,float xspeed,float yspeed,float acc,const char*file,int nx);
    cPlayer(float x,float y,int w,int h,float xspeed,float yspeed,float acc);
    cPlayer(){};
    SDL_Rect SetCamera(SDL_Rect cam);
    void Interact(vector<cNpc*>n);
    void Interact(vector<cItem*>n);
    void Render(SDL_Rect camera);
    void Move();
    void HandleInput(SDL_Event event,vector<cItem*>n,Inventory *inv);
    void Grab(SDL_Rect object);
};
