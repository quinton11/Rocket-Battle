#pragma once
#include "SDL_mixer.h"
#include "string"
#include "iostream"

class SoundManager
{
public:
    SoundManager();
    SoundManager(std::string path);

    ~SoundManager();

    static Mix_Music *music;
    static Mix_Chunk *laser_shot;
    static Mix_Chunk *player_dead;
    static Mix_Chunk *menu_change;
};