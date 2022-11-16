#pragma once
#include "SDL.h"
#include "Enemy.h"
#include <list>
#include "Rocket.h"
#include "..\Utils\CustomEnums.h"

struct EnemyTypes
{
    SDL_Texture *text;
    CustomEnums::EnemyT etype;
};
class EnemyManager
{
private:
    int max = 5;
    int deviation = 5;
    EnemyTypes reg = EnemyTypes();
    EnemyTypes sbane = EnemyTypes();
    EnemyTypes wv = EnemyTypes();

public:
    EnemyManager(); // Constructor
    EnemyManager(SDL_Texture *r, SDL_Texture *s, SDL_Texture *w);
    ~EnemyManager();               // Destructor
    std::list<Enemy *> enemyships; // hold list of enemy ships
    int max_ships;
    CustomEnums::Spawn positions[4] = {CustomEnums::Spawn::Top, CustomEnums::Spawn::Bottom, CustomEnums::Spawn::Right, CustomEnums::Spawn::Left};

public:
    // Loop through list of enemy ships to render each of them
    // Ships for now would have the same look
    void render(SDL_Renderer *renderer, Rocket rocket, double dt, int ScreenW, int ScreenH);
    void spawn(CustomEnums::Spawn pos, int ScreenW, int ScreenH);
    void InitSpawn(int ScreenW, int ScreenH);

    // Set each enemy ship starting position randomly within the bounds of screen
    // returns an SDL_FRect with its start position calculated randomly
    void randomSpawn(int spawnAmt, int ScreenW, int ScreenH);

    // Function to check list of enemy ships for their life.
    // If life is empty then delete ship
    bool checkLife(Enemy &ship);
};
