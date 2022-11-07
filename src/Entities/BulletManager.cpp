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

void BulletManager::makeBullet(float cx, float cy, Vector2d dir, bool playerShot)
{
    std::cout << "Bullet shot: " << shot << std::endl;
    Bullet bullet = Bullet(cx, cy, dir, playerShot);
    std::cout << "Created" << std::endl;
    std::cout << "Bullet created: " << shot << std::endl;
    //bullets.insert(bullets.end(), bullet);
    //bullets.push_back(bullet);
    bullets[shot]= bullet;
    shot+=1;
    std::cout << "Bullet Inserted: " << shot << std::endl;
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

    for (int i=0;i<shot;i++){
        //bullets[i]
        if (bullets[i].collision(wW, wH))
        {
            //bullets.remove(&it);
            //std::remove(std::begin(bullets),std::end(bullets),bullets[i]);
            std::cout<<"Collide";
        }
        else
        {
            bullets[i].render(r, t, dt);
        }
    }
    // loop through list of bullets
    // update each position
    /* for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
    {
        // if rocket bullet, Check if its collided with an enemy ship
        // If collided, call the collision manager which returns the ship
        // if bullet x is greater than window width or less than o or bullet y is
        // greater than window height or less than 0 then we remove bullet from list
        if (it->collision(wW, wH))
        {
            //bullets.remove(&it);
            bullets.erase(it);
        }
        else
        {
            it->render(r, t, dt);
        }

        // it collided with enemy ship,call enemy ship takehit function
        // which reduces enemy hp
        // perform some collision animation
        // some sound effects
        // update position
        // check if its out of bounds, if yes delete bullet pointer
        // and pop from list
    } */
}

void BulletManager::render(SDL_Renderer *r, SDL_Texture *t, double dt, const int wW, const int wH)
{
    update(r, t, dt, wW, wH);
}