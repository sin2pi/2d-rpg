//
//  Animation.cpp
//  openworld
//
//  Created by martin dionisi on 19/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#include "Animation.h"

Animation::Animation(int x,int y,int w,int h,int nx,int speed)
{
    
    Nx = nx;
    for(int i = 0;i<Nx;i++)
    {
        SDL_Rect rect;
        rect.x = x + w*i;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        clip.push_back(rect);
    }
    frame = 0;
    counter = 0;
    timer = 0;
    Speed = speed;
}

void Animation::RenderFrame(SDL_Rect pos, SDL_Texture *txt)
{
    //SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, img);
    SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)), txt, &clip[frame],&pos);
    //SDL_BlitSurface(img,&clip[frame],SDL_GetVideoSurface(),&pos);
}

void Animation::RunAnimation(SDL_Rect pos, SDL_Texture *txt)
{
    timer ++;
    if(timer >= Speed*counter){
        frame ++;
        counter ++;
    }
    if(frame >= Nx){
        frame = 0;
    }
    
    SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)), txt, &clip[frame],&pos);
}