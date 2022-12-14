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

void BulletManager::setEnemyList(std::list<Enemy *> &aE)
{
    allE = &aE;
    // std::cout << allE->size() << std::endl;
};

void BulletManager::setTextures(SDL_Texture *rtext, SDL_Texture *riftext, SDL_Texture *kbtext)
{
    reg.text = rtext;
    reg.type = CustomEnums::BulletT::RegularB;

    sniper.text = riftext;
    sniper.type = CustomEnums::BulletT::Rifle;

    kb.text = kbtext;
    kb.type = CustomEnums::BulletT::Kaboom;
}

bool BulletManager::checkCollision(Bullet *b)
{
    // collision bool
    bool collided = false;
    // std::cout << "Size of enemy: " << (allE)->size();
    for (std::list<Enemy *>::iterator ene = (*allE).begin(); ene != (*allE).end(); ene++)
    {
        // std::cout << "Size of enemy: " << (allE)->size();

        if (b->collision((*ene)->rect) && b->from)
        {
            CustomEnums::Entity a = CustomEnums::Entity::Bullet;
            collided = true;
            (*ene)->takeHit(a);
            // std::cout << "Bullet Collided with enemy ship" << std::endl;
            //   call enemy takehit function
        }

        // if(b->collision(rocke))
        /* check if bullet collided with rocket, if yes,call bullet hit function */
        if (!b->from && b->collision(player->rect))
        {
            // bullet shot by enemy
            // std::cout << "Collided with rocket!" << std::endl;
            CustomEnums::Entity a = CustomEnums::Entity::Bullet;
            collided = true;
            player->takeHit(a);
        }
    }
    return collided;
}

void BulletManager::setRocket(Rocket &r)
{
    // std::cout << "In" << std::endl;
    player = &r;
    // std::cout << "After" << std::endl;
}

void BulletManager::makeBullet(float cx, float cy, float angle, bool playerShot)
{
    Bullet *bullet = new Bullet(cx, cy, angle, playerShot);

    all.push_back(bullet);
};

void BulletManager::stallShooting(bool check)
{
    stall = check;
}

bool BulletManager::isStalled()
{
    return stall;
}

void BulletManager::clearBullets()
{
    for (std::list<Bullet *>::iterator bullet = all.begin(); bullet != all.end();)
    {
        delete (*bullet);
        all.erase(bullet++);
    }
}
void BulletManager::update(SDL_Renderer *r, double dt, const int wW, const int wH)
{
    // std::unique_ptr<Bullet> b;
    //  Bullet *temp;
    // std::cout << allE->size() << std::endl;
    bool collideScreen;
    bool collideEntity;
    for (std::list<Bullet *>::iterator bullet = all.begin(); bullet != all.end();)
    {
        (*bullet)->render(r, reg.text, dt);
        collideScreen = (*bullet)->collideScreen(wW, wH);
        collideEntity = checkCollision((*bullet)); // Entity Collision
        // collide
        if (collideScreen || collideEntity)
        {
            delete (*bullet);
            all.erase(bullet++); // remove from the list and take next
            // collideEntity = false;
        }
        else
        {
            ++bullet; // take next object
            // collideEntity = false;
        }
    }
}

void BulletManager::render(SDL_Renderer *r, double dt, const int wW, const int wH)
{
    update(r, dt, wW, wH);
}