#include "Bullet.h"

Bullet::Bullet(float sx, float sy, float ang, bool f)
{
    // Instantiate bullet object
    // std::cout<<"Direction vector: "<<d.getx()<<","<<d.gety()<<std::endl;
    // std::cout <<"In make bullet constructor with centres: "<< sx << "," << sy << std::endl;
    from = f;
    rect.x = sx - 4;
    rect.y = sy;
    rect.w = 8;
    rect.h = 25;
    angle = ang;
    deltax = speed * sin(angle * degtorad);
    deltay = speed * (-1 * cos(angle * degtorad));
}

Bullet::Bullet()
{
    rect.w = 8;
    rect.h = 15;
}

Bullet::~Bullet()
{
    // Delete bullet object
    // Called in hit function
}

bool Bullet::collision(SDL_FRect other)
{
    // Check for collision with other rect
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    // Sides of Bullet rect
    leftA = rect.x;
    rightA = rect.x + rect.w;
    topA = rect.y;
    bottomA = rect.y + rect.h;

    // Sides of other rect
    leftB = other.x;
    rightB = other.x + other.w;
    topB = other.y;
    bottomB = other.y + other.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}

bool Bullet::collideScreen(const int wW, const int wH)
{
    // std::cout <<"In collission: "<< rect.x << "," << rect.y << std::endl;
    // std::cout<<"Angle: "<<angle<<" Width& height"<<rect.w<<","<<rect.y<<std::endl;
    // std::cout<<"Deltas: "<<deltax<<","<<deltay<<std::endl;
    float rectsidex = rect.x + rect.w;
    float rectsidey = rect.y + rect.h;
    // std::cout<<rectsidex<<","<<rectsidey<<std::endl;
    // std::cout<<"Window: "<<wW<<","<<wH<<std::endl;
    if ((rectsidex >= wW || (rect.x <= 0)) || (rectsidey >= wH || (rect.y <= 0)))
    {
        return true;
    }
    return false;
}

void Bullet::update(double dt)
{
    // update bullet position as time moves on
    deltax = speed * (dt / 100.f) * sin(angle * degtorad);
    deltay = speed * (dt / 100.0f) * (-1 * cos(angle * degtorad));
    rect.x = rect.x + deltax;
    rect.y = rect.y + deltay;
}

void Bullet::render(SDL_Renderer *r, SDL_Texture *t, double dt)
{
    // Update position
    // std::cout<<"Bullet Render"<<std::endl;
    update(dt);
    // render bullet on screen
    // std::cout<<"After update"<<std::endl;
    SDL_RenderCopyExF(r, t, nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
    // std::cout<<"After rendercopy"<<std::endl;
}