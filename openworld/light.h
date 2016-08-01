//
//  weather.h
//  weather
//
//  Created by martin dionisi on 13/3/16.
//  Copyright (c) 2016 martin dionisi. All rights reserved.
//

#include <iostream>
#include <SDL/SDL.h>
#include <math.h>
#include <vector>

using namespace std;

#pragma once

class light{
    
private:
    
    float ambient,point;
    int scalar;
    float lapse;
    
    
public:
    
    light(int speed);
    
    float resolvePointLight(float x,float y,float px,float py);
    
    float getAmb();
    
    void startLapse();
    
    
};
