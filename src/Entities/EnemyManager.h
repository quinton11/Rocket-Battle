#pragma once
#include "SDL.h"
#include "Enemy.h"
#include <list>

class EnemyManager
{
private:
    EnemyManager(int ScreenW, int ScreenH); // Constructor
    ~EnemyManager();                        // Destructor

public:
    std::list<Enemy> enemyships; // hold list of enemy ships
    int max_ships;

public:
    // Loop through list of enemy ships to render each of them
    // Ships for now would have the same look
    void render(SDL_Renderer *renderer, SDL_Texture *texture, double dt);

    // Set each enemy ship starting position randomly within the bounds of screen
    // returns an SDL_FRect with its start position calculated randomly
    SDL_FRect randomSpawn(int ScreenW, int ScreenH);

    // Function to check list of enemy ships for their life.
    // If life is empty then delete ship
    bool checkLife(Enemy &ship);
};