#pragma once
#include "iostream"
/* #include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class SubScreen
{
private:
    std::string screenName;
    SDL_Event events;
    int mouse_x, mouse_y;
    bool ismounted = false;
    TTF_Font *selffont;
    SDL_Texture *backtext;
    SDL_Texture *labeltext;
    bool backtextSet = false;

public:
    SubScreen();
    SubScreen(TTF_Font *font);
    ~SubScreen();

    void render(SDL_Renderer *r, bool &im, bool &quit, int screenW, int screenH);
    void eventChecker(bool &im, bool &quit);
    std::string getName();
    void setName(std::string name);
    bool getIsMounted();
    void setIsMounted(bool ism);

private:
    void renderNewPlayer(SDL_Renderer *r, int screenW, int screenH);
    void renderSelectPlayer(SDL_Renderer *r, int screenW, int screenH);
    void renderHighScores(SDL_Renderer *r, int screenW, int screenH);
    void renderSettings(SDL_Renderer *r, int screenW, int screenH);
    //SDL_Texture *createText(SDL_Renderer *r, std::string text, SDL_Color color);
}; */