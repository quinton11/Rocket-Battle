#include "Bullet.h"

Bullet::Bullet()
{
    // Instantiate bullet object
}

Bullet::~Bullet()
{
    // Delete bullet object
    // Called in hit function
}

void Bullet::update(double dt)
{
    // update bullet position as time moves on
}

void Bullet::render(SDL_Renderer *r, SDL_Texture *t, double dt)
{
    // render bullet on screen
}