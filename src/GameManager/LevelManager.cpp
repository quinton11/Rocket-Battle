#include "LevelManager.h"

CustomEnums::Levels LevelManager::level = CustomEnums::Levels::RegLevel;

LevelManager::LevelManager() {}
LevelManager::~LevelManager() {}

void LevelManager::changelevel(int kills)
{
    if (kills < 30)
    {
        level = CustomEnums::Levels::RegLevel;
    }
    if (kills >= 30 && kills < 90)
    {
        level = CustomEnums::Levels::BaneLevel;
    }
    if (kills > 90)
    {
        level = CustomEnums::Levels::VetLevel;
    }
}
