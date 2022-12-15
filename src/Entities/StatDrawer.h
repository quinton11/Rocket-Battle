#include "SDL.h"
#include "..\Entities\Rocket.h"

/*
    Display defence power up count
    Display bullet tier counts
    Display ship health percentage and tier
 */
class StatDrawer
{
public:
    StatDrawer();
    StatDrawer(SDL_Texture *hbg, SDL_Texture *fbg);
    ~StatDrawer();
    Rocket *rocket;
    SDL_FRect container;
    SDL_FRect health;
    SDL_FRect healthfg;
    SDL_Texture *hbgtext;
    SDL_Texture *hfgtext;
    SDL_Texture *healtht;
    SDL_Texture *lbolt;
    SDL_Texture *sun;
    SDL_Texture *shield;

    void render(SDL_Renderer *r, int sW, int sH, SDL_Texture *sD);
    void renderHealthBar(SDL_Renderer *r);
    void setRocket(Rocket &rkt);
    void setTextures(SDL_Texture *h, SDL_Texture *lb, SDL_Texture *s, SDL_Texture *sh);
};