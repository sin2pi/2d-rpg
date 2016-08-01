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
    int angle;
    int ix,iy;
    vec2d pos;
    vec2d l1,l2;
    float speed;
    vec2d dir;
    vec2d vec;
    bool active;
    
public:
    
    void changeState(bool running){
        if(running){
            active = true;
        }
        else{
            active = false;
        }
    }
    
    void SetPos(int x,int y){
        pos.x = x;
        pos.y = y;
    }
    
    void SetDir(float dx,float dy){
        vec.x = dx;
        vec.y = dy;
    }
    
    float Rand(int nMin, int nMax)
    {
        return nMin + (int)((double)rand() / (RAND_MAX+1) * (nMax-nMin+1));
    }
    float RandomFloat(float a, float b) {
        return ((b-a)*((float)rand()/RAND_MAX))+a;
    }
    
    ParticleEngine(int amt,int ang,int spd,vec2d d,vec2d p)
    {
        active = true;
        speed = spd;
        angle = ang;
        vec = d;
        pos.x = p.x;
        pos.y = p.y;
        int time;
      //  l1 = {1,-0.1};
      //  l2 = {0.5,0.5};
        
        for(int i = 0;i < amt;i++)
        {
            particles.push_back(new Particle());
        }
    }
    
    void Run()
    {
        if(active && onScreen()){
        l1.x = cos((angle* 3.142 / 180.0)/2)*vec.x - sin((angle* 3.142 / 180.0)/2)*vec.y;
        l1.y = sin((angle* 3.142 / 180.0)/2)*vec.x + cos((angle* 3.142 / 180.0)/2)*vec.y;
        
        l2.x = cos(-(angle* 3.142 / 180.0)/2)*vec.x - sin(-(angle* 3.142 / 180.0)/2)*vec.y;
        l2.y = sin(-(angle* 3.142 / 180.0)/2)*vec.x + cos(-(angle* 3.142 / 180.0)/2)*vec.y;
        for(int i = 0;i<particles.size();i++)
        {
            
            particles.at(i)->Update();
            if(particles.at(i)->isDead())
            {
                dir.x = RandomFloat(l2.x,l1.x);
                dir.y = RandomFloat(l2.y,l1.y);
                int spd = Rand(speed - 1,speed + 1);
                int time = Rand(500,1000);
                delete  particles.at(i);
                particles.erase(particles.begin()+i);
                particles.push_back(new Particle(pos,dir,spd,time));
            }
        }
        }
    }
    
    bool onScreen()
    {
        int w,h;
        SDL_GetWindowSize(SDL_GetWindowFromID(1),&w,&h);
        if(pos.x > w)
            return false;
        else if(pos.x < 0)
            return false;
        else if(pos.y > h)
            return false;
        else if(pos.y < 0)
            return false;
        else return true;
    }
    
    void Render(float amb)
    {
        if(active && onScreen()){
        for(int i = 0;i<particles.size();i++)
        {
            particles.at(i)->Render(amb);
        }
        }
    }
    
    
};

#endif
