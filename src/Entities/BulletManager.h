#pragma once
#include "SDL.h"
#include "Bullet.h"
#include <list>

class BulletManager
{
private:
    static BulletManager *bminstance;

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
};