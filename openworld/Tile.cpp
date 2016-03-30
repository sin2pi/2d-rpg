#include "Tile.h"

extern SDL_Rect camera;

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

void cTile::RenderLayer(SDL_Texture *tiles[],int ln)
{
    for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
		    SDL_Rect rect;
		    rect.x = i*32 - camera.x;
		    rect.y = j*32 - camera.y;
            rect.w = 32;
            rect.h = 32;
            //SDL_DisplayFormat(*tiles);
            
            SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),tiles[layer[i][j][ln]],NULL,&rect);
		}
	}
}
