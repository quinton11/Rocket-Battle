#include "StatDrawer.h"

StatDrawer::StatDrawer() {}

StatDrawer::StatDrawer(SDL_Texture *hbg, SDL_Texture *fbg)
{
    // rocket = &r;
    hbgtext = hbg;
    hfgtext = fbg;
}

StatDrawer::~StatDrawer() {}

void StatDrawer::setRocket(Rocket &rkt)
{
    rocket = &rkt;
}

void StatDrawer::setTextures(SDL_Texture *h, SDL_Texture *lb, SDL_Texture *s, SDL_Texture *sh)
{
    healtht = h;
    lbolt = lb;
    sun = s;
    shield = sh;
}

void StatDrawer::render(SDL_Renderer *r, int sW, int sH, SDL_Texture *sD)
{
    // render at bottom or side of screen
    container.x = 0;
    container.h = 100;
    container.y = sH - container.h;
    container.w = sW;

    // SDL_SetRenderDrawColor(r, 50, 12, 68, 255);
    // SDL_RenderFillRectF(r, &container);
    health.x = container.x + 30;
    health.h = 20;
    health.y = (container.y + container.h / 2) - health.h / 2;
    health.w = 200;

    SDL_RenderCopyF(r, sD, nullptr, &container);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRectF(r, &health);
    // SDL_RenderCopyF(r, nullptr, nullptr, &health);
    renderHealthBar(r);
    // have different images or rects representing the powerups and bullets
    // when user collects powerup, count increases, user uses different keys to use
    // powerups and bullets
    // if possible render text tutorial showing keys to use
}

void StatDrawer::renderHealthBar(SDL_Renderer *r)
{
    // use percentage to render life
    // White background
    // SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRectF(r, &health);
    // SDL_RenderCopyF(r, hbgtext, nullptr, &health);
    healthfg.w = health.w * rocket->healthPercent;
    // std::cout << "In drawer " << rocket->healthPercent << std::endl;

    // healthfg.x = health.x + (health.w - healthfg.w);
    healthfg.x = health.x;
    healthfg.y = health.y;
    healthfg.h = health.h;
    // SDL_RenderCopyF(r, hfgtext, nullptr, &healthfg);
    SDL_SetRenderDrawColor(r, 19, 62, 81, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &healthfg);

    // render health
    SDL_FRect healthrect;
    healthrect.w = 18;
    healthrect.h = 18;
    healthrect.x = health.x - healthrect.w / 2;
    healthrect.y = health.y - healthrect.h / 2;
    // SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRectF(r, &healthrect);
    SDL_RenderCopyF(r, healtht, nullptr, &healthrect);

    /* Render three boxes */
    SDL_FRect defence;
    SDL_FRect banebullet;
    SDL_FRect vetbullet;
    float offset = 40;
    defence.x = health.x + health.w + offset+30;
    defence.y = health.y;
    defence.w = 45;
    defence.h = 40;

    banebullet.x = defence.x + defence.w + offset;
    banebullet.y = health.y;
    banebullet.w = 45;
    banebullet.h = 40;

    vetbullet.x = banebullet.x + banebullet.w + offset;
    vetbullet.y = health.y;
    vetbullet.w = 45;
    vetbullet.h = 40;

    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRectF(r, &defence);
    SDL_RenderFillRectF(r, &banebullet);
    SDL_RenderFillRectF(r, &vetbullet);
}
