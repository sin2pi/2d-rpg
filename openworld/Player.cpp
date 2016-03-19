#include "Player.h"

extern bool running;
cPlayer::cPlayer(float x,float y,int w,int h,float xspeed,float yspeed,float acc,const char*file,int nx)
{
    image = SDL_LoadBMP(file);
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xSpeed = xspeed;
    ySpeed = yspeed;
    acceleration = acc;
    ranim = new Animation(0,0,w,h,nx,10);
    lanim = new Animation(0,h,w,h,nx,10);
    SDL_Rect rect = {0,0,static_cast<Uint16>(w),static_cast<Uint16>(h)};
    idle.push_back(new Animation(0,0,w,h,1,10));
    rect = {0,static_cast<Sint16>(h),static_cast<Uint16>(w),static_cast<Uint16>(h)};
    idle.push_back(new Animation(0,h,w,h,1,10));
    SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,255,255));
    idleframe = 0;
}

void cPlayer::Interact(vector<cNpc *> n)
{
    for(int i = 0; i< n.size();i++)
    {
        if(Physics::collision(&box,n.at(i)->getBox()))
        {
            if(dir[1] || dir[3])
            box.x -= xVel;
            if(dir[0] || dir[2])
            box.y -= yVel;
        }
    }
}

void cPlayer::HandleInput(SDL_Event event)
{
    switch(event.type){
        case SDL_QUIT:
            SDL_Quit();
            break;
        case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
            //cout << event.jaxis.value << endl;
            if(event.jaxis.axis == 0){
                if( event.jaxis.value < -3200 )
                {
                    dir[1] = 1;
                    idleframe = 1;
                }

                else if( event.jaxis.value > 3200 )
                {
                    dir[3] = 1;
                    idleframe = 0;
                }
                else
                {
                    dir[1] = 0;
                    dir[3] = 0;
                }
            }
            else if( event.jaxis.axis == 1 )
            {

                if( event.jaxis.value < -3200 )
                {
                    dir[0] = 1;
                }

                else if( event.jaxis.value > 3200)
                {
                    dir[2] = 1;
                }
                else
                {
                    dir[0] = 0;
                    dir[2] = 0;
                }
            }
            
            break;
        case SDL_JOYBUTTONDOWN:  /* Handle Joystick Button Presses */
            if ( event.jbutton.button == 4 )
            {
                
            }
            if ( event.jbutton.button == 5 )
            {

            }
            if ( event.jbutton.button == 2 )
            {
                break;
            }
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
        {
                break;
            case SDLK_UP:
                dir[0] = 1;
                break;
            case SDLK_LEFT:
                dir[1] = 1;
                break;
            case SDLK_DOWN:
                dir[2] = 1;
                break;
            case SDLK_RIGHT:
                dir[3] = 1;
                break;
             case SDLK_ESCAPE:
                running = false;
                break;
                
        }break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
        {
                
            case SDLK_UP:
                dir[0] = 0;
                break;
            case SDLK_LEFT:
                dir[1] = 0;
                idleframe = 1;
                break;
            case SDLK_DOWN:
                dir[2] = 0;
                break;
            case SDLK_RIGHT:
                dir[3] = 0;
                idleframe = 0;
                break;
        }break;
    }
}

void cPlayer::Move()
{
    
    
    if(dir[0] == 1){
        yVel -= acceleration;
        if(yVel < -ySpeed)
            yVel = -ySpeed;
    }

    else if(dir[2] == 1){
        yVel += acceleration;
        if(yVel > ySpeed)
            yVel = ySpeed;
    }

    else{
        if(yVel < 0)
        {
            yVel += acceleration;
            if(yVel > 0.0)
                yVel = 0.0;
    }

    else {
        yVel -= acceleration;
        if(yVel < 0.0)
            yVel = 0.0;
    }

    }


    if(dir[1] == 1){
        xVel -= acceleration;
        if(xVel < -xSpeed)
            xVel = -xSpeed;
    }

    else if(dir[3] == 1){
        xVel += acceleration;
        if(xVel > xSpeed)
            xVel = xSpeed;
    }

    else{
        if(xVel < 0)
        {
            xVel += acceleration;
            if(xVel > 0.0)
                xVel = 0.0;
    }

    else {
        xVel -= acceleration;
        if(xVel < 0.0)
            xVel = 0.0;
    }

    }

    box.x += xVel;
    box.y += yVel;

    /*
    if(box.x + box.w >= 1280)
        box.x -= xVel;
    if(box.y + box.h >= 1280)
        box.y -= yVel;
        */
}

void cPlayer::Grab(SDL_Rect object)
{
    object.x = box.x + box.w /2;
    object.y = box.y + object.h/2;
}

SDL_Rect cPlayer::SetCamera(SDL_Rect cam)
{
    cam.x = ( box.x + box.w / 2 ) - 640 / 2;
    cam.y = ( box.y + box.h / 2 ) - 480 / 2;
    if( cam.x < 0)
    {
        cam.x = 0;
    }
    if(cam.x > 1280 - 640)
    {
        cam.x = 1280 - 640;
    }
    if( cam.y < 0)
    {
        cam.y = 0 ;
    }
    if(cam.y > 1280 - 480)
    {
        cam.y = 1280 - 480;
    }
    return cam;

}

void cPlayer::Render(SDL_Rect camera)
{
    
    SDL_Rect rect = {static_cast<Sint16>(box.x - camera.x), static_cast<Sint16>(box.y - camera.y)};
    
    if(dir[1])
    {
        lanim->RunAnimation(rect,image);
    }
    else if(dir[3])
    {
        ranim->RunAnimation(rect,image);
    }
    else if(dir[0])
    {
        idleframe = 0;
        ranim->RunAnimation(rect,image);
    }
    else if(dir[2])
    {
        idleframe = 0;
        ranim->RunAnimation(rect,image);
    }
    
    else
        idle.at(idleframe)->RunAnimation(rect,image);
    
    //SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&rect);
}
