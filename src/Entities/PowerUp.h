#pragma once
#include "iostream"
#include "SDL.h"
#include "..\Utils\CustomEnums.h"



class PowerUp
{
public:
    PowerUp();
    PowerUp(CustomEnums::Upgrades t,float x, float y);

    SDL_FRect rect;
    CustomEnums::Upgrades type;
    void render(SDL_Renderer *r,SDL_Texture* t);
};

