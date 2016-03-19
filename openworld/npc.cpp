#include "npc.h"

extern SDL_Surface *screen;
extern SDL_Rect camera;
extern bool collision(SDL_Rect* rect1,SDL_Rect* rect2);
using namespace std;

cNpc::cNpc(float x,float y,int w,int h,int xvel,int yvel,float power,float hp,const char*file)
{
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xVel = xvel;
    yVel = yvel;
    Hp = hp;
    Power = power;
    image = SDL_LoadBMP(file);
}

void cNpc::Interact(vector<cNpc*>n)
{
    for(int  i = 0;i < n.size();i++)
    {
        if(box.x == n.at(i)->box.x && box.y == n.at(i)->box.y)
        {
            continue;
        }
        else if(Physics::collision(&box, &n.at(i)->box))
        {
            if(side[1])
            {
                xVel = 0;
            }
            else if(side[3])
            {
                xVel = 0;
            }
            if(side[0])
            {
                yVel = 0;
            }
            else if(side[2])
            {
                yVel = 0;
            }
            
        }
    }
    
}

void cNpc::Interact(cPlayer p)
{
    if(Physics::collision(&box,p.getBox()))
    {
        if(side[1])
        {
            xVel = 0;
        }
        else if(side[3])
        {
            xVel = 0;
        }
        if(side[0])
        {
            yVel = 0;
        }
        else if(side[2])
        {
            yVel = 0;
        }
    }
}

void cNpc::Move(int x, int y)
{
    if(Hp > 0)
    {
    int e;
    int b;
    if(box.y != y)
    e = 1;
    if(box.x != x)
    b = 1;
    if(e == 1)
     {
          if (y  < box.y){
             box.y -= yVel;
             side[2] = 1;
             side[0] = 0;
             }
          if (y > box.y){
             box.y += yVel;
             side[0] = 1;
             side[2] = 0;
             }
     }
     if(box.y == y)
     {
       e = 2;
     }

      if(b == 1)
     {
          if (x  < box.x){
             box.x -= xVel;
             side[1] = 0;
             side[3] = 1;
             }
          if (x > box.x){
             box.x += xVel;
             side[1] = 1;
             side[3] = 0;
             }
     }
     if(box.x == x)
     {
       b = 2;
     }
     }
}

void cNpc::Render()
{
    SDL_Rect rect = {static_cast<Sint16>(box.x - camera.x), static_cast<Sint16>(box.y - camera.y)};
    if(Hp > 0)
    SDL_BlitSurface(image,NULL,screen,&rect);
}
