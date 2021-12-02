#include <iostream>

#include "SDL.h"
#include "gamemanager.h"
#undef main


int main() {
	
	GameManager* gm = GameManager::instance();

	gm->Run();

	//deleting gm pointer and freeing its memory
	gm->release();
	gm = NULL;

	SDL_Quit();

	return 0;
}