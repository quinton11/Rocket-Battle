#include "SDL.h"
#include "..\Utils\Components.h"
#include "list"
#include "string"
#include "..\GameManager\TextureManager.h"
#include "HomeScreen.h"

class PauseScreen
{
    // should be toggled
public:
    PauseScreen();
    ~PauseScreen();

    static bool active;
    void render(SDL_Renderer *r, int sW, int sH,bool gOver);

private:
    std::list<Button> buttons;
    bool gameOver=false;
    int mx,my;
    SDL_Event events;
    void renderButtons(SDL_Renderer *r, int sW, int sH);
    void createButtons(SDL_Renderer *r, int sW, int sH);
    void inButton(bool isClicked);
    bool mouse_in_play(int &x, int &y, SDL_FRect &rect);
    std::pair<SDL_Texture *, SDL_Texture *> buttonText(SDL_Renderer *r, std::string nm, SDL_FRect &dest);
    void eventChecker(); // check if mouse event for buttons
    Button createButton(SDL_Renderer *r,std::string nm, int sW, int sH);
};