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

void EnemyManager::randomSpawn(int spawnAmt, int ScreenW, int ScreenH)
{
    // At enemy Manager class instantiation, set create and set
    // enemy ship spawning location
    // return enemy ship
    int randx = 0;
    int randy = 0;
    for (int i = 0; i < spawnAmt; i++)
    {
        randx = rand() % ScreenW;
        randy = rand() % ScreenH;
        spawn(randx, randy);
    }
}

void EnemyManager::InitSpawn(int ScreenW, int ScreenH)
{
    // loop max times and spawn ships randomly on screen
    int randx = 0;
    int randy = 0;
    for (int i = 0; i < max; i++)
    {
        // generate random x and y
        // use to spawn enemy ship and add to list
        randx = rand() % ScreenW;
        randy = rand() % ScreenH;
        spawn(randx, randy);
    }
}

void EnemyManager::spawn(int x, int y)
{
    Enemy *ship = new Enemy(x, y);
    enemyships.push_back(ship);
}

void EnemyManager::render(SDL_Renderer *renderer, SDL_Texture *texture, Rocket rocket, double dt, int ScreenW, int ScreenH)
{
    // Check length of enemy ship list(number of enemy ships on screen)
    int length = enemyships.size();
    // std::cout << "Enemy Ships size" << std::endl;

    if (length == 0)
    {
        // If enemy ships are zero,at the start of game

        InitSpawn(ScreenW, ScreenH);
        // std::cout << "Init Spawn" << std::endl;
    }

    // Generate random number less than 5
    int random = rand() % 5 + 1;
    // determines number of remaining enemy ships needed to trigger respawning
    int randid = rand() % 2 + 1;
    // if random number is greater than number of ships
    // if number of ships is less than 2 spawn a ship

    // NB:: Fix spawning mechanism
    bool spawn = (random > length) && (length <= randid);
    if (spawn)
    {
        int spawnamt = random - length;
        randomSpawn(spawnamt, ScreenW, ScreenH);
        // std::cout << "Random Spawn" << std::endl;
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