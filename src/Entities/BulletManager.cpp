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
    std::cout << "Bullet shot: " << shot << std::endl;
    std::cout << "In make bullet with centres: " << cx << "," << cy << std::endl;
    Bullet *bullet = new Bullet(cx, cy, angle, playerShot);
    // Bullet(cx, cy, angle, playerShot);
    std::cout << "Created" << std::endl;
    std::cout << "Bullet created: " << shot << std::endl;
    // bullets.insert(bullets.end(), bullet);
    // bullets.push_back(bullet);
    // bullets[shot]= bullet;
    all.push_back(bullet);
    shot += 1;
    std::cout << "Bullet Inserted: " << shot << std::endl;
    std::cout << "After insertion" << bullet->rect.x << "," << bullet->rect.y << std::endl;
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
    for (std::list<Bullet *>::iterator it = all.begin(); it != all.end();)
    {
        (*it)->render(r, t, dt);
        if ((*it)->collision(wW, wH))
        {
            delete (*it);
            all.erase(it++); // remove from the list and take next
        }
        else
        {
            ++it; // take next object
        }
    }
    /* for ( auto &b : all)
    {
        std::cout << "In loop: " << b->rect.w << "," << b->rect.h << std::endl;
        std::cout << b->from << std::endl;
        b->render(r, t, dt);

        if (b->collision(wW, wH))
        {
            std::cout << "Collide" << std::endl;
            delete &b;
            //all.erase(std::remove(all.begin(),all.end(),b));
        }
    } */
}

void BulletManager::render(SDL_Renderer *r, SDL_Texture *t, double dt, const int wW, const int wH)
{
    update(r, t, dt, wW, wH);
}