//
//  Item.h
//  openworld
//
//  Created by martin dionisi on 2/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#ifndef openworld_Item_h
#define openworld_Item_h

#include <SDL/SDL.h>
#include "Player.h"
#include "Physics.h"
#include "Inventory.h"

class Inventory;

class cItem
{
private:
    
    SDL_Rect box;
    SDL_Surface *image;
    bool used,dropped;
    int state;
    string filename;
    int id;
    
public:
    bool grabed;
    cItem(int xpos,int ypos,int w,int h,string file,int index);
    void Render();
    void Interact(SDL_Event event,cPlayer player,Inventory *inv);
    SDL_Rect getPos(){ return box;};
    int getState(){ return state;};
    void setPos(int x,int y){box = {static_cast<Sint16>(x),static_cast<Sint16>(y),box.w,box.h};};
    SDL_Surface *getImage(){return image;};
    int getId(){return id;};
};


#endif
