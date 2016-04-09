//
//  Physics.h
//  openworld
//
//  Created by martin dionisi on 1/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#ifndef openworld_Physics_h
#define openworld_Physics_h
#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>
#include "item.h"

//class cItem;

using namespace std;

class Physics{
    
public:
    
    static void elasticCollision(float &v1,float m1,float &v2,float m2)
    {
        float ve1 = v1;
        float ve2 = v2;
        float dm = m1-m2;
        float sm = m1+m2;
        v1 = ((dm/sm)*ve1)+(((2*m2)/sm)*ve2);
        v2 = (((2*m2)/sm)*ve1)-((dm/sm)*ve2);
        
    }
    
    static bool circlecol(SDL_Rect *rect1,int x,int y,int r)
    {
        float dx = rect1->x - x;
        float dy = rect1->y - y;
        
        float dis = sqrtf(((dx*dx)+(dy*dy)));
        
        if(dis <= r)
            return true;
        else
            return false;
    }
    
    static bool collision(SDL_Rect* rect1,SDL_Rect* rect2)
    {
        if(rect1->y + rect1->h <= rect2->y)
            return 0;
        if(rect1->x + rect1->w <= rect2->x)
            return 0;
        if(rect1->y >= rect2->y + rect2->h)
            return 0;
        if(rect1->x >= rect2->x + rect2->w)
            return 0;
       
        return 1;
    }
};

#endif
