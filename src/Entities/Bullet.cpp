#include "Bullet.h"

Bullet::Bullet(float sx,float sy,Vector2d d,bool f)
{
    // Instantiate bullet object
    from=f;
    rect.x=sx;
    rect.y=sy;
    rect.w=8;
    rect.h=15;
    direction=d;
}

Bullet::Bullet(){}

Bullet::~Bullet()
{
    // Delete bullet object
    // Called in hit function
}

bool Bullet::collision(const int wW,const int wH)
{
    if (((rect.x+rect.w)>=wW || (rect.x<=0)) ||  ((rect.y+rect.h)>=wH || (rect.y<=0)))
    {
        return true;
    }
    return false;
}

void Bullet::update(double dt)
{
    // update bullet position as time moves on
    rect.x+=speed*direction.getx();
    rect.y+=speed*direction.gety();
}

void Bullet::render(SDL_Renderer *r, SDL_Texture *t, double dt)
{
    //Update position
    update(dt);
    // render bullet on screen
    SDL_RenderCopyF(r,t,nullptr,&rect);
}