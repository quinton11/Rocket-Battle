#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "..\VectorMath\Vector2d.h"

class Bullet : public GameEntity
{
public:
    Bullet(float sx,float sy,Vector2d d,bool from);  // Constructor
    Bullet();
    ~Bullet(); // Destructor

private:
    SDL_FRect rect; // holds bullet position and size
    float speed=30.0f;    // how fast it changes position
    Vector2d direction;
    bool from;

public:
    void update(double dt);
    void render(SDL_Renderer *r, SDL_Texture *t, double dt);
    void hit();
    bool collision(const int wW,const int wH);
};