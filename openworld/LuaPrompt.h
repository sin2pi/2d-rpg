#ifndef LUAPROMPT_H
#define LUAPROMPT_H
#include <SDL2/SDL.h>
#include <string>
#include <SDL_ttf/SDL_ttf.h>
extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}
class LuaPrompt
{
public:
    //Constructor & Deconstructor
    LuaPrompt();
    ~LuaPrompt();

    TTF_Font *font2;
    SDL_Color green = {0,200,0};
    bool PromptActive;
    //String Holder
    std::string str;
    //Update Prompt Text
    void update(SDL_Surface*);
    //Handle Input To Prompt
    void handle_input();
};

#endif // LUAPROMPT_H
