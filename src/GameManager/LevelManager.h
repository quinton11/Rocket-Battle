#pragma once
#include "iostream"
#include "..\Utils\CustomEnums.h"

class LevelManager
{
public:
    LevelManager();
    ~LevelManager();

    static CustomEnums::Levels level;
    static void changelevel(int kills);
};