#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class SubScreen
{
private:
    std::string screenName;
    SDL_Event events;
    int mouse_x, mouse_y;
    bool ismounted = false;

public:
    SubScreen();
    SubScreen(std::string name);
    ~SubScreen();

    void render(SDL_Renderer *r, bool &im, bool &quit);
    void eventChecker(bool &im, bool &quit);
    std::string getName();
    void setName(std::string name);
    bool getIsMounted();
    void setIsMounted(bool ism);

private:
    void renderNewPlayer(SDL_Renderer *r);
    void renderSelectPlayer(SDL_Renderer *r);
    void renderHighScores(SDL_Renderer *r);
    void renderSettings(SDL_Renderer *r);
};