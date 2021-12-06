#include "gamemanager.h"
#include "iostream"
#include "Rocket.h"
#include "TextureManager.h"
#include "HomeScreen.h"
#include "TimeSetting.h"

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

	//Rocket object
	Rocket rocket = Rocket();
	TextureManager txman = TextureManager();
	SDL_Texture* texture = txman.loadTexture("textures/spaceship3.png", nGraphics->getrenderer());
	HomeScreen homescreen = HomeScreen(nGraphics->getrenderer());

	//TimeSetting
	TimeSetting tset = TimeSetting();

	float dt;


	
	while (!isDone) {

		//Deltatime
		dt = tset.getDeltaTime();

		if (homescreen.getismounted()) {
			homescreen.render(nGraphics->getrenderer());
		}

		else if (!homescreen.getismounted() && homescreen.getisquit()) {
			isDone = true;
		}

		else {
			//Check event queue to exeute events
			while (SDL_PollEvent(&nevents)) {
				if (nevents.type == SDL_QUIT) {
					isDone = true;
				}

				const Uint8* state = SDL_GetKeyboardState(NULL);

				if (nevents.type == SDL_KEYDOWN) {
					if (state[SDL_SCANCODE_UP]) {
						rocket.moveup(dt);
						std::cout << "UP" << std::endl;
					}
					else if (state[SDL_SCANCODE_DOWN]) {
						rocket.movedown(dt);
						std::cout << "DOWN" << std::endl;
					}
					else if (state[SDL_SCANCODE_RIGHT]) {
						rocket.moveright(dt);
						std::cout << "RIGHT" << std::endl;
					}
					else if (state[SDL_SCANCODE_LEFT]) {
						rocket.moveleft(dt);
						std::cout << "LEFT" << std::endl;
					}

				}

				
			}

			 //Renderscreen
			 nGraphics->render();

			 //Render rocket
			 //rocket.render(nGraphics->getrenderer());

			 //rocket.update();

			 SDL_RenderCopy(nGraphics->getrenderer(), texture, nullptr, &rocket.rect);
			 //rocket.resetrotangle();
			 //Updating screen
			 SDL_RenderPresent(nGraphics->getrenderer());
		}
		
		

	}

	//delete texture;
	//texture = NULL;
}

GameManager::GameManager() {

	isDone = false;

	nGraphics = GameGraphics::getInstance();

	if (!GameGraphics::getInitialized())
		isDone = true;
}