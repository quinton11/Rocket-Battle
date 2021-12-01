#pragma once
#include "SDL.h"

class GameEntity {

public:
	void render(SDL_Renderer* renderer);
	void update();

	GameEntity();
	~GameEntity();
};