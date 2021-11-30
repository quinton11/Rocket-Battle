#pragma once
#include "SDL.h"

//handles game window and graphics
//Singleton design
class GameGraphics {

public:
	

	static const int window_width = 600;
	static const int window_height = 400;

private:
	SDL_Window* window;
	static GameGraphics* gInstance;
	SDL_Renderer* renderer;
	static bool gInitialized;

	

public:
	static GameGraphics* getInstance();
	static void release();
	static bool getInitialized();

	//Renders items on screen
	void render();

private:
	GameGraphics();
	~GameGraphics();

	bool Init();
	
};