#include "LuaPrompt.h"
#include "lua.h"


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
            SDL_QueryTexture(txt, NULL, NULL, &rect.w, &rect.h);
            
            //rect.h = 30;
            
            SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)), txt, NULL,&rect);
        }

    }

}

void LuaPrompt::runScrip(lua_State *L)
{
        int ret = luaL_dostring(L,strcpy.c_str());
        if(ret != 0)
        {
            const char *out = lua_tostring(L,-1);
            std::cout << out << std::endl;
            lua_pop(L,1);
        }
        str = "";
}

void LuaPrompt::HandleInput(SDL_Event event,lua_State *L)
{
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB){
        if(PromptActive)
            PromptActive = false;
        else
            PromptActive = true;
    }
    //SDL_Enable( SDL_ENABLE );
    if(PromptActive){
        if (event.type == SDL_KEYDOWN)
        {
            if( event.key.keysym.sym == (Uint16)' ' )
            {
                str += (char)event.key.keysym.sym;
            }
            else if( ( event.key.keysym.sym >= (Uint16)'0' ) && ( event.key.keysym.sym <= (Uint16)'9' ) )
            {
                if(!SDL_GetModState() & KMOD_SHIFT)
                    str += (char)event.key.keysym.sym;
            }
            
            else if( event.key.keysym.sym == 0x0028 || event.key.keysym.sym == 0x0029 || event.key.keysym.sym == 0x002C || event.key.keysym.sym == 0x0022 || event.key.keysym.sym == 0x002F || event.key.keysym.sym == 0x002B || event.key.keysym.sym == 0x002D || event.key.keysym.sym == 0x002E || event.key.keysym.sym == 0x003D || event.key.keysym.sym == 0x003A)
            {
                if(!SDL_GetModState() & KMOD_SHIFT)
                    str += (char)event.key.keysym.sym;
            }
            else if( ( event.key.keysym.sym >= (Uint16)'a' ) && ( event.key.keysym.sym <= (Uint16)'z' ) )
            {
                if(!SDL_GetModState() & KMOD_SHIFT)
                    str += (char)event.key.keysym.sym;
                // else
                
            }
            
            
            if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
            {
                str.erase(str.length()-1);
            }
            
            if ( event.key.keysym.sym == SDLK_RETURN)
            {
                strcpy = str;
                runScrip(L);
            }
            if(event.key.keysym.sym == SDLK_LSHIFT){
                str += "\n";
                
            }
            
            
            Prompt = TTF_RenderText_Blended_Wrapped(font2,str.c_str(),{0,0,0},800);
            txt = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)),Prompt);
            
            
            
        }
        if( event.type == SDL_TEXTINPUT )
        {
            if(SDL_GetModState() && KMOD_CAPS)
                str += event.text.text;
            
            Prompt = TTF_RenderText_Blended_Wrapped(font2,str.c_str(),{0,0,0},800);
            txt = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)),Prompt);
            
        }
    }
}
