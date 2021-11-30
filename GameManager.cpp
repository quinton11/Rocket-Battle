#include "gamemanager.h"
#include "iostream"


GameManager* GameManager::gmInstance = NULL;

GameManager* GameManager::instance() {
	if (gmInstance == NULL) 
		gmInstance = new GameManager();
	
	return gmInstance;
}

void GameManager::release() {
	delete gmInstance;
	gmInstance = NULL;
}

GameManager::GameManager(){

	isDone = false;

	nGraphics = GameGraphics::getInstance();

	if (!GameGraphics::getInitialized())
		isDone = true;
}

GameManager::~GameManager() {
	GameGraphics::release();
	nGraphics = NULL;
}

void GameManager::Run() {
	while (!isDone) {


		//Check event queue to exeute events
		while (SDL_PollEvent(&nevents)) {
			if (nevents.type == SDL_QUIT) {
				isDone = true;
			}

			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP]) {
				//firstrect.y -= 5;
				std::cout << "UP" << std::endl;
			}
			else if (state[SDL_SCANCODE_DOWN]) {
				//firstrect.y += 5;
				std::cout << "DOWN" << std::endl;
			}
			else if (state[SDL_SCANCODE_RIGHT]) {
				//firstrect.x += 5;
				std::cout << "RIGHT" << std::endl;
			}
			else if (state[SDL_SCANCODE_LEFT]) {
				//firstrect.x -= 5;
				std::cout << "LEFT" << std::endl;
			}
		}

		nGraphics->render();

		/*//Set render color for window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//Clear renderer target, in this case the window
		SDL_RenderClear(renderer);


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		//Draw rectangle
		SDL_RenderDrawRect(renderer, &firstrect);
		SDL_RenderFillRect(renderer, &firstrect);

		//Update screen
		SDL_RenderPresent(renderer);*/
	}
}