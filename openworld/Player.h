#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Physics.h"
#include "npc.h"
#include "Item.h"
#include "Animation.h"

using namespace std;
class cNpc;
class cItem;
class cPlayer
{
    private:
    
    SDL_Surface *image;
    SDL_Texture *txt;
    float acceleration;
    
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
    void Render(SDL_Rect camera);
    void Move();
    void HandleInput(SDL_Event event);
    void Grab(SDL_Rect object);
};
