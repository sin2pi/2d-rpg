//
//  Item.h
//  openworld
//
//  Created by martin dionisi on 2/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#ifndef openworld_Item_h
#define openworld_Item_h

#include <SDL2/SDL.h>
#include "Player.h"
#include "Physics.h"
#include "Inventory.h"
#include "Particle.h"

class Inventory;

class cItem
{
private:
    
    SDL_Rect box;
    SDL_Surface *image;
    SDL_Texture *txt;
    
    int state;
    float vel;
    float xvel,yvel;
    vec2d pos;
    string sf;
    int id;
    string filename;
    
public:
    bool grabed;
    bool used,dropped,moved;
    
    
    string getScript(){return sf;}
    string getImgFile(){return filename;}
    cItem(int xpos,int ypos,int w,int h,float vel,string file,string script,int index);
    void Render();
    void Interact(vector<cItem*>items);
    SDL_Rect getPos(){ return box;};
    SDL_Rect *getRect(){ return &box;};
    int getState(){ return state;};
    void setPos(int x,int y){pos.x = x;pos.y = y;};
    void setVel(float xv,float yv){xvel = xv;yvel = yv;}
    SDL_Texture *getImage(){return txt;};
    int getId(){return id;};
};


#endif
