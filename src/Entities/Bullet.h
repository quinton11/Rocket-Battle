#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "..\VectorMath\Vector2d.h"

class Bullet : public GameEntity
{
public:
    Bullet(float sx,float sy,float angle,bool from);  // Constructor
    Bullet();
    ~Bullet(); // Destructor
    SDL_FRect rect; // holds bullet position and size
    bool from;


private:
    float speed=10.0f;    // how fast it changes position
    Vector2d direction;
    float angle=0.f;
    float deltax=0.f;
    float deltay=0.f;
	float degtorad = 0.017453f;


public:
    void update(double dt);
    void render(SDL_Renderer *r, SDL_Texture *t, double dt);
    void hit();
    bool collision(const int wW,const int wH);
};