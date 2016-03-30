#include <fstream>

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class cTile
{
    private:
    
    int mapSizeX,mapSizeY;
    int ***layer = NULL;
    SDL_Texture *txt;
    int LoadCounterX,LoadCounterY;
    bool once;
    
    public:
    
    cTile();
    void LoadMap(const char* filename);
    void RenderMap(SDL_Surface *tiles[]);
    void RenderLayer(SDL_Texture *tiles[],int layer);
    
};
