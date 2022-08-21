#include "Enemy.h"

void Enemy::update(Rocket *rocket, double dt)
{
    // takes in deltatime and updates
    // rocket position
}

void Enemy::render(SDL_Renderer *renderer, SDL_Texture *texture, Rocket *rocket, double dt)
{
    update(rocket, dt); // Takes in reference to rocket ship for knowledge on its position
    // render function for enemy ships
    SDL_RenderCopyExF(renderer, texture, nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
}

// angle and position should change based on rocket position

Enemy::Enemy()
{
    rect.x = 20;
    rect.y = 180;
    rect.w = 60;
    rect.h = 45;
}

Enemy::~Enemy() {}

/*
    For enemy ships manager,
    have a function which generates random places to spawn
    ships at
    Enemy manager class on instantiating should set the
    max number of ships on screen and rendering each of them per
    frame. The enemy ships would hold their own rendering and update
    function.
    From where the enemy ship starts from and the angle it starts at
    is decided by the enemy manager.
 */

/*
    TODO:
    Implement enemy update and render functions
    Implement enemy Manager functions
    Test implementations
    Set textures for enemy ships
    Move texture instantiation and creation to class constructor
 */