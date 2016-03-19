#include "Tile.h"

extern SDL_Rect camera;
extern SDL_Surface *screen;

cTile::cTile()
{
    
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

void cTile::RenderLayer(SDL_Surface *tiles[],int ln)
{
    for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
		    SDL_Rect rect;
		    rect.x = i*tiles[0]->w - camera.x;
		    rect.y = j*tiles[0]->h - camera.y;
                SDL_BlitSurface(tiles[layer[i][j][ln]],NULL,screen,&rect);
		}
	}
}
