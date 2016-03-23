//
//  listManager.h
//  openworld
//
//  Created by martin dionisi on 15/2/16.
//  Copyright (c) 2016 martin dionisi. All rights reserved.
//

#ifndef openworld_listManager_h
#define openworld_listManager_h

#include <fstream>

using namespace std;

void LoadNpcList(vector<cNpc*>*list,const char *file)
{
    ifstream openfile(file);
    float x,y,w,h,xv,yv,hp;
    int rep;
    int nx;
    string f;
    const char *c;
    
    while(!openfile.eof())
    {
        openfile >> x >> y >> w >> h >> xv >> yv >> hp >> rep >> f >> nx;
        c = f.c_str();
        list->push_back(new cNpc(x,y,w,h,xv,yv,hp,10,rep,c,nx));
    }
}

void LoadItemList(vector<cItem*>*list,const char *file)
{
    ifstream openfile(file);
    float x,y,w,h,id;
    string f;
    const char *c;
    while(!openfile.eof())
    {
        openfile >> x >> y >> w >> h >> f >> id;
        c = f.c_str();
        list->push_back(new cItem(x,y,w,h,c,id));
    }
}

#endif
