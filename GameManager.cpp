#include "gamemanager.h"
#include "iostream"
#include "Rocket.h"
#include "TextureManager.h"
#include "HomeScreen.h"
#include "TimeSetting.h"
#include "KeyBoardHandler.h"

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
	KeyboardHandler::release();
	nGraphics = NULL;
}

void GameManager::Run() {

	//Rocket object
	Rocket rocket = Rocket();
	TextureManager txman = TextureManager();
	SDL_Texture* texture = txman.loadTexture("textures/rocken.png", nGraphics->getrenderer());
	HomeScreen homescreen = HomeScreen(nGraphics->getrenderer());
	KeyboardHandler* kb_handler = KeyboardHandler::instance();

	//TimeSetting
	TimeSetting tset = TimeSetting();

	float dt; 
	const Uint8* state = SDL_GetKeyboardState(NULL);


	
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

			//keyboard input
			kb_handler->keyboard_input(state, rocket, dt);


			//single hit keys
			// 
			//SDL Poll Event logs every event in some sort of ds .
			
			//Check event queue to exeute events
			while (SDL_PollEvent(&nevents)) {
				if (nevents.type == SDL_QUIT) {
					isDone = true;
				}
				
			}

			 //Renderscreen
			 nGraphics->render();

			 //Render rocket

			 rocket.render(nGraphics->getrenderer(), texture,dt);

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