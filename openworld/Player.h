#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Physics.h"
#include "npc.h"
#include "Item.h"
#include "Inventory.h"
#include "Animation.h"

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
    float xpos,ypos;
    
    SDL_Rect box;
    vector<Animation*>idle;
    Animation *ranim;
    Animation *lanim;
    int idleframe;
    int dir[4] = {0,0,0,0};
    
    public:
    float xSpeed,ySpeed;
    float xVel,yVel;
    SDL_Rect *getBox(){ return &box;}
    cPlayer(float x,float y,int w,int h,float xspeed,float yspeed,float acc,const char*file,int nx);
    SDL_Rect SetCamera(SDL_Rect cam);
    void Interact(vector<cNpc*>n);
    void Interact(vector<cItem*>n);
    void Render(SDL_Rect camera);
    void Move();
    void HandleInput(SDL_Event event,vector<cItem*>n,Inventory *inv);
    void Grab(SDL_Rect object);
};
