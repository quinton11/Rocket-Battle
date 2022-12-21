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
            // std::cout << "Defence" << std::endl;
            // std::cout << (*it)->rect.x << " , " << (*it)->rect.y << std::endl;
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
        else if ((*it)->type == CustomEnums::Upgrades::Health)
        {
            (*it)->render(r, healthTxt);
        }
        // check if powerup is collided with rocket
        if (checkCollision(*(*it)))
        {

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

bool PowerUpManager::checkCollision(PowerUp pUp)
{
    if (rocket->collision(pUp.rect))
    {
        if (pUp.type == CustomEnums::Upgrades::Defence)
        {
            // std::cout << "Defence" << std::endl;
            // std::cout << (*it)->rect.x << " , " << (*it)->rect.y << std::endl;
            rocket->dPacket += 1;
            return true;
        }
        else if (pUp.type == CustomEnums::Upgrades::Bane)
        {
            return true;
        }
        else if (pUp.type == CustomEnums::Upgrades::Vet)
        {
            return true;
        }
        else if (pUp.type == CustomEnums::Upgrades::Health)
        {

            rocket->addHealth(1.f);
            return true;
        }
    }
    return false;
}

void PowerUpManager::addPowerUp(CustomEnums::Upgrades pUps, float x, float y)
{
    //rocket->kills += 1;
    //std::cout << rocket->kills << std::endl;
    LevelManager::changelevel(rocket->kills);
    PowerUp *pU = new PowerUp(pUps, x, y);
    powerUps.push_back(pU);
}

void PowerUpManager::setReference(Rocket &rkt)
{
    rocket = &rkt;
}

void PowerUpManager::addTextures(SDL_Texture *dtxt, SDL_Texture *btxt, SDL_Texture *vtxt, SDL_Texture *htxt)
{
    defenceTxt = dtxt;
    baneTxt = btxt;
    vetTxt = vtxt;
    healthTxt = htxt;
}
