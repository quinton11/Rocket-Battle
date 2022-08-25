#include "BulletManager.h"

BulletManager *BulletManager::bminstance = NULL;

BulletManager *BulletManager::getBMInstance()
{
    // instantiate bullet manager
    // and return
    if (bminstance == NULL)
        bminstance = new BulletManager();

    return bminstance;
}

void BulletManager::release()
{
    delete bminstance;
    bminstance = NULL;
}

BulletManager::~BulletManager()
{
    //
}

void BulletManager::update()
{
    // loop through list of bullets
    // update each position
    for (std::list<Bullet *>::iterator it = bullets.begin(); it != bullets.end();)
    {
        // update position
        // check if its out of bounds, if yes delete bullet pointer
        // and pop from list

        // if rocket bullet, Check if its collided with an enemy ship
        // If collided, call the collision manager which returns the ship
        // it collided with enemy ship,call enemy ship takehit function
        // which reduces enemy hp
        // perform some collision animation
        // some sound effects
    }
}