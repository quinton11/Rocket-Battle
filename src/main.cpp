#include <iostream>

#include "SDL.h"

#include "GameManager/gamemanager.h"
#undef main

int main()
{

	GameManager *gm = GameManager::instance();

	gm->Run();

	// deleting gm pointer and freeing its memory
	gm->release();
	gm = NULL;

	SDL_Quit();

	return 0;
}

/*
	Work on spawning enemy ships
	Should be a max number of enemy ships
	on screen at a time.

*/

/*
	Enemy ship would be spawned at random
	with a fixed health life
	when a bullet hits them, a fraction of
	their health is taken away.
	This happens till the health becomes 0
	and they disappear.
	After a set time, rocket list is
	filled to maximum and rendered.
	For now user just plays to beat the high-score
	Add score count to left top of screen which increases
	with increase in enemy ship take-downs
 */