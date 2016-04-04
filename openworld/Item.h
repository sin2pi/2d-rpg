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

class Inventory;

class cItem
{
private:
    
    SDL_Rect box;
    SDL_Surface *image;
    SDL_Texture *txt;
    bool used,dropped,moved;
    int state;
    float vel;
    float xvel,yvel;
    string sf;
    int id;
    string filename;
    
public:
    bool grabed;
    string getScript(){return sf;}
    string getImgFile(){return filename;}
    cItem(int xpos,int ypos,int w,int h,float vel,string file,string script,int index);
    void Render();
    void Interact(vector<cItem*>items);
    SDL_Rect getPos(){ return box;};
    SDL_Rect *getRect(){ return &box;};
    float &getVel(int a){if(a==1)return xvel;else return yvel;}
    int getState(){ return state;};
    void setPos(int x,int y){box = {static_cast<Sint16>(x),static_cast<Sint16>(y),box.w,box.h};};
    void setVel(float xv,float yv){xvel = xv;yvel = yv;}
    SDL_Texture *getImage(){return txt;};
    int getId(){return id;};
};


#endif
