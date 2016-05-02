#include "Tile.h"
#include "Physics.h"

Physics physics;

extern SDL_Rect camera;

cTile::cTile(int w,int h)
{
    tw = w;
    th = h;
}

void cTile::LoadSheet(const char *file)
{
    SDL_Surface *sur =  SDL_LoadBMP(file);
    txt = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)), sur);
    xs = sur->w/tw;
    ys = sur->h/th;
    SDL_FreeSurface(sur);
    int cnt = 0;
    for(int i = 0;i < ys;i++)
    {
        for(int j = 0;j < xs;j++)
        {
            clip[cnt] = {tw*j,th*i,tw,th};
            cnt++;
        }
    }
}

void cTile::LoadMap(const char *filename)
{
    LoadCounterX = 0;
    LoadCounterY = 0;
    int layers = 0;
    ifstream openfile (filename);
    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            if(once == false)
            {
                openfile >> mapSizeX >> mapSizeY >> layers;
                layer = new int **[mapSizeX];
                for(int i = 0;i < mapSizeX;i++)
                {
                    layer[i] = new int *[mapSizeY];
                    for(int j = 0; j < mapSizeY;j++)
                    {
                        layer[i][j] = new int[layers];
                    }
                }
                once = true;
            }
            
            for(int i = 0 ; i < layers; i++)
            {
                for(int j = 0; j < mapSizeY ;j++)
                {
                    for(int g = 0; g < mapSizeX; g++)
                    {
                        openfile >> layer[g][j][i];
                    }
                }
            }
            
        }
    }
}

void cTile::RenderLayer(int ln)
{
    float lif = 0.6;
    for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
		    SDL_Rect rect;
		    rect.x = i*tw - camera.x;
		    rect.y = j*th - camera.y;
            rect.w = tw;
            rect.h = th;
            SDL_SetTextureColorMod(txt,255*lif,255*lif,255*lif);
            SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),txt,&clip[layer[i][j][ln]],&rect);
		}
	}
}
