#pragma once
#include "SDL.h"

class GameEntity
{

public:
	void render(SDL_Renderer *renderer);
	bool collision(SDL_FRect other);
	void update();

	GameEntity();
	~GameEntity();
};