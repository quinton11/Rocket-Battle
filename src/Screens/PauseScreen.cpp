#include "PauseScreen.h"

bool PauseScreen::active = false;

PauseScreen::PauseScreen(){
    //
};
PauseScreen::~PauseScreen(){};

void PauseScreen::render(SDL_Renderer *r, int sW, int sH, bool gOver)
{
    gameOver = gOver;
    if (gameOver)
    {
        active = true;
        // check if playerscore is greater than currentscore
        // if so update current players highscore
        FileManager::updateHScore();
    }
    while (active)
    {
        // std::cout << "Pause Event Checker" << std::endl;
        eventChecker();
        renderButtons(r, sW, sH);
        // std::cout << "After renderButtons" << std::endl;
    }
}

void PauseScreen::renderButtons(SDL_Renderer *r, int sW, int sH)
{
    // if buttons have notbeen created, create buttons and add to list of buttons
    int size = buttons.size();
    SDL_FRect midCon;
    midCon.w = 300;
    midCon.h = 150;
    midCon.x = (sW / 2) - (midCon.w / 2);
    midCon.y = (sH / 2) - midCon.h / 2;

    if (size == 0)
    {
        // create buttons
        float yoff = midCon.y + 20;
        Button btempr;
        Button btempng;
        Button btempq;
        btempr = createButton(r, "Resume", sW, sH);
        btempng = createButton(r, "New Game", sW, sH);
        btempq = createButton(r, "quit", sW, sH);

        // buttons position
        btempr.dest.x = (midCon.x + midCon.w / 2) - (btempr.dest.w / 2);
        btempr.dest.y = yoff;

        yoff += btempr.dest.h + 5;

        btempng.dest.x = (midCon.x + midCon.w / 2) - (btempng.dest.w / 2);
        btempng.dest.y = yoff;

        yoff += btempng.dest.h + 5;

        btempq.dest.x = (midCon.x + midCon.w / 2) - (btempq.dest.w / 2);
        btempq.dest.y = yoff;

        buttons.push_back(btempr);
        buttons.push_back(btempng);
        buttons.push_back(btempq);
    }
    // render container
    // SDL_RenderClear()
    SDL_SetRenderDrawColor(r, 0, 0, 0, 50);
    SDL_RenderFillRect(r, nullptr);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRectF(r, &midCon);
    SDL_RenderCopyF(r, nullptr, nullptr, &midCon);

    for (std::list<Button>::iterator it = buttons.begin(); it != buttons.end();)
    {
        if (gameOver)
        {
            if (it->name == "Resume")
            {
                it++;
            }
        }
        if (it->isActive)
        {
            SDL_RenderCopyF(r, it->hovertext, nullptr, &(it->dest));
            it++;
        }
        else
        {
            SDL_RenderCopyF(r, it->text, nullptr, &(it->dest));
            it++;
        }
    }
    SDL_RenderPresent(r);
    // loop through buttons and draw them with textures
    //  loop through buttons and render them
}

bool PauseScreen::mouse_in_play(int &x, int &y, SDL_FRect &rect)
{
    return (x >= rect.x) && (y >= rect.y) &&
           (x < rect.x + rect.w) && (y < rect.y + rect.h);
}
void PauseScreen::inButton(bool isClicked)
{
    std::list<Button>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); it++)
    {
        it->isActive = false;
        if (mouse_in_play(mx, my, it->dest))
        {
            it->isActive = true;
            if (isClicked)
            {
                // std::cout << it->name << " was clicked" << std::endl;
                if (it->name == "Resume")
                {
                    active = false;
                }
                if (it->name == "quit")
                {
                    active = false;
                    HomeScreen::ismounted = false;
                    HomeScreen::quit = true;
                    FileManager::updateHScore();
                }
                if (it->name == "New Game")
                {
                    active = false;
                    HomeScreen::ismounted = true;
                    FileManager::updateHScore();
                }
            }
            return;
        }
    }
}
void PauseScreen::eventChecker()
{
    // check for events
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            active = false;
            HomeScreen::ismounted = false;
            HomeScreen::quit = true;
            break;
        case SDL_MOUSEMOTION:
            mx = events.motion.x;
            my = events.motion.y;
            inButton(false);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                inButton(true);
            }
            break;

        case SDL_KEYDOWN:
            switch (events.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                active = false;
            }
            break;
        }
    }
}

Button PauseScreen::createButton(SDL_Renderer *r, std::string nm, int sW, int sH)
{
    Button temp = {nm, false, false};
    std::pair<SDL_Texture *, SDL_Texture *> res = buttonText(r, nm, temp.dest);
    temp.text = res.first;
    temp.hovertext = res.second;
    return temp;
    // create textures
}
std::pair<SDL_Texture *, SDL_Texture *> PauseScreen::buttonText(SDL_Renderer *r, std::string nm, SDL_FRect &dest)
{
    SDL_Surface *surf;
    SDL_Texture *texture;
    SDL_Texture *hovtexture;
    std::pair<SDL_Texture *, SDL_Texture *> res;

    surf = TTF_RenderText_Blended(TextureManager::font, nm.c_str(), {0, 0, 0});
    texture = SDL_CreateTextureFromSurface(r, surf);
    dest.w = surf->w - 20;
    dest.h = surf->h - 20;
    SDL_FreeSurface(surf);

    // hover
    surf = TTF_RenderText_Blended(TextureManager::font, nm.c_str(), {255, 0, 0});
    hovtexture = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);
    res = std::pair<SDL_Texture *, SDL_Texture *>(texture, hovtexture);
    return res;
}
