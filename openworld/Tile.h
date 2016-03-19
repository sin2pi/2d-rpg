#include <fstream>

#include <SDL/SDL.h>
#include <iostream>

using namespace std;

class cTile
{
    private:
    
    int mapSizeX,mapSizeY;
    int ***layer = NULL;
    
    int LoadCounterX,LoadCounterY;
    bool once;
    
    public:
    
    cTile();
    void LoadMap(const char* filename);
    void RenderMap(SDL_Surface *tiles[]);
    void RenderLayer(SDL_Surface *tiles[],int layer);
    
};
