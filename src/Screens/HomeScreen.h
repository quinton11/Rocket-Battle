#pragma once
#include "Screen.h"
#include "..\GameManager\TextureManager.h"

class HomeScreen : public Screen
{

public:
	TextureManager textm;

private:
	bool ismounted = true;
	bool quit = false;
	SDL_Texture *screentexture = nullptr;
	SDL_Event events;
	SDL_Rect play_rect = {250, 350, 70, 70};
	int mouse_x, mouse_y = 0;

public:
	void render(SDL_Renderer *renderer);
	void eventchecker();

	bool getismounted();
	bool getisquit();
	void setismounted(bool);
	bool mouse_in_play(int &x, int &y, SDL_Rect &rect);

	HomeScreen(SDL_Renderer *renderer);
	HomeScreen();
	~HomeScreen();
};
