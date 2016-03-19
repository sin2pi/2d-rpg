//
//  Particle.h
//  ParticleEngine
//
//  Created by martin dionisi on 13/3/16.
//  Copyright (c) 2016 martin dionisi. All rights reserved.
//

#ifndef ParticleEngine_Particle_h
#define ParticleEngine_Particle_h

#include <SDL/SDL.h>
#include <vector>


struct vec2d{
    float x,y;
};

class Particle{
    
private:
    
    SDL_Rect pos;
    Uint32 timer;
    Uint32 life;
    SDL_Color *col;
    bool dead = false;
    float speed;
    int ix,iy;
    
    
public:
    vec2d dir;
    Particle(vec2d p,vec2d d,float s,int lf){
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
    Particle(){};
    
    void Update(){
        if(!isDead()){
            pos.x += dir.x * speed;
            pos.y += dir.y * speed;
        }
        
    }
    
    bool isDead(){
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
    
    void Render()
    {
        if(!isDead())
            SDL_FillRect(SDL_GetVideoSurface(),&pos,SDL_MapRGB(SDL_GetVideoSurface()->format,0,0,200));
    }
    
};

#endif
