#include "HomeScreen.h"
#include "iostream"

//SDL_Texture* HomeScreen::screentexture = textm.loadTexture("textures/universe.png", renderer);
void HomeScreen::render(SDL_Renderer* renderer) {

	SDL_Texture* play = textm.loadTexture("textures/gamepad.png",renderer);
	while (ismounted) {
		//Check events
		HomeScreen::eventchecker();
		//Render Image to window
		SDL_RenderCopy(renderer, screentexture, NULL, NULL);
		SDL_RenderCopy(renderer, play, NULL, &play_rect);
		SDL_RenderPresent(renderer);
	}
	
	HomeScreen::~HomeScreen();
	
}

void HomeScreen::eventchecker() {
	SDL_PollEvent(&events);
	switch (events.type) {
	case SDL_QUIT:
		ismounted = false;
		quit = true;
		//SDL_Quit();
		break;

	case SDL_MOUSEMOTION:
		mouse_x = events.motion.x;
		mouse_y = events.motion.y;


	case SDL_MOUSEBUTTONDOWN:
		//std::cout << "Mouse clicker" << std::endl;
		if (events.button.button == SDL_BUTTON_LEFT && HomeScreen::mouse_in_play(mouse_x, mouse_y, play_rect)) {
			std::cout << "Mouse clicker" << std::endl;
			ismounted = false;
		}
			
		
	}

	
}

bool HomeScreen::mouse_in_play(int& x, int& y, SDL_Rect& rect) {
	return (x >= rect.x) && (y >= rect.y) &&
		(x < rect.x + rect.w) && (y < rect.y + rect.h);
}

bool HomeScreen::getismounted() {
	return ismounted;
}

bool HomeScreen::getisquit() {
	return quit;
}

void HomeScreen::setismounted(bool is) {
	ismounted = is;
}

HomeScreen::HomeScreen(SDL_Renderer *renderer) {
	screentexture = textm.loadTexture("textures/amongus2.png", renderer);
}


HomeScreen::~HomeScreen() {
	//delete screentexture;
	//delete events;

	screentexture = NULL;
}