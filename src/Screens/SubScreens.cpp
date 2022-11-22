#include "SubScreens.h"

SubScreen::SubScreen() {}
SubScreen::~SubScreen() {}
SubScreen::SubScreen(std::string name)
    : screenName(name) {}

void SubScreen::render(SDL_Renderer *r, bool &im, bool &quit)
{
    // event checker
    eventChecker(im, quit);
    //  render necessaries based on name
    if (screenName == "New Player")
    {
        // render new player screen
        renderNewPlayer(r);
    }
    else if (screenName == "Select Player")
    {
        // render select player screen
        renderSelectPlayer(r);
    }
    else if (screenName == "High Score")
    {
        // render High Score screen
        renderHighScores(r);
    }
    else if (screenName == "Settings")
    {
        rendeSettings(r);
    }
}

std::string SubScreen::getName()
{
    return screenName;
}

void SubScreen::setName(std::string name)
{
    screenName = name;
}

bool SubScreen::getIsMounted()
{
    return ismounted;
}

bool SubScreen::setIsMounted(bool ism)
{
    ismounted = ism;
}

void SubScreen::eventChecker(bool &im, bool &quit)
{
    // check for click and hover events
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            std::cout << "SDL QUIT event" << std::endl;
            im = false;
            quit = false;

        case SDL_MOUSEMOTION:
            mouse_x = events.motion.x;
            mouse_y = events.motion.y;

        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Left Click in Sub Screen: " << screenName << std::endl;
            }
        }
    }
}

void SubScreen::renderNewPlayer(SDL_Renderer *r){
    // render New Player screen structure
};
void SubScreen::renderSelectPlayer(SDL_Renderer *r){
    // render Select Player screen structure

};
void SubScreen::renderHighScores(SDL_Renderer *r){
    // render High Scores screen structure

};

void SubScreen::renderSettings(SDL_Renderer *r)
{
    // render Settings screen structure
}
