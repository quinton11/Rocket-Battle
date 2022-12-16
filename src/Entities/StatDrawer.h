#include "SDL.h"
#include "..\Entities\Rocket.h"
#include "string"
#include "sstream"
#include "..\GameManager\TextureManager.h"
#include "..\GameManager\FileManager.h"

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
    bool textSet = false;
    SDL_FRect container;
    SDL_FRect health;
    SDL_FRect healthfg;

    /* // rectangles
    SDL_FRect defence;
    SDL_FRect banebullet;
    SDL_FRect vetbullet;

    // blits
    SDL_FRect healthrect;
    SDL_FRect defencerect;
    SDL_FRect bbrect;
    SDL_FRect vbrect; */

    // names
    SDL_FRect hname;
    SDL_FRect dname;
    SDL_FRect bname;
    SDL_FRect vname;

    SDL_Texture *hbgtext;
    SDL_Texture *hfgtext;
    SDL_Texture *healtht;
    SDL_Texture *lbolt;
    SDL_Texture *sun;
    SDL_Texture *shield;
    SDL_Texture *prect;
    SDL_Texture *temph;
    SDL_Texture *tempd;
    SDL_Texture *tempb;
    SDL_Texture *tempv;

    void render(SDL_Renderer *r, int sW, int sH, SDL_Texture *sD);
    void renderHealthBar(SDL_Renderer *r);
    void setRocket(Rocket &rkt);
    void setTextures(SDL_Texture *h, SDL_Texture *lb, SDL_Texture *s, SDL_Texture *sh, SDL_Texture *pr);

private:
    SDL_Texture *getText(SDL_Renderer *r, std::string text, SDL_FRect &dest);
    std::string toString(int amt);
};