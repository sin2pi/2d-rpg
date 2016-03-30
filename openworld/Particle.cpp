//
//  Inventory.cpp
//  openworld
//
//  Created by martin dionisi on 30/3/16.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//


#include "Particle.h"

Particle::Particle(vec2d p,vec2d d,float s,int lf){
    pos.x = p.x;
    pos.y = p.y;
    pos.w = 4;
    pos.h = 4;
    ix = p.x;
    iy = p.y;
    dir.x = d.x;
    dir.y = d.y;
    speed = s;
    timer = SDL_GetTicks()+lf;
    life = lf;
}


void Particle::Update(){
    if(!isDead()){
        pos.x += dir.x * speed;
        pos.y += dir.y * speed;
    }
    
}

bool Particle::isDead(){
    if(SDL_GetTicks() > timer)
        return true;
    if(pos.x < 0)
        return true;
    if(pos.y < 0)
        return true;
    if(pos.x > 640)
        return true;
    if(pos.y > 480)
        return true;
    
    
    return false;
}

void Particle::Render()
{
    if(!isDead()){
        //SDL_FillRect(,&pos,SDL_MapRGB(SDL_GetRenderer()->format,0,0,200));
        SDL_SetRenderDrawColor(SDL_GetRenderer(SDL_GetWindowFromID(1)), 0, 0, 255, 255 );
        
        // Render rect
        SDL_RenderFillRect(SDL_GetRenderer(SDL_GetWindowFromID(1)), &pos );
    }
}
