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

void StatDrawer::setTextures(SDL_Texture *h, SDL_Texture *lb, SDL_Texture *s, SDL_Texture *sh, SDL_Texture *pr)
{
    healtht = h;
    lbolt = lb;
    sun = s;
    shield = sh;
    prect = pr;
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

SDL_Texture *StatDrawer::getText(SDL_Renderer *r, std::string text, SDL_FRect &dest,SDL_Color col)
{
    SDL_Surface *surf;
    SDL_Texture *txture;
    if (text == "")
    {
        text = "Player";
    }
    surf = TTF_RenderText_Blended(TextureManager::font, text.c_str(), col);
    txture = SDL_CreateTextureFromSurface(r, surf);
    dest.w = surf->w * 0.4;
    dest.h = surf->h * 0.4;
    SDL_FreeSurface(surf);

    return txture;
}
std::string StatDrawer::toString(int amt)
{
    std::ostringstream s;
    s << amt;
    std::string text(s.str());
    return text;
}

void StatDrawer::renderHealthBar(SDL_Renderer *r)
{
    //std::cout << rocket->healthPercent << std::endl;

    healthfg.w = health.w * rocket->healthPercent;
    // std::cout << "In drawer " << rocket->healthPercent << std::endl;

    // healthfg.x = health.x + (health.w - healthfg.w);
    healthfg.x = health.x;
    healthfg.y = health.y;
    healthfg.h = health.h;
    // SDL_RenderCopyF(r, hfgtext, nullptr, &healthfg);
    SDL_SetRenderDrawColor(r, 19, 62, 81, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(r, &healthfg);

    /* Render three boxes */
    SDL_FRect defence;
    SDL_FRect banebullet;
    SDL_FRect vetbullet;
    float offset = 40;
    defence.x = health.x + health.w + offset + 30;
    defence.y = health.y - 20;
    defence.w = 45;
    defence.h = 40;

    banebullet.x = defence.x + defence.w + offset;
    banebullet.y = health.y - 20;
    banebullet.w = 45;
    banebullet.h = 40;

    vetbullet.x = banebullet.x + banebullet.w + offset;
    vetbullet.y = health.y - 20;
    vetbullet.w = 45;
    vetbullet.h = 40;

    // render health
    SDL_FRect healthrect;
    healthrect.w = 18;
    healthrect.h = 18;
    healthrect.x = health.x - healthrect.w / 2;
    healthrect.y = health.y - healthrect.h / 2;

    SDL_FRect defencerect;
    defencerect.w = 18;
    defencerect.h = 18;
    defencerect.x = defence.x - defencerect.w / 2;
    defencerect.y = defence.y - defencerect.h / 2;

    SDL_FRect bbrect;
    bbrect.w = 18;
    bbrect.h = 18;
    bbrect.x = banebullet.x - bbrect.w / 2;
    bbrect.y = banebullet.y - bbrect.h / 2;

    SDL_FRect vbrect;
    vbrect.w = 18;
    vbrect.h = 18;
    vbrect.x = vetbullet.x - vbrect.w / 2;
    vbrect.y = vetbullet.y - vbrect.h / 2;
    // SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRectF(r, &healthrect);

    // if (!textSet)
    //{
    temph = getText(r, FileManager::currentPlayer, hname,{255,255,255});
    tempd = getText(r, "Defence", dname,{255,255,255});
    tempb = getText(r, "Bane", bname,{255,255,255});
    tempv = getText(r, "Vet", vname,{255,255,255});
    textSet = true;

    // For amount of packets collected by rocket
    SDL_FRect tempdamrect;
    SDL_FRect tempbamrect;
    SDL_FRect tempvamrect;

    tempdamrect.w = 10;
    tempdamrect.h = 10;
    tempdamrect.x = (defence.x + defence.w / 2) - tempdamrect.w / 2;
    tempdamrect.y = (defence.y + defence.h / 2) - tempdamrect.h / 2;

    tempbamrect.w = 10;
    tempbamrect.h = 10;
    tempbamrect.x = (banebullet.x + banebullet.w / 2) - tempbamrect.w / 2;
    tempbamrect.y = (banebullet.y + banebullet.h / 2) - tempbamrect.h / 2;

    tempvamrect.w = 10;
    tempvamrect.h = 10;
    tempvamrect.x = (vetbullet.x + vetbullet.w / 2) - tempvamrect.w / 2;
    tempvamrect.y = (vetbullet.y + vetbullet.h / 2) - tempvamrect.h / 2;

    SDL_Texture *tempdam = getText(r, "x" + toString(rocket->dPacket), tempdamrect,{0,0,0});
    SDL_Texture *tempbam = getText(r, "x" + toString(rocket->bPacket), tempbamrect,{0,0,0});
    SDL_Texture *tempvam = getText(r, "x" + toString(rocket->vPacket), tempvamrect,{0,0,0});

    //}
    // SDL_FRect hname;
    hname.x = health.x;
    hname.y = health.y + health.h + 10;
    // SDL_FRect dname;
    dname.x = (defence.x + defence.w / 2) - dname.w / 2;
    dname.y = defence.y + defence.h + 10;
    // SDL_FRect bname;
    bname.x = (banebullet.x + banebullet.w / 2) - bname.w / 2;
    bname.y = banebullet.y + banebullet.h + 10;
    // SDL_FRect vname;
    vname.x = (vetbullet.x + vetbullet.w / 2) - vname.w / 2;
    vname.y = vetbullet.y + vetbullet.h + 10;

    // SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderCopyF(r, prect, nullptr, &defence);
    SDL_RenderCopyF(r, prect, nullptr, &banebullet);
    SDL_RenderCopyF(r, prect, nullptr, &vetbullet);

    SDL_RenderCopyF(r, healtht, nullptr, &healthrect);
    SDL_RenderCopyF(r, shield, nullptr, &defencerect);
    SDL_RenderCopyF(r, lbolt, nullptr, &bbrect);
    SDL_RenderCopyF(r, sun, nullptr, &vbrect);

    SDL_RenderCopyF(r, temph, nullptr, &hname);
    SDL_RenderCopyF(r, tempd, nullptr, &dname);
    SDL_RenderCopyF(r, tempb, nullptr, &bname);
    SDL_RenderCopyF(r, tempv, nullptr, &vname);

    SDL_RenderCopyF(r, tempdam, nullptr, &tempdamrect);
    SDL_RenderCopyF(r, tempbam, nullptr, &tempbamrect);
    SDL_RenderCopyF(r, tempvam, nullptr, &tempvamrect);

    SDL_DestroyTexture(temph);
    SDL_DestroyTexture(tempb);
    SDL_DestroyTexture(tempd);
    SDL_DestroyTexture(tempv);

    SDL_DestroyTexture(tempbam);
    SDL_DestroyTexture(tempdam);
    SDL_DestroyTexture(tempvam);

    /* SDL_RenderFillRectF(r, &defence);
    SDL_RenderFillRectF(r, &banebullet);
    SDL_RenderFillRectF(r, &vetbullet); */
}
