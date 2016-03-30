#include "LuaPrompt.h"
#include "lua.h"

extern lua_State *L;
extern SDL_Event event;

SDL_Surface* Prompt;
LuaPrompt::LuaPrompt()
{
    str = "";
    font2 = TTF_OpenFont("/Users/martindionisi/Desktop/openworld/openworld/arial.ttf",20);

}
//Lua Prompt Destructor
LuaPrompt::~LuaPrompt()
{

}

//Lua Prompt Update Text/Render Function
void LuaPrompt::update(SDL_Surface* screen)
{

    if(PromptActive == true)
    {
        if(Prompt != NULL)
        {
            SDL_Rect rect;
            rect.x = 10;
            rect.y = 300;
            rect.w =100;
            rect.h = 100;
            SDL_Texture *txt = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(NULL)),Prompt);
            SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(NULL)), txt, NULL,&rect);
        }

    }

}
void LuaPrompt::handle_input()
{
    //SDL_Enable( SDL_ENABLE );
    if (event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.mod == 0x09){
            if(PromptActive)
                PromptActive = false;
            else
                PromptActive = true;
        }

        if( event.key.keysym.mod == (Uint16)' ' )
        {
            str += (char)event.key.keysym.mod;
        }
        else if( ( event.key.keysym.mod >= (Uint16)'0' ) && ( event.key.keysym.mod <= (Uint16)'9' ) )
        {
            str += (char)event.key.keysym.mod;
        }
        else if( ( event.key.keysym.mod >= (Uint16)'A' ) && ( event.key.keysym.mod <= (Uint16)'Z' ) )
        {
            str += (char)event.key.keysym.mod;
        }
        else if( ( event.key.keysym.mod >= (Uint16)'a' ) && ( event.key.keysym.mod <= (Uint16)'z' ) )
        {
            str += (char)event.key.keysym.mod;
        }
        else if( event.key.keysym.mod == 0x0028 || event.key.keysym.mod == 0x0029 || event.key.keysym.mod == 0x002C || event.key.keysym.mod == 0x0022 || event.key.keysym.mod == 0x002F || event.key.keysym.mod == 0x002B || event.key.keysym.mod == 0x002D || event.key.keysym.mod == 0x002E || event.key.keysym.mod == 0x003D || event.key.keysym.mod == 0x003A)
        {
            str += (char)event.key.keysym.mod;
        }
        

        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            str.erase(str.length()-1);
        }

        if ( event.key.keysym.sym == SDLK_RETURN)
        {
            int ret = luaL_dostring(L,str.c_str());
            if(ret != 0)
            {
                const char *out = lua_tostring(L,-1);
                lua_pop(L,1);
            }
            str = "";
        }
        if(event.key.keysym.sym == SDLK_LSHIFT){
            str += "\n";
            
        }
        
        Prompt = TTF_RenderText_Shaded(font2,str.c_str(),green, {0,0,0});
        
        

    }
}
