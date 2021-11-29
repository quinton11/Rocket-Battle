#include <iostream>

#include "SDL.h"
#undef main


int main() {
	//start build
	SDL_Init(SDL_INIT_EVERYTHING);

	//Window
	SDL_Window* window = SDL_CreateWindow("Rocket Battle",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600,400,0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	bool gameIsRunning = true;

	/*
	Draw a rectangle which moves in the direction of key stroke
	*/

	//rectangle
	SDL_Rect firstrect;

	firstrect.x = 20;
	firstrect.y = 20;
	firstrect.w = 10;
	firstrect.h = 10;

	while (gameIsRunning) {
		SDL_Event event;

		
		//Check event queue to exeute events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameIsRunning = false;
			}

			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP]) {
				firstrect.y -= 5;
				std::cout << "UP" << std::endl;
			}
			else if (state[SDL_SCANCODE_DOWN]) {
				firstrect.y += 5;
				std::cout << "DOWN" << std::endl;
			}
			else if (state[SDL_SCANCODE_RIGHT]) {
				firstrect.x += 5;
				std::cout << "RIGHT" << std::endl;
			}
			else if (state[SDL_SCANCODE_LEFT]) {
				firstrect.x -= 5;
				std::cout << "LEFT" << std::endl;
			}
		}

		//Set render color for window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//Clear renderer target, in this case the window
		SDL_RenderClear(renderer);


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		//Draw rectangle
		SDL_RenderDrawRect(renderer, &firstrect);
		SDL_RenderFillRect(renderer, &firstrect);

		//Update screen
		SDL_RenderPresent(renderer);
	}

	//SDL_Delay(5000);

	SDL_Quit();

	return 0;
}