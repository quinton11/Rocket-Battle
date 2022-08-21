#include "EnemyManager.h"

EnemyManager::EnemyManager(int ScreenW, int ScreenH)
{
    // Using screen width and height, set x and y starting
    // position of Enemy ship, store result in list
}

EnemyManager::~EnemyManager()
{
    // Destructor
    // Release any pointers used here
}

SDL_FRect EnemyManager::randomSpawn(int ScreenW, int ScreenH)
{
    // At enemy Manager class instantiation, set create and set
    // enemy ship spawning location
    // return enemy ship
}

void EnemyManager::render(SDL_Renderer *renderer, SDL_Texture *texture, double dt)
{
    // Each enemy ship will also have to call the update functions
    // Edit enemy ship update function to take in copy of enemy ship position
    // update functions will take note of Rocket's position and move accordingly
    //  loop through list of enemy ships and per their position,
    //  render them on screen
}

bool EnemyManager::checkLife(Enemy &ship)
{
    // Check if enemy ship life is empty
    // If yes, pop from list of enemy ships
}