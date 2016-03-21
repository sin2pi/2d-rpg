//
//  Animation.h
//  openworld
//
//  Created by martin dionisi on 19/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#ifndef __openworld__Animation__
#define __openworld__Animation__

#include <vector>
#include <SDL/SDL.h>

using namespace std;

class Animation{
    
private:
    SDL_Rect offset;
    int Nx,Speed,timer,frame,counter;
    vector<SDL_Rect>clip;
    
public:
    
    void SetFrame(int f){
        frame = f;
    }
    
    Animation(int x,int y,int w,int h,int nx,int speed);
    
    void RunAnimation(SDL_Rect pos,SDL_Surface*img);
    void RenderFrame(SDL_Rect pos,SDL_Surface *img);
    
};

#endif /* defined(__openworld__Animation__) */
