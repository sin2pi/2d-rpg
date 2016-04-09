//  Item.cpp
//  openworld
//
//  Created by martin dionisi on 2/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#include "Item.h"

extern SDL_Rect camera;

cItem::cItem(int xp,int yp,int w,int h,float vel,string file,string script,int index)
{
    box.x = xp;
    box.y = yp;
    box.w = w;
    box.h = h;
    xpos = xp;
    ypos = yp;
    xvel = yvel = vel;
    filename = file;
    const char *f =file.c_str();
    grabed = false;
    image = SDL_LoadBMP(f);
    sf = script;
    txt = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)),image);
    id = index;
}


void cItem::Interact(vector<cItem*> items)
{
    for(int i = 0;i<items.size();i++)
    {
        if(box.x == items.at(i)->box.x && box.y == items.at(i)->box.y)
        {
            continue;
        }
        else if(Physics::collision(&box,items.at(i)->getRect()))
        {
            if(xvel!=0){
                Physics::elasticCollision(xvel,20,items.at(i)->xvel,20);
            }
            if(yvel!=0) {
                Physics::elasticCollision(yvel,20,items.at(i)->yvel,20);
            }
            
        }
    }
    
    if(xvel > 0){
        //int xs = xvel;
        xvel -= 0.05;
        if(xvel <= 0)
            xvel = 0;
        xpos += xvel;
    }
    else if(xvel < 0){
        //int xs = xvel;
        xvel += 0.05;
        if(xvel >= 0)
            xvel = 0;
        xpos += xvel;
    }
    else xvel = 0;
    if(yvel > 0){
        //int ys = yvel;
        yvel -= 0.05;
        if(yvel <= 0)
            yvel = 0;
        ypos += yvel;
    }
    else if(yvel < 0){
        //int xs = xvel;
        yvel += 0.05;
        if(yvel >= 0)
            yvel = 0;
        ypos += yvel;
    }
    else yvel = 0;
    
    

}

void cItem::Render()
{
    box.x = (int)xpos;
    box.y = (int)ypos;
    SDL_Rect box1 = {static_cast<Sint16>(box.x-camera.x),static_cast<Sint16>(box.y-camera.y),box.w,box.h};
    if(grabed == false){
        SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),txt,NULL,&box1);
    }
}






