#pragma once

#include <SDL/SDL.h>
#include <vector>
#include "Player.h"
#include <fstream>

using namespace std;

class cPlayer;

class cNpc
{
    private:
    
    SDL_Surface *image;
    float xVel,yVel,ySpeed,xSpeed;
    SDL_Rect box;
    int side[4];
    float Power,Hp;
    bool friends;
    int rep;
    int rad = 250;
 
    public:
    cNpc(float x,float y,int w,int h,int xvel,int yvel,float power,float hp,int rp,const char*file);
    SDL_Rect *getBox(){ return &box;}
    float getXvel() { return xVel;};
    float getYvel() { return yVel;};
    void Interact(cPlayer p);
    void Interact(vector<cNpc*>n);
    void Move(int x,int y);
    void collide(SDL_Rect object);
    void Render();
};
