#pragma once
#include "SDL.h"
#include "Bullet.h"
#include "Enemy.h"
#include <list>
#include "Rocket.h"
#include <vector>
#include <memory>
#include "..\Utils\CustomEnums.h"

struct BulletTypes
{
    SDL_Texture *text;
    CustomEnums::BulletT type;
};

class BulletManager
{
private:
    static BulletManager *bminstance;
    BulletTypes reg;
    BulletTypes sniper;
    BulletTypes kb;
    int max = 10;
    int shot = 0;
    bool stall = false; // Control shooting

public:
    std::list<Bullet *> all;
    std::list<Enemy *> *allE;

private:
    void update(SDL_Renderer *r,double dt, const int wW, const int wH); // loop through bullet list and update each bullet position
    BulletManager();                                                                     // constructor
    ~BulletManager();                                                                    // Destructor

public:
    static BulletManager *getBMInstance(); // get instance of bullet manager
    static void release();                 // Instance Released at end of game
    void clearBullets();
    void setTextures(SDL_Texture *rtext, SDL_Texture *riftext, SDL_Texture *wvtext);
    void setEnemyList(std::list<Enemy *> &aE);
    bool checkCollision(Bullet *b);
    void render(SDL_Renderer *r, double dt, const int wW, const int wH); // Render bullets
    void makeBullet(float cx, float cy, float angle, bool playerShot);                   // make bullet takes in a rocket pointer and  instantiates a new bullet
    // into the bullets list
    void stallShooting(bool check);
    bool isStalled();
};