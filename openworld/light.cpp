#include "light.h"

light::light(int speed)
{
    scalar = speed;
}

void light::startLapse()
{
    lapse ++;
    
    float grad = lapse/scalar;
    
    ambient = cosf(grad);
    if(ambient < 0)
        ambient *= -1;
    if(ambient < 0.15)
        ambient = 0.15;
    
    cout << ambient << endl;
}
float light::resolvePointLight(float x,float y,float px,float py)
{
    SDL_Rect o;
    o.x = x;
    o.y = y;
    float dis = sqrtf(((px-o.x)*(px-o.x))+((py-o.y)*(py-o.y)));
    float inv = (50/dis);
    float res = ambient+(inv);
    return res;
}


float light::getAmb()
{
    return ambient;
}