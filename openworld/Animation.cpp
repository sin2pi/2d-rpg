//
//  Animation.cpp
//  openworld
//
//  Created by martin dionisi on 19/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#include "Animation.h"
extern SDL_Rect camera;

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
        if(rect.w > 100)
            rect.w = 100;
        clip.push_back(rect);
    }
    frame = 0;
    counter = 0;
    timer = 0;
    Speed = speed;
}

void Animation::RenderFrame(SDL_Rect pos, SDL_Texture *txt,light w)
{

        float a = w.resolvePointLight(600-camera.x, 700-camera.y,pos.x,pos.y);
        float c1 = a*255;
        float c2 = a*255;
        float c3 = a*255;
        if(c1 > 255)
            c1 = 255;
        if(c2 > 255)
            c2 = 255;
        if(c3 > 255)
            c3 = 255;
        SDL_SetTextureColorMod(txt,c1,c2,c3);

}

void Animation::RunAnimation(SDL_Rect pos, SDL_Texture *txt,light w)
{
    timer ++;
    if(timer >= Speed*counter){
        frame ++;
        counter ++;
    }
    if(frame >= Nx){
        frame = 0;
    }
    float amb = w.getAmb();
    float angle = 0.0f; // set the angle.
    SDL_Point center = {8, 8}; // the center where the texture will be rotated.
    SDL_RendererFlip flip = SDL_FLIP_NONE; // the flip of the texture.
    //SDL_SetTextureColorMod(txt,255*amb,255*amb,255*amb);
    if(Physics::circlecol(&pos, 600-camera.x, 700-camera.y, 4000))
    {
        float a = w.resolvePointLight(600-camera.x, 700-camera.y,pos.x,pos.y);
        float c1 = a*255;
        float c2 = a*255;
        float c3 = a*255;
        if(c1 > 255)
            c1 = 255;
        if(c2 > 255)
            c2 = 255;
        if(c3 > 255)
            c3 = 255;
        SDL_SetTextureColorMod(txt,c1,c2,c3);
    }
    else SDL_SetTextureColorMod(txt,255*amb,255*amb,255*amb);
        
    SDL_RenderCopyEx(SDL_GetRenderer(SDL_GetWindowFromID(1)), txt, &clip[frame],&pos,angle,&center,flip);
}