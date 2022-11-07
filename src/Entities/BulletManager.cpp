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

BulletManager::BulletManager() {
    //
}

BulletManager::~BulletManager()
{
    //
}

void BulletManager::makeBullet(float cx, float cy, float angle, bool playerShot)
{
    std::cout << "Bullet shot: " << shot << std::endl;
	std::cout <<"In make bullet with centres: "<< cx << "," << cy << std::endl;
    Bullet temp= Bullet(cx, cy, angle, playerShot);
    Bullet bullet = temp;
    std::cout << "Created" << std::endl;
    std::cout << "Bullet created: " << shot << std::endl;
    //bullets.insert(bullets.end(), bullet);
    //bullets.push_back(bullet);
    //bullets[shot]= bullet;
    all.push_back(bullet);
    shot+=1;
    std::cout << "Bullet Inserted: " << shot << std::endl;
    std::cout<<"After insertion"<<bullet.rect.x<<","<<bullet.rect.y<<std::endl;
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
    //Bullet *temp;
    for (Bullet b:all){
        std::cout<<"In loop: "<<b.rect.w<<","<<b.rect.h<<std::endl;
        std::cout<<b.from<<std::endl;
        if (b.collision(wW, wH))
        {
            std::cout<<"Collide"<<std::endl;
        }
        else
        {
            b.render(r, t, dt);
        }
    }

}

void BulletManager::render(SDL_Renderer *r, SDL_Texture *t, double dt, const int wW, const int wH)
{
    update(r, t, dt, wW, wH);
}