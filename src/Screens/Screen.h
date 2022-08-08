#pragma once
#include "SDL.h"

class Screen {
private:
	bool ismounted;

public:
	void render(SDL_Renderer* renderer);
	void eventchecker(SDL_Event& events);

	bool getismounted();
	void setismounted();
};
