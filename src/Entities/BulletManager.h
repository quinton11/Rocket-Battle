#pragma once
#include "SDL.h"
#include "Bullet.h"
#include <list>
#include "Rocket.h"
#include <vector>

class BulletManager
{
private:
    static BulletManager *bminstance;
    int max = 10;
    int shot=0;
    bool stall = false; // Control shooting

public:
    std::vector<Bullet> all;

private:
    void update(SDL_Renderer *r, SDL_Texture *t, double dt,const int wW,const int wH);    // loop through bullet list and update each bullet position
    BulletManager();  // constructor
    ~BulletManager(); // Destructor

public:
    static BulletManager *getBMInstance();                   // get instance of bullet manager
    static void release();                                   // Instance Released at end of game
    void render(SDL_Renderer *r, SDL_Texture *t, double dt,const int wW,const int wH); // Render bullets
    void makeBullet(float cx,float cy,float angle,bool playerShot);                         // make bullet takes in a rocket pointer and  instantiates a new bullet
    // into the bullets list
    void stallShooting(bool check);
    bool isStalled();
};