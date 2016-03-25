//
//  Inventory.h
//  openworld
//
//  Created by martin dionisi on 2/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#pragma once

#include "Item.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <SDL/SDL.h>

class cItem;
class cPlayer;

using namespace std;

class Inventory{
    
private:
    
    vector<int*>index;
    vector<cItem*>inventory;
    int queue;
    SDL_Rect rq;
    SDL_Surface *asur;
    
public:
    
    Inventory();
    void HandleInput(SDL_Event event,cPlayer player,vector<cItem*>items);
    void AddItem(cItem *item);
    void QuitItem(int id);
    void Render();
};

