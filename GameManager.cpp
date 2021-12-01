#include "gamemanager.h"
#include "iostream"
#include "Rocket.h"
#include "TextureManager.h"

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



GameManager::~GameManager() {
	GameGraphics::release();
	nGraphics = NULL;
}

void GameManager::Run() {

	Rocket rocket = Rocket();
	TextureManager txman = TextureManager();
	SDL_Texture* texture = txman.loadTexture("textures/spaceship1.png", nGraphics->getrenderer());

	
	while (!isDone) {


		//Check event queue to exeute events
		while (SDL_PollEvent(&nevents)) {
			if (nevents.type == SDL_QUIT) {
				isDone = true;
			}

			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP]) {
				//firstrect.y -= 5;
				rocket.moveup();
				std::cout << "UP" << std::endl;
			}
			else if (state[SDL_SCANCODE_DOWN]) {
				//firstrect.y += 5;
				rocket.movedown();
				std::cout << "DOWN" << std::endl;
			}
			else if (state[SDL_SCANCODE_RIGHT]) {
				//firstrect.x += 5;
				rocket.moveright();
				std::cout << "RIGHT" << std::endl;
			}
			else if (state[SDL_SCANCODE_LEFT]) {
				//firstrect.x -= 5;
				rocket.moveleft();
				std::cout << "LEFT" << std::endl;
			}
		}

		nGraphics->render();

		//Render rocket
		//rocket.render(nGraphics->getrenderer());
		
		SDL_RenderCopy(nGraphics->getrenderer(),texture,nullptr,&rocket.rect);

		//Updating screen
		SDL_RenderPresent(nGraphics->getrenderer());

	}
}

GameManager::GameManager() {

	isDone = false;

	nGraphics = GameGraphics::getInstance();

	if (!GameGraphics::getInitialized())
		isDone = true;
}