#ifndef LUAPROMPT_H
#define LUAPROMPT_H
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <SDL2_ttf/SDL_ttf.h>

extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

class LuaPrompt
{
    
private:
    int c = 1;
    std::string strcpy;
    SDL_Texture *txt;
    bool run = false;
    TTF_Font *font2;
    SDL_Color green = {0,200,0};
    bool PromptActive;
    std::string str;
    
public:
    LuaPrompt();
    ~LuaPrompt();
 
    void runScrip(lua_State *L);
    void update(SDL_Surface*);
    void HandleInput(SDL_Event event,lua_State *L);
};

#endif // LUAPROMPT_H
