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

BulletManager::BulletManager()
{
    //
}

BulletManager::~BulletManager()
{
    //
}

void BulletManager::makeBullet(float cx, float cy, float angle, bool playerShot)
{
    //std::cout << "Bullet shot: " << shot << std::endl;
    //std::cout << "In make bullet with centres: " << cx << "," << cy << std::endl;
    Bullet *bullet = new Bullet(cx, cy, angle, playerShot);
    
    //std::cout << "Created" << std::endl;
    //std::cout << "Bullet created: " << shot << std::endl;
    
    all.push_back(bullet);
    //shot += 1;
    //std::cout << "Bullet Inserted: " << shot << std::endl;
    //std::cout << "After insertion" << bullet->rect.x << "," << bullet->rect.y << std::endl;
};

void BulletManager::stallShooting(bool check)
{
    stall = check;
}

bool BulletManager::isStalled()
{
    return stall;
}
void BulletManager::update(SDL_Renderer *r, SDL_Texture *t, double dt, const int wW, const int wH)
{
    // std::unique_ptr<Bullet> b;
    //  Bullet *temp;
    bool collideScreen;
    bool collideEntity;
    for (std::list<Bullet *>::iterator bullet = all.begin(); bullet != all.end();)
    {
        (*bullet)->render(r, t, dt);
        collideScreen = (*bullet)->collideScreen(wW, wH);
        //collide
        if (collideScreen)
        {
            delete (*bullet);
            all.erase(bullet++); // remove from the list and take next
        }
        else
        {
            ++bullet; // take next object
        }
    }
}

void BulletManager::render(SDL_Renderer *r, SDL_Texture *t, double dt, const int wW, const int wH)
{
    update(r, t, dt, wW, wH);
}