#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Player.h"
#include <fstream>
#include "Particle.h"
#include "Animation.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace std;

class cPlayer;

class cNpc
{
    private:
    
    SDL_Surface *image;
    SDL_Texture *txt;
   
    SDL_Rect box;
    int side[4];
    float Power,Hp;
    bool friends;
    int rep;
    int rad = 10;
    bool rmoving;
    bool ontrack;
    bool onradar;
    bool moving;
    int vrtRange;
    int timeRange;
    int horRange;
    int iX,iY;
    int nx;
    float xVel,yVel,ySpeed,xSpeed;
    Animation *ranim;
    Animation *lanim;
    vector <Animation*>idle;
    int idleframe;
    vec2d vrt[4];
    bool ontarget = false;
    int movNum = 2;
    int x,y;
    Uint32 timer;
 
    public:
    
    cNpc(float x,float y,int w,int h,int xvel,int yvel,float power,float hp,int rp,const char*file,int nx);
    SDL_Rect *getBox(){ return &box;}
    float *getXvel() { return &xVel;};
    float getYvel() { return yVel;};
    int getRep(){return rep;};
    bool isonTarget(int tx,int ty);
    void startPath(int type);
    void stopPath();
    void setSquarePath(int width, int height);
    void setRandPath(int ix,int iy,int hr,int vr,int tr);
    void runRandPath();
    void setSpeed(float n);
    void setRep(int n);
    void setPos(int x,int y);
    void runPath();
    void Interact(cPlayer p);
    void Interact(vector<cNpc*>n);
    void Move(int x,int y);
    void collide(SDL_Rect object);
    void Render(SDL_Rect camera,light w);
};
