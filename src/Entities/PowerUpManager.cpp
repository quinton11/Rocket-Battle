#include "PowerUpManager.h"

PowerUpManager::PowerUpManager() {}
PowerUpManager::~PowerUpManager() {}

void PowerUpManager::render(SDL_Renderer *r)
{
    std::list<PowerUp *>::iterator it;
    for (it = powerUps.begin(); it != powerUps.end();)
    {
        if ((*it)->type == CustomEnums::Upgrades::Defence)
        {
            //std::cout << "Defence" << std::endl;
            //std::cout << (*it)->rect.x << " , " << (*it)->rect.y << std::endl;
            (*it)->render(r, defenceTxt);
        }
        else if ((*it)->type == CustomEnums::Upgrades::Bane)
        {
            (*it)->render(r, baneTxt);
        }
        else if ((*it)->type == CustomEnums::Upgrades::Vet)
        {
            (*it)->render(r, vetTxt);
        }
        // check if powerup is collided with rocket
        if (rocket->collision((*it)->rect))
        {
            rocket->dPacket += 1;
            delete ((*it));
            powerUps.erase(it++);
        }
        else
        {
            it++;
        }
        // if yes increment rocket count for respective power up
        // and pop power up from list
    }
}
void PowerUpManager::addPowerUp(CustomEnums::Upgrades pUps, float x, float y)
{
    PowerUp *pU = new PowerUp(pUps, x, y);
    powerUps.push_back(pU);
}

void PowerUpManager::setReference(Rocket &rkt)
{
    rocket = &rkt;
}

void PowerUpManager::addTextures(SDL_Texture *dtxt, SDL_Texture *btxt, SDL_Texture *vtxt)
{
    defenceTxt = dtxt;
    baneTxt = btxt;
    vetTxt = vtxt;
}
