#include "MinScreen.h"

bool MinScreen::mouse_in_play(int &x, int &y, SDL_FRect &rect)
{
    return (x >= rect.x) && (y >= rect.y) &&
           (x < rect.x + rect.w) && (y < rect.y + rect.h);
}

void MinScreen::setName(std::string n) { name = n; }
void MinScreen::setfont(TTF_Font *f) { font = f; }
void MinScreen::eventChecker(bool &im, bool &quit)
{
    int leng;
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            std::cout << "SDL QUIT event" << std::endl;
            im = false;
            quit = true;
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

        case SDL_TEXTINPUT:
            if (name == "New Player")
            {
                // add to text input
                textInput += events.text.text;
                // std::cout << textInput << std::endl;
            }
            break;
        case SDL_KEYDOWN:
            if (name == "New Player")
            {
                switch (events.key.keysym.sym)
                {
                case SDLK_SPACE:
                    // std::cout << "Space Bar hit" << std::endl;
                    break;

                case SDLK_BACKSPACE:
                    //std::cout << "Back Space hit" << std::endl;
                    leng = textInput.size();
                    ////std::cout << leng << std::endl;

                    if (leng > 0)
                    {
                        textInput.pop_back();
                    }
                    break;

                case SDLK_RETURN:
                    //std::cout << "Enter hit" << std::endl;
                    //std::cout << textInput << std::endl;
                    addPlayer();
                    movetoplay();
                    // textInput = "";
                    //  create new player and move to play screen
                    break;
                }
            }
            break;
        }
    }
}

void MinScreen::inButton(bool isClicked)
{
    // check if mouse is in button
    // If mouse is in back button
    isActive = false;
    if (mouse_in_play(mx, my, backButton))
    {
        isActive = true;
        // hover
        if (isClicked)
        {
            // std::cout << "Back Button clicked" << std::endl;
            isMtd = false;
            isActive = false;
        }
        return;
    }
    if (name == "Select Player")
    {
        std::list<Button>::iterator it;
        for (it = playerButtons.begin(); it != playerButtons.end(); it++)
        {
            it->isActive = false;
            if (mouse_in_play(mx, my, it->dest))
            {
                it->isActive = true;
                if (isClicked)
                {
                    // it->isSelected = true;
                    setSelectedPButton(*it);
                    FileManager::currentPlayer = it->name;
                    FileManager::currentScore = FileManager::playerScores[it->name];
                    //std::cout << it->name << " is selected" << std::endl;
                }
            }
        }
    }

    // need to have locations of each button
    // common button is the back button
    // then we have the create player button
    // then select player buttons where user is shown a list of players and highscore
    // also implement highlight on hover
}
void MinScreen::render(SDL_Renderer *r, int sW, int sH)
{
    //  render necessaries based on name
    if (name == "New Player")
    {
        // render new player screen
        renderNewPlayer(r, sW, sH);
    }
    else if (name == "Select Player")
    {
        // render select player screen
        renderSelectPlayer(r, sW, sH);
    }
    else if (name == "High Score")
    {
        // render High Score screen
        renderHS(r, sW, sH);
    }
    else if (name == "Settings")
    {
        renderSettings(r, sW, sH);
    }
    SDL_RenderPresent(r);
}

void MinScreen::addPlayer()
{
    // check if textname is not empty
    // if so then add it to the map of players
    // clear text
    if (textInput != "")
    {
        FileManager::writeHSM(textInput, 0);
        FileManager::currentPlayer = textInput;
        FileManager::currentScore = 0;
        textInput = "";
        playerSelected = true;
        matchPlayers(); // update list of players
        return;
    }

    // if empty return and do nothing
    return;
}

void MinScreen::movetoplay()
{
    isMtd = false;
}

void MinScreen::setBackText(SDL_Renderer *r)
{
    SDL_FRect backbutton = {20, 20, 50, 30};

    if (!backTextSet)
    {
        SDL_Texture *texture;
        std::string text = "Back";
        SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
        texture = SDL_CreateTextureFromSurface(r, surf);
        SDL_FreeSurface(surf);
        SDL_Texture *backt = texture;

        // hover
        surf = TTF_RenderText_Blended(font, text.c_str(), {255, 0, 0});
        texture = SDL_CreateTextureFromSurface(r, surf);
        SDL_FreeSurface(surf);
        backtext = backt;
        backtextH = texture;
        backTextSet = true;
        backButton = backbutton;
    }
}

void MinScreen::renderTitle(SDL_Renderer *r, int sW, int sH)
{
    SDL_Surface *temps;
    SDL_FRect paget;

    temps = TTF_RenderText_Blended(font, name.c_str(), {255, 255, 255});
    if (temps)
    {
        titleImage = SDL_CreateTextureFromSurface(r, temps);
        paget.w = temps->w;
        paget.h = temps->h;
        paget.x = (float)(sW / 2) - paget.w / 2;
        paget.y = 40;
        SDL_FreeSurface(temps);
        temps = NULL;
    }
    SDL_RenderCopyF(r, titleImage, nullptr, &paget);
}

void MinScreen::renderInputBox(SDL_Renderer *r, int sW, int sH)
{
    SDL_FRect container;
    SDL_Surface *temps;
    SDL_FRect tinp;
    container.w = (float)(sW)-100;
    container.h = 50;
    container.x = (float)(sW / 2) - container.w / 2;
    container.y = 200;

    temps = TTF_RenderText_Blended(font, textInput.c_str(), {0, 0, 0});
    if (temps)
    {
        textImage = SDL_CreateTextureFromSurface(r, temps);
        tinp.w = temps->w;
        tinp.h = temps->h;
        tinp.x = (float)(sW / 2) - tinp.w / 2;
        tinp.y = 200;
        SDL_FreeSurface(temps);
        temps = NULL;
    }

    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRectF(r, &container);
    SDL_RenderCopyF(r, textImage, nullptr, &tinp);
}

void MinScreen::renderBackButton(SDL_Renderer *r)
{
    SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(r, NULL); // fill screen

    setBackText(r);

    if (isActive)
    {
        SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
    }
    else
    {
        SDL_RenderCopyF(r, backtext, nullptr, &backButton);
    }
}

void MinScreen::renderNewPlayer(SDL_Renderer *r, int sW, int sH)
{
    // render page title at middle top
    renderBackButton(r);
    renderTitle(r, sW, sH);
    renderInputBox(r, sW, sH);
    // after inputting,push name with highscore of 0 to the playerScores map when user has
    // created player
}
void MinScreen::renderSelectPlayer(SDL_Renderer *r, int sW, int sH)
{
    matchPlayerButtons(r);
    renderBackButton(r);
    renderTitle(r, sW, sH);
    renderPlayersScroll(r, 0.0f, sW, sH);
    // render list of players
    // list of players to create buttons

    // if size of playerScores is 0, render no player
    // else render all players
}

void MinScreen::renderHS(SDL_Renderer *r, int sW, int sH)
{
    renderBackButton(r);

    renderTitle(r, sW, sH);
    matchPlayerScoreDisplay(r, sW, sH);
    // if size of playerScores map is 0 render none
    // loop through player buttons to render
    // else render players and their scores
}
void MinScreen::renderSettings(SDL_Renderer *r, int sW, int sH)
{
    // std::cout << "Render Settings" << std::endl;
    renderBackButton(r);

    renderTitle(r, sW, sH);
}

// Updates players list with FileManager::playerScores map
void MinScreen::matchPlayers()
{
    int sizeps = FileManager::playerScores.size();
    int sizep = players.size();
    std::string nm;
    if (sizeps == 0)
    {
        std::cout << "Zero players" << std::endl;
    }
    if (sizeps != sizep)
    {
        std::map<std::string, int>::iterator it;
        players.clear(); // clear list

        for (it = FileManager::playerScores.begin(); it != FileManager::playerScores.end(); it++)
        {
            nm = it->first;
            players.push_back(nm);
        }
    }
}

