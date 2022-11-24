/* #include "SubScreens.h"

SubScreen::SubScreen() {}
SubScreen::~SubScreen() {}
SubScreen::SubScreen(TTF_Font *font)
    : selffont(font) {}

void SubScreen::render(SDL_Renderer *r, bool &im, bool &quit, int screenW, int screenH)
{
    // event checker
    eventChecker(im, quit);
    //  render necessaries based on name
    if (screenName == "New Player")
    {
        // render new player screen
        renderNewPlayer(r, screenW, screenH);
    }
    else if (screenName == "Select Player")
    {
        // render select player screen
        renderSelectPlayer(r, screenW, screenH);
    }
    else if (screenName == "High Score")
    {
        // render High Score screen
        renderHighScores(r, screenW, screenH);
    }
    else if (screenName == "Settings")
    {
        renderSettings(r, screenW, screenH);
    }
    SDL_RenderPresent(r);
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

void SubScreen::setIsMounted(bool ism)
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

 SDL_Texture *SubScreen::createText(SDL_Renderer *r, std::string text, SDL_Color color)
{
    SDL_Texture *texture;
    SDL_Surface *surf = TTF_RenderText_Blended(selffont, text.c_str(), {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);

    return texture;
} 

void SubScreen::renderNewPlayer(SDL_Renderer *r, int screenW, int screenH)
{
    // render New Player screen structure
    // render black background
    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(r, NULL); // fill screen
    // a back button at the top left corner
    // back button
    // x=20,y=20,w=50,h=30
    if (!backtextSet)
    {
        SDL_Texture *texture;
        std::string text = "Back";
        SDL_Surface *surf = TTF_RenderText_Blended(selffont, text.c_str(), {255, 255, 255});
        texture = SDL_CreateTextureFromSurface(r, surf);
        SDL_FreeSurface(surf);
        SDL_Texture *backt = texture;
        backtext = backt;
        backtextSet = true;
    }
    SDL_FRect backbutton = {20, 20, 50, 30};
    SDL_RenderCopyF(r, backtext, nullptr, &backbutton);
    // w is 30 h is 20
    // x is middle of screenx - w/2
    float lw = 30;
    float lh = 20;
    float lx = (screenW / 2) - lw / 2;
    float ly = 40;
    SDL_FRect label = {lx, ly, lw, lh};
    // text for back and middle top
    SDL_Texture *texture;
    std::string text = "Create Player";
    SDL_Surface *surf = TTF_RenderText_Blended(selffont, text.c_str(), {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);
    SDL_Texture *labeltext = texture;
    SDL_RenderCopyF(r, labeltext, nullptr, &label);

    // a text label at middle top requesting for name of player
    // a text input below label requesting for user input
};
void SubScreen::renderSelectPlayer(SDL_Renderer *r, int screenW, int screenH)
{
    // render Select Player screen structure
    // render black background
    // a back button at top left corner
    // a text label at top of screen
    // a large container under which contains a stretch of registered players to select from
    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(r, NULL); // fill screen
    // a back button at the top left corner
    // back button
    // x=20,y=20,w=50,h=30
    if (!backtextSet)
    {
        SDL_Texture *texture;
        std::string text = "Back";
        SDL_Surface *surf = TTF_RenderText_Blended(selffont, text.c_str(), {255, 255, 255});
        texture = SDL_CreateTextureFromSurface(r, surf);
        SDL_FreeSurface(surf);
        SDL_Texture *backt = texture;
        backtext = backt;
        backtextSet = true;
    }
    SDL_FRect backbutton = {20, 20, 50, 30};
    SDL_RenderCopyF(r, backtext, nullptr, &backbutton);
    // w is 30 h is 20
    // x is middle of screenx - w/2
    float lw = 30;
    float lh = 20;
    float lx = (screenW / 2) - lw / 2;
    float ly = 40;
    SDL_FRect label = {lx, ly, lw, lh};
    // text for back and middle top
    SDL_Texture *texture;
    std::string text = "Select Player";
    SDL_Surface *surf = TTF_RenderText_Blended(selffont, text.c_str(), {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);
    SDL_Texture *labeltext = texture;
    SDL_RenderCopyF(r, labeltext, nullptr, &label);
};
void SubScreen::renderHighScores(SDL_Renderer *r, int screenW, int screenH)
{
    // render High Scores screen structure
    // render black background
    // a back button at top left corner
    // a text label at top of screen
    // a large container under containing registered players and their highscores
    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(r, NULL); // fill screen
    // a back button at the top left corner
    // back button
    // x=20,y=20,w=50,h=30
    if (!backtextSet)
    {
        SDL_Texture *texture;
        std::string text = "Back";
        SDL_Surface *surf = TTF_RenderText_Blended(selffont, text.c_str(), {255, 255, 255});
        texture = SDL_CreateTextureFromSurface(r, surf);
        SDL_FreeSurface(surf);
        SDL_Texture *backt = texture;
        backtext = backt;
        backtextSet = true;
    }
    SDL_FRect backbutton = {20, 20, 50, 30};
    SDL_RenderCopyF(r, backtext, nullptr, &backbutton);
    // w is 30 h is 20
    // x is middle of screenx - w/2
    float lw = 30;
    float lh = 20;
    float lx = (screenW / 2) - lw / 2;
    float ly = 40;
    SDL_FRect label = {lx, ly, lw, lh};
    // text for back and middle top
    SDL_Texture *texture;
    std::string text = "Back";
    SDL_Surface *surf = TTF_RenderText_Blended(selffont, text.c_str(), {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);
    SDL_Texture *labeltext = texture;
    SDL_RenderCopyF(r, labeltext, nullptr, &label);
};

void SubScreen::renderSettings(SDL_Renderer *r, int screenW, int screenH)
{
    // render Settings screen structure
    // render black background
    // a back button at top left corner
    // a text label at top of screen
    // a slider to select volume level
}
 */