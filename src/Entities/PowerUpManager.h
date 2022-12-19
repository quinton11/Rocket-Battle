#pragma once
#include "SDL.h"
#include "list"
#include "PowerUp.h"
#include "..\Utils\CustomEnums.h"
#include "Rocket.h"

// handle rendering of power ups
// creating one at a position and deleting one when collided with rect
class PowerUpManager
{
public:
    PowerUpManager();
    ~PowerUpManager();

    SDL_Texture *defenceTxt;
    SDL_Texture *baneTxt;
    SDL_Texture *vetTxt;
    SDL_Texture *healthTxt;
    Rocket *rocket;

    std::list<PowerUp *> powerUps;
    void addPowerUp(CustomEnums::Upgrades pUps, float x, float y);
    bool checkCollision(PowerUp pUp);
    void render(SDL_Renderer *r);
    void setReference(Rocket &rkt);
    void addTextures(SDL_Texture *dtxt, SDL_Texture *btxt, SDL_Texture *vtxt, SDL_Texture *htxt);
};