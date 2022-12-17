#include "PowerUp.h"

PowerUp::PowerUp() {}
PowerUp::PowerUp(CustomEnums::Upgrades t, float x, float y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 15;
    rect.h = 15;
    type = t;
}

void PowerUp::render(SDL_Renderer *r, SDL_Texture *t)
{
    SDL_RenderCopyF(r, t, nullptr, &rect);
    // SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRectF(r, &rect);
    // std::cout << "Rendering " << rect.x << " , " << rect.y << rect.w << " , " << rect.h << std::endl;
    //  SDL_DestroyTexture(t);
}
