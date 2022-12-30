#include "SoundManager.h"

Mix_Music *SoundManager::music = nullptr;
Mix_Chunk *SoundManager::laser_shot = nullptr;
Mix_Chunk *SoundManager::menu_change = nullptr;
Mix_Chunk *SoundManager::player_dead = nullptr;

SoundManager::SoundManager() {}
SoundManager::SoundManager(std::string path)
{
    // Init sound
    Mix_Init(0);
    /* if (Mix_Init(0) == 0)
    {
        std::cout << "Mixer init failed" << std::endl;
        return;
    } */

    // Audio settings
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    // loading files
    std::string mus = path + "/mixgame-music.wav";
    std::string las = path + "/mix-laser-sound.wav";
    std::string mc = path + "/mixarcade-menu.wav";
    std::string pd = path + "/mixarcade-dead.wav";

    music = Mix_LoadMUS(mus.c_str());
    laser_shot = Mix_LoadWAV(las.c_str());
    menu_change = Mix_LoadWAV(mc.c_str());
    player_dead = Mix_LoadWAV(pd.c_str());
}

SoundManager::~SoundManager() {}