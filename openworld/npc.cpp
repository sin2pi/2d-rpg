#include "npc.h"

extern SDL_Surface *screen;
extern SDL_Rect camera;
extern bool collision(SDL_Rect* rect1,SDL_Rect* rect2);
using namespace std;

cNpc::cNpc(float x,float y,int w,int h,int xvel,int yvel,float power,float hp,int rp,const char*file,int nx)
{
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xVel = xvel;
    yVel = yvel;
    xSpeed = xVel;
    ySpeed = yVel;
    ranim = new Animation(0,0,w,h,nx,10);
    lanim = new Animation(0,h,w,h,nx,10);
    Hp = hp;
    Power = power;
    rep = rp;
    setSquarePath(150, 100);
    image = SDL_LoadBMP(file);
    SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,255,255));
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
                box.x -= xVel;
            }
            else if(side[3])
            {
                box.x += xVel;
            }
            if(side[0])
            {
                box.y -= yVel;
            }
            else if(side[2])
            {
                box.y += yVel;
            }
            
        }
    }
    
    
}

void cNpc::setSquarePath(int width, int height)
{
    vrt[0] = {static_cast<float>(box.x),static_cast<float>(box.y)};
    vrt[1] = {static_cast<float>(box.x + width),static_cast<float>(box.y)};
    vrt[2] = {static_cast<float>(box.x + width),static_cast<float>(box.y+height)};
    vrt[3] = {static_cast<float>(box.x),static_cast<float>(box.y+height)};
}

void cNpc::runPath()
{
    ontrack = false;
    if(box.y == vrt[1].y && box.x <= vrt[1].x){
        Move(vrt[1].x,vrt[1].y);
        ontrack = true;
    }
    if(box.x == vrt[2].x && box.y <= vrt[2].y){
        Move(vrt[2].x,vrt[2].y);
        ontrack = true;
    }
    if(box.y == vrt[3].y && box.x >= vrt[3].x){
        Move(vrt[3].x,vrt[3].y);
        ontrack = true;
    }
    if(box.x == vrt[0].x && box.y >= vrt[0].y){
        Move(vrt[0].x,vrt[0].y);
        ontrack = true;
    }
    if(!ontrack && !onradar)
        Move(vrt[0].x,vrt[0].y);
}

void cNpc::Interact(cPlayer p)
{
    if(Physics::circlecol(p.getBox(),box.x,box.y,rad))
    {
        onradar = true;
        if(rep >= 70)
        {
            friends = true;
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
        if(rep < 30)
        {
            friends = false;
            Move(p.getBox()->x,p.getBox()->y);
            //attack & stuff
            if(Physics::collision(&box,p.getBox()))
            {
                if(side[1])
                {
                    box.x -= xVel;
                }
                else if(side[3])
                {
                    box.x += xVel;
                }
                if(side[0])
                {
                    box.y -= yVel;
                }
                else if(side[2])
                {
                    box.y += yVel;
                }
            }
        }
        if(rep >= 30 && rep < 70)
        {
            friends = false;
            
        }

    }
    else{
        
        xVel = xSpeed;
        yVel = ySpeed;
        onradar = false;
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
         if(box.y == y)
         {
             e = 2;
         }
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
         if(box.x == x)
         {
             b = 2;
         }
     }
     
     }
}

void cNpc::Render()
{
    SDL_Rect rect = {static_cast<Sint16>(box.x - camera.x), static_cast<Sint16>(box.y - camera.y)};
    if(Hp > 0){
        if(side[3])
        {
            lanim->RunAnimation(rect,image);
        }
        else if(side[1])
        {
            ranim->RunAnimation(rect,image);
        }
        else if(side[2])
        {
            lanim->RunAnimation(rect,image);
        }
        else if(side[0])
        {
            ranim->RunAnimation(rect,image);
        }
    }
}
