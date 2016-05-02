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
    int xs,ys;
    int tw,th;
    int amt;
    SDL_Rect clip[100];
    
    public:
    
    cTile(int w,int h);
    void LoadSheet(const char*file);
    void LoadMap(const char* filename);
    void RenderMap(SDL_Surface *tiles[]);
    void RenderLayer(int layer);
    
};
