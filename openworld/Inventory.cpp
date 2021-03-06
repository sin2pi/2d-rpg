//
//  Inventory.cpp
//  openworld
//
//  Created by martin dionisi on 4/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#include "Inventory.h"

Inventory::Inventory()
{
    queue = 0;
}

void Inventory::AddItem(cItem *item)
{
    inventory.push_back(item);
}
void Inventory::QuitItem(int id)
{
    delete inventory.at(id);
    inventory.erase(inventory.begin()+id);
}

void Inventory::HandleInput(SDL_Event event,cPlayer player,vector<cItem*>items)
{
    int x,y;
    
    SDL_GetMouseState(&x,&y);
    SDL_Rect mouse = {static_cast<Sint16>(x),static_cast<Sint16>(y)};
    switch(event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_RIGHT)
            {
                for(int i = 0; i< inventory.size();i++)
                {
                    SDL_Rect rec = {static_cast<Sint16>((100+(i*60))),400,30,30};
                    if(Physics::collision(&mouse,&rec)){
                        items.at(inventory.at(i)->getId())->isGrabed() = false;
                        items.at(inventory.at(i)->getId())->setPos(player.getBox()->x, player.getBox()->y);
                        inventory.erase(inventory.begin()+i);
                    }
                }
            }break;
        case SDL_JOYBUTTONDOWN:
            if(event.jbutton.button == 3)
            {
                if(inventory.size() >= 1){
                    items.at(inventory.at(queue)->getId())->isGrabed() = false;
                    items.at(inventory.at(queue)->getId())->setPos(player.getBox()->x, player.getBox()->y);
                    inventory.erase(inventory.begin()+queue);
                }
            }
            if(event.jbutton.button == 4)
            {
                queue --;
            }
            if(event.jbutton.button == 5)
            {
                queue ++;
            }
            break;
    }
}

void Inventory::Render()
{
    SDL_Surface *asur = SDL_LoadBMP("/Users/martindionisi/Desktop/openworld/openworld/queuerec.bmp");
    //SDL_SetAlpha(asur,SDL_SRCALPHA,120);
    if(queue < 0)
        queue = 0;
    if(queue >= inventory.size())
        queue = inventory.size()-1;
    
    
    rq = {static_cast<Sint16>((100+(queue*60))),400,40,40};
    for(int i =0; i < inventory.size();i++)
    {
        SDL_Rect box = {static_cast<Sint16>(100+(i*60)),static_cast<Sint16>(400),32,32};
        SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),inventory.at(i)->getImage(),NULL,&box);
        
    }
    //SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(NULL)),txt,NULL,&rq);
    SDL_FreeSurface(asur);
    
}