void MinScreen::renderPlayersScroll(SDL_Renderer *r, float offset, int sW, int sH)
{
    SDL_FRect midCon;
    SDL_FRect dest;
    /*
    x is the middle of screen minus half of container width
    y is displacement between title and container plus title y+title height
    width is varied
     */
    midCon.w = 300;
    midCon.h = 400;
    midCon.x = (sW / 2) - (midCon.w / 2);
    midCon.y = 130;

    SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &midCon);
    // SDL_SetRenderDrawColor(r, 255, 0, 0, SDL_ALPHA_OPAQUE);

    /*
        Loop through buttons list and render each
        buttons rect. each's width and height are set
        then the x is set however the y changes on each iteration
     */
    if (selectedB != nullptr)
    {
        SDL_SetRenderDrawColor(r, 20, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRectF(r, &(selectedB->dest));
    }
    float yoff = midCon.y + 20;
    for (std::list<Button>::iterator it = playerButtons.begin(); it != playerButtons.end(); it++)
    {
        it->rect.w = 180;
        it->rect.h = 20;
        it->rect.x = (midCon.x + midCon.w / 2) - (it->rect.w / 2);
        it->rect.y = yoff;
        // dest.w =(it->text)
        it->dest.x = it->rect.x;
        it->dest.y = it->rect.y;

        // SDL_RenderFillRectF(r, &(it->rect));

        if (it->isActive)
        {
            SDL_RenderCopyF(r, it->hovertext, nullptr, &(it->dest));
        }
        if (!it->isActive)
        {
            SDL_RenderCopyF(r, it->text, nullptr, &(it->dest));
        }
        yoff += it->rect.h + 5;
    }
}
void MinScreen::matchPlayerButtons(SDL_Renderer *r)
{
    int sizep = players.size();
    int sizepb = playerButtons.size();
    Button temp;
    std::pair<SDL_Texture *, SDL_Texture *> tempText;

    if (sizep == 0)
    {
        std::cout << "Empty" << std::endl;
        // return;
    }
    else if (sizep != sizepb)
    {
        std::list<std::string>::iterator it;
        playerButtons.clear();
        for (it = players.begin(); it != players.end(); it++)
        {
            // create buttons
            temp = Button{*it, false, false};
            tempText = buttonText(r, *it, temp.dest);
            temp.text = tempText.first;
            temp.hovertext = tempText.second;
            playerButtons.push_back(temp);
            // add them to list of buttons
        }
    }
}

void MinScreen::matchPlayerScoreDisplay(SDL_Renderer *r, int sW, int sH)
{

    SDL_FRect midCon;
    SDL_FRect dest;
    midCon.w = 400;
    midCon.h = 400;
    midCon.x = (sW / 2) - (midCon.w / 2);
    midCon.y = 130;

    SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &midCon);

    // loop through playerscore map,create texture
    // render rects holding players name and highscore
    float yoff = midCon.y + 20;
    std::map<std::string, int>::iterator it;
    std::pair<SDL_Texture *, SDL_Texture *> p;
    std::stringstream s;
    for (it = FileManager::playerScores.begin(); it != FileManager::playerScores.end(); it++)
    {
        // x,y position of dest rect
        // create textures
        s << it->second; // to string
        p = displayText(r, it->first, s.str(), dest);
        dest.x = (midCon.x + midCon.w / 2) - (dest.w / 2);
        dest.y = yoff;
        // set w and height
        // draw text on rect
        SDL_RenderCopyF(r, p.first, nullptr, &dest);
        // offset y
        // delete textures
        SDL_DestroyTexture(p.first);
        SDL_DestroyTexture(p.second);

        yoff += dest.h + 5;
        // s.
        std::stringstream().swap(s);
    }
}

void MinScreen::setSelectedPButton(Button &b)
{
    selectedB = &b;
}

std::pair<SDL_Texture *, SDL_Texture *> MinScreen::buttonText(SDL_Renderer *r, std::string nm, SDL_FRect &dest)
{
    SDL_Surface *surf;
    SDL_Texture *texture;
    SDL_Texture *hovtexture;
    std::pair<SDL_Texture *, SDL_Texture *> res;

    surf = TTF_RenderText_Blended(font, nm.c_str(), {0, 0, 0});
    texture = SDL_CreateTextureFromSurface(r, surf);
    dest.w = surf->w - 20;
    dest.h = surf->h - 20;
    SDL_FreeSurface(surf);

    // hover
    surf = TTF_RenderText_Blended(font, nm.c_str(), {255, 0, 0});
    hovtexture = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);
    res = std::pair<SDL_Texture *, SDL_Texture *>(texture, hovtexture);
    return res;
}

std::pair<SDL_Texture *, SDL_Texture *> MinScreen::displayText(SDL_Renderer *r, std::string nm, std::string score, SDL_FRect &dest)
{
    SDL_Surface *surf;
    SDL_Texture *ntexture;
    SDL_Texture *stexture;
    std::pair<SDL_Texture *, SDL_Texture *> res;
    // std::stringstream s;
    // s << nm << "\t" << score;
    std::string gap = nm + "          " + score;
    // std::cout << gap << std::endl;
    surf = TTF_RenderText_Blended(font, gap.c_str(), {0, 0, 0});
    ntexture = SDL_CreateTextureFromSurface(r, surf);
    dest.w = surf->w - 20;
    dest.h = surf->h - 20;
    SDL_FreeSurface(surf);

    surf = TTF_RenderText_Blended(font, score.c_str(), {255, 0, 0});
    stexture = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);
    res = std::pair<SDL_Texture *, SDL_Texture *>(ntexture, stexture);

    return res;
}