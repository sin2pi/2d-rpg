//
//  Particle.h
//  ParticleEngine
//
//  Created by martin dionisi on 13/3/16.
//  Copyright (c) 2016 martin dionisi. All rights reserved.
//

#ifndef ParticleEngine_Particle_h
#define ParticleEngine_Particle_h

#include <SDL2/SDL.h>
#include <vector>


struct vec2d{
    float x,y,w,h;
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
    Particle(vec2d p,vec2d d,float s,int lf);
    Particle(){};
    
    void Update();
    
    bool isDead();
    
    void Render();
    
};

#endif
