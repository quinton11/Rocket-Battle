#pragma once
#include "SDL.h"
#include "Bullet.h"
#include <list>
#include "Rocket.h"

class BulletManager
{
private:
    static BulletManager *bminstance;
    int sum = 0;
    bool stall = false; // Control shooting

public:
    std::list<Bullet *> bullets; // hold list of bullets

private:
    void update();    // loop through bullet list and update each bullet position
    BulletManager();  // constructor
    ~BulletManager(); // Destructor

public:
    static BulletManager *getBMInstance();                   // get instance of bullet manager
    static void release();                                   // Instance Released at end of game
    void render(SDL_Renderer *r, SDL_Texture *t, double dt); // Render bullets
    void makeBullet(Rocket *rocket);                         // make bullet takes in a rocket pointer and  instantiates a new bullet
    // into the bullets list
    void stallShooting(bool check);
    bool isStalled();
};