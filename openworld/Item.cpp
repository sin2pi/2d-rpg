//
//  Item.cpp
//  openworld
//
//  Created by martin dionisi on 2/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#include "Item.h"

extern SDL_Rect camera;

cItem::cItem(int xpos,int ypos,int w,int h,string file,int index)
{
    box.x = xpos;
    box.y = ypos;
    box.w = w;
    box.h = h;
    filename = file;
    const char *f =file.c_str();
    grabed = false;
    image = SDL_LoadBMP(f);
    txt = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)),image);
    id = index;
}

void cItem::Interact(SDL_Event event,cPlayer player,Inventory *inv)
{
    if(event.type == SDL_QUIT)
        SDL_Quit();
    if(event.type == SDL_KEYDOWN){
        
        if(event.key.keysym.sym == SDLK_g)
        {
            if(Physics::collision(&box,player.getBox())&& grabed == false)
            {
                inv->AddItem(new cItem(box.x,box.y,box.w,box.h,filename,id));
                grabed = true;
            }
        }
        
    }
    if(event.type == SDL_JOYBUTTONDOWN)
    {
        if(event.jbutton.button == 1)
        {
            if(Physics::collision(&box,player.getBox())&& grabed == false)
            {
                inv->AddItem(new cItem(box.x,box.y,box.w,box.h,filename,id));
                grabed = true;
            }
        }
    }
    if(event.type == SDL_KEYUP){
        
    }
}

void cItem::Render()
{
    SDL_Rect box1 = {static_cast<Sint16>(box.x-camera.x),static_cast<Sint16>(box.y-camera.y),box.w,box.h};
    if(grabed == false){
        SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),txt,NULL,&box1);
    }
}






