#include "GGraphics.h"
#include "iostream";


GameGraphics* GameGraphics::gInstance = NULL;
bool GameGraphics::gInitialized = false;



void GameGraphics::render(){
	//Render screen background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//SDL_RenderPresent(renderer);

}


bool GameGraphics::Init(){
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "SDL Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Creating Window
	window = SDL_CreateWindow("Rocket Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);

	if (window == NULL) {
		std::cout<<"Window error: "<<SDL_GetErrorMsg << std::endl;
		return false;
	}
	//renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	return true;

}

//If SDL is initialized set initialized to true
bool GameGraphics::getInitialized() {
	
	return gInitialized;

}

GameGraphics* GameGraphics::getInstance(){
	if (gInstance == NULL)
		gInstance = new GameGraphics();

	return gInstance;
}

void GameGraphics::release(){
	delete gInstance;

	gInstance = NULL;

	gInitialized = false;
}

SDL_Renderer* GameGraphics::getrenderer() {
	return renderer;
}

GameGraphics::GameGraphics() {

	renderer = NULL;
	gInitialized = GameGraphics::Init();
}


GameGraphics::~GameGraphics() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}