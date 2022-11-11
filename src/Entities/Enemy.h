#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "Rocket.h"

// Enemy Class. Describes an enemy ship
// Implements GameEntity
class Enemy : public GameEntity
{
public:
    Enemy(int x,int y);
    ~Enemy();

private:
    SDL_FRect rect;         // describes position of ship
    float min_dist = 50.0f; // If distance from rocket is less than this stop.
    int attack_count = 5;   // number of attacks ship has till reload
    double angle = 0.0f;
    float degtorad = 0.017453f;
    float speed = 30.0f;
    float max_dist = 50.0f; // If distance from rocket is greater than this move.
    float rot_speed = 20.0f;
    float aimmag = 30.0f;

public:
    void
    update(Rocket rocket, double dt);
    void angleCheck();
    bool lifeEmpty();
    void angleCalc(Rocket rocket, double dt);
    void rocketAim(Rocket rocket, float &normy, float &normx);
    void render(SDL_Renderer *renderer, SDL_Texture *texture, Rocket rocket, double dt);
};

/*
    Enemy ship should move in direction of rocket
    Enemy ship should move till a min distance between ship
    Enemy ship attacks(shoots) periodically
 */