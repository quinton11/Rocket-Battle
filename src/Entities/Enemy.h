#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "Rocket.h"

// Enemy Class. Describes an enemy ship
// Implements GameEntity
class Enemy : public GameEntity
{
public:
    Enemy();
    ~Enemy();

private:
    SDL_FRect rect; // describes position of ship
    float min_dist = 10.0;
    int attack_count = 5; // number of attacks ship has till reload
    float angle;

public:
    void update(Rocket *rocket, double dt);
    void render(SDL_Renderer *renderer, SDL_Texture *texture, Rocket *rocket, double dt);
};

/*
    Enemy ship should move in direction of rocket
    Enemy ship should move till a min distance between ship
    Enemy ship attacks(shoots) periodically
 */