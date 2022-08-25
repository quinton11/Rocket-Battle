#pragma once
#include "SDL.h"
#include "GameEntity.h"

class Bullet : public GameEntity
{
public:
    Bullet();  // Constructor
    ~Bullet(); // Destructor

private:
    SDL_FRect rect; // holds bullet position and size
    float speed;    // how fast it changes position

public:
    void update(double dt);
    void render(SDL_Renderer *r, SDL_Texture *t, double dt);
    void hit();
};