#pragma once

#include <SDL/SDL.h>
#include <vector>
#include "Player.h"
#include <fstream>
#include "Particle.h"
#include "Animation.h"

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
    int rad = 150;
    bool ontrack;
    bool onradar;
    bool moving;
    int nx;
    Animation *ranim;
    Animation *lanim;
    vec2d vrt[4];
    
 
    public:
    cNpc(float x,float y,int w,int h,int xvel,int yvel,float power,float hp,int rp,const char*file,int nx);
    SDL_Rect *getBox(){ return &box;}
    float getXvel() { return xVel;};
    float getYvel() { return yVel;};
    int getRep(){return rep;};
    void startPath(){moving = true;};
    void stopPath(){moving = false;};
    void setSquarePath(int width, int height);
    void setSpeed(float n);
    void setRep(int n);
    void setPos(int x,int y);
    void runPath();
    void Interact(cPlayer p);
    void Interact(vector<cNpc*>n);
    void Move(int x,int y);
    void collide(SDL_Rect object);
    void Render();
};
