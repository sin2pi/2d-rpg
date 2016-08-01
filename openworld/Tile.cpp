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
    SDL_SetColorKey(sur,SDL_TRUE,SDL_MapRGB(sur->format,0,255,255));
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

void cTile::RenderLayer(int ln,float amb,light l)
{
    for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
		    SDL_Rect rect;
		    rect.x = i*tw - camera.x;
		    rect.y = j*th - camera.y;
            rect.w = tw;
            rect.h = th;
            
            if(Physics::circlecol(&rect, 600-camera.x, 700-camera.y, 4000))
            {
                float a = l.resolvePointLight(600-camera.x, 700-camera.y,rect.x, rect.y);
                float c1 = a*255;
                float c2 = a*255;
                float c3 = a*255;
                if(c1 > 255)
                    c1 = 255;
                if(c2 > 255)
                    c2 = 255;
                if(c3 > 255)
                    c3 = 255;
                SDL_SetTextureColorMod(txt,c1,c2,c3);
            }
            else SDL_SetTextureColorMod(txt,255*amb,255*amb,255*amb);
            
            SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),txt,&clip[layer[i][j][ln]],&rect);
		}
	}
}
