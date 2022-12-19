#include "EnemyManager.h"
#include <cstdlib>
#include "time.h"

EnemyManager::EnemyManager()
{
    srand(time(NULL));

    // Using screen width and height, set x and y starting
    // position of Enemy ship, store result in list
}

EnemyManager::EnemyManager(SDL_Texture *r, SDL_Texture *s, SDL_Texture *w)
{
    srand(time(NULL));
    // set regular
    reg.text = r;
    reg.etype = CustomEnums::EnemyT::Regular;

    // set space bane
    sbane.text = s;
    sbane.etype = CustomEnums::EnemyT::SpaceBane;

    // set war veteran
    wv.text = w;
    wv.etype = CustomEnums::EnemyT::WarVet;
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
    int random = 0;
    CustomEnums::Spawn pos;
    for (int i = 0; i < spawnAmt; i++)
    {

        random = rand() % 4;
        pos = positions[random];
        spawn(pos, ScreenW, ScreenH);
    }
}

void EnemyManager::InitSpawn(int ScreenW, int ScreenH)
{
    // loop max times and spawn ships randomly on screen
    int random = 0;
    CustomEnums::Spawn pos;
    for (int i = 0; i < max; i++)
    {
        // generate random x and y
        // use to spawn enemy ship and add to list
        /* Spawn ships at random positions around edge of screen */
        // have a list of spawn positions(enums).. then for every iteration
        // generate a random number between the length of the list and 0
        // index the list at the random number and retrieve the spawnposition
        // pass it to spawn function
        random = rand() % 4;
        pos = positions[random];

        // In spawn function, using spawn position and deviation
        // and generating a random position(x or y) we set the random spawn position
        spawn(pos, ScreenW, ScreenH);
    }
}

void EnemyManager::spawn(CustomEnums::Spawn pos, int ScreenW, int ScreenH)
{
    int x = 0;
    int y = 0;

    if (pos == CustomEnums::Spawn::Bottom)
    {
        // Spawn at bottom
        // X is random y is max - deviation
        x = rand() % ScreenW + 1;
        y = ScreenH - deviation;
    }
    else if (pos == CustomEnums::Spawn::Top)
    {
        // Spawn at top
        // X is random y is min+deviation
        x = rand() % ScreenW + 1;
        y = deviation;
    }
    else if (pos == CustomEnums::Spawn::Right)
    {
        // Spawn at right
        //  X is max -deviation and y is random
        x = ScreenW - deviation;
        y = rand() % ScreenH + 1;
    }
    else if (pos == CustomEnums::Spawn::Left)
    {
        // Spawn at left
        // X is min + deviation and y is random
        x = deviation;
        y = rand() % ScreenH + 1;
    }
    Enemy *ship = new Enemy(x, y, CustomEnums::EnemyT::Regular);
    enemyships.push_back(ship);
}

void EnemyManager::clearEShips()
{
    for (std::list<Enemy *>::iterator enemy = enemyships.begin(); enemy != enemyships.end();)
    {
        delete (*enemy);
        enemyships.erase(enemy++);
    }
}

void EnemyManager::render(SDL_Renderer *renderer, BulletManager *bm, Rocket rocket, double dt, int ScreenW, int ScreenH)
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
    EnemyShoot shoot;

    // NB:: Fix spawning mechanism
    bool spawn = (random > length) && (length <= randid);
    if (spawn)
    {
        int spawnamt = random - length;
        randomSpawn(spawnamt, ScreenW, ScreenH);
        // std::cout << "Random Spawn" << std::endl;
    }

    // std::cout << "In enemy loop" << std::endl;
    for (std::list<Enemy *>::iterator enemy = enemyships.begin(); enemy != enemyships.end();)
    {
        // render ship with its position
        (*enemy)->render(renderer, reg.text, rocket, dt);
        // Check if enemyship life is empty
        // if empty, delete from list and move to next iteration

        // check if enemy shot a bullet
        shoot = (*enemy)->attack(rocket);
        if (shoot.shoot)
        {
            float cx = (*enemy)->rect.x + (*enemy)->rect.w / 2;
            float cy = (*enemy)->rect.y + (*enemy)->rect.h / 2;
            bm->makeBullet(cx, cy, (*enemy)->angle, false, shoot.btype);
        }
        if ((*enemy)->lifeEmpty())
        {
            kills += 1;
            // std::cout << "Kills: " << kills << std::endl;
            spawnPowerUp((*enemy)->rect.x, (*enemy)->rect.y);
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

void EnemyManager::setReference(PowerUpManager &pum)
{
    puManager = &pum;
}

void EnemyManager::resetKills()
{
    kills = 0;
}

void EnemyManager::spawnPowerUp(float x, float y)
{
    if (LevelManager::level == CustomEnums::Levels::RegLevel)
    {
        if (kills >= 15)
        {
            // add defence powerup
            // std::cout << "Spawning Defence " << x << ", " << y << std::endl;
            puManager->addPowerUp(CustomEnums::Upgrades::Defence, x, y);
            kills = 0;
        }
        else if (kills % 10 == 0)
        {
            // health
            puManager->addPowerUp(CustomEnums::Upgrades::Health, x, y);
        }
    }
    else if (LevelManager::level == CustomEnums::Levels::BaneLevel)
    {
        // check if user has killed a certain number of bane enemies
        // if yes add power up to puManager
        // when user collects it, he can shoot a specific amount of bane bullets
        // based on his bane power up count
    }
    else if (LevelManager::level == CustomEnums::Levels::VetLevel)
    {
        /* Check if user has killed a certain number of vet enemies
        If yes add power up to pumanager
        when user collects it,he can shoot a specific amount of vet bombs
        based on his vet power up count */
    }

    /* Also fix enemy spawn frequency and entity based on level */
}
