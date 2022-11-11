#include "EnemyManager.h"
#include <cstdlib>
#include "time.h"

EnemyManager::EnemyManager()
{
    srand(time(NULL));
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

void EnemyManager::spawn(int x,int y)
{
    Enemy *ship = new Enemy(x,y);
    enemyships.push_back(ship);
}

void EnemyManager::render(SDL_Renderer *renderer, SDL_Texture *texture, Rocket rocket, double dt, int ScreenW, int ScreenH)
{
    // Check length of enemy ship list(number of enemy ships on screen)
    int length = enemyships.size();

    // Generate random number less than 5
    int random = rand() % 5 + 1;
    // if random number is greater than number of ships
    // if number of ships is less than 2 spawn a ship
    bool spawn = (random > length) || (length < 2);
    if (spawn)
    {
        randomSpawn(ScreenW, ScreenH);
    }

    for (std::list<Enemy *>::iterator enemy = enemyships.begin(); enemy != enemyships.end();)
    {
        // render ship with its position
        (*enemy)->render(renderer, texture, rocket, dt);
        // Check if enemyship life is empty
        // if empty, delete from list and move to next iteration
        if ((*enemy)->lifeEmpty())
        {
            delete (*enemy);
            enemyships.erase(enemy++);
        }
        else
        {
            ++enemy;
        }
    }

    //  Each enemy ship will also have to call the update functions
    //  Edit enemy ship update function to take in copy of enemy ship position
    //  update functions will take note of Rocket's position and move accordingly
    //   loop through list of enemy ships and per their position,
    //   render them on screen
}

bool EnemyManager::checkLife(Enemy &ship)
{
    // Check if enemy ship life is empty
    // If yes, pop from list of enemy ships
}