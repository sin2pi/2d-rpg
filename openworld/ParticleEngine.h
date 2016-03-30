//
//  ParticleEngine.h
//  ParticleEngine
//
//  Created by martin dionisi on 13/3/16.
//  Copyright (c) 2016 martin dionisi. All rights reserved.
//

#ifndef ParticleEngine_ParticleEngine_h
#define ParticleEngine_ParticleEngine_h

#include "Particle.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

using namespace std;

class ParticleEngine{
    
private:
    
    vector<Particle*> particles;
    vec2d lim1,lim2;
    int ix,iy;
    vec2d pos;
    
public:
    
    void SetPos(int x,int y){
        pos.x = x;
        pos.y = y;
    }
    
    float Rand(int nMin, int nMax)
    {
        return nMin + (int)((double)rand() / (RAND_MAX+1) * (nMax-nMin+1));
    }
    float RandomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return random;
    }
    
    ParticleEngine(int amt,vec2d l1,vec2d l2,vec2d p)
    {
        float speed;
        vec2d dir;
        lim1 = l1;
        lim2 = l2;
        pos.x = p.x;
        pos.y = p.y;
        int time;
        
        for(int i = 0;i < amt;i++)
        {
            particles.push_back(new Particle());
        }
    }
    
    void Run()
    {
        float speed;
        vec2d dir;
        for(int i = 0;i<particles.size();i++)
        {
            particles.at(i)->Update();
            if(particles.at(i)->isDead())
            {
                
                dir.x =rand()%10-5;
                dir.y =rand()%10-5;
                //dir.x = Rand(lim1.x, lim2.x);
                //dir.y = Rand(lim1.y, lim2.y);
                speed = Rand(1,4);
                int time = Rand(1000,3000);
                delete particles.at(i);
                particles.erase(particles.begin()+i);
                particles.push_back(new Particle(pos,dir,speed,time));
            }
        }
    }
    void Render()
    {
        for(int i = 0;i<particles.size();i++)
        {
            particles.at(i)->Render();
        }
    }
    
    
};

#endif
