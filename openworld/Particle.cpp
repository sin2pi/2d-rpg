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
    pos.w = 3;
    pos.h = 3;
    posVec.x = p.x;
    posVec.y = p.y;
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
        fx++;
        posVec.x += dir.x * speed;
        posVec.y += dir.y * speed+(fx*fx)/40;
        pos.x = (int)posVec.x;
        pos.y = (int)posVec.y;
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

void Particle::Render(float amb)
{
    if(!isDead()){
        //SDL_FillRect(,&pos,SDL_MapRGB(SDL_GetRenderer()->format,0,0,200));
        SDL_SetRenderDrawColor(SDL_GetRenderer(SDL_GetWindowFromID(1)), 0, 0*amb, 255*amb, 255*amb);
        
        // Render rect
        SDL_RenderFillRect(SDL_GetRenderer(SDL_GetWindowFromID(1)), &pos );
    }
}
