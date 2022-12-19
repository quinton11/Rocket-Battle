#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "Rocket.h"
#include "..\Utils\CustomEnums.h"

// Enemy Class. Describes an enemy ship
// Implements GameEntity

struct EnemyShoot
{
    CustomEnums::BulletT btype;
    bool shoot;
    float speed;
};

class Enemy : public GameEntity
{
public:
    Enemy(int x, int y,CustomEnums::EnemyT type);
    ~Enemy();
    SDL_FRect rect; // describes position of ship
    CustomEnums::EnemyT type;
    double angle = 0.0f;


private:
    float min_dist = 50.0f; // If distance from rocket is less than this stop.
    int attack_count = 5;   // number of attacks ship has till reload
    float degtorad = 0.017453f;
    float speed = 30.0f;
    float stallSpeed = 10.0f;
    float max_dist = 50.0f; // If distance from rocket is greater than this move.
    float rot_speed = 20.0f;
    float aimmag = 30.0f;
    float attackRange = 200.0f;
    int interval=100;
    float health = 10.0f;
    float healthMax = 5.0f;
    float healthPercent =1.0f;

public:
    void update(Rocket rocket, double dt);
    void angleCheck();
    bool lifeEmpty();
    void takeHit(CustomEnums::Entity e);
    bool collision(SDL_FRect other);
    void angleCalc(Rocket rocket, double dt);
    void rocketAim(Rocket rocket, float &normy, float &normx);
    void render(SDL_Renderer *renderer, SDL_Texture *texture, Rocket rocket, double dt);
    void renderHealthBar(SDL_Renderer *renderer);
    void calcHealthP();
    EnemyShoot attack(Rocket rocket);
};

/*
    Enemy ship should move in direction of rocket
    Enemy ship should move till a min distance between ship
    Enemy ship attacks(shoots) periodically
 */