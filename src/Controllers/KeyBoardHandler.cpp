#include "KeyBoardHandler.h"

KeyboardHandler* KeyboardHandler::khandler_instance = NULL;

KeyboardHandler* KeyboardHandler::instance() {
	if (khandler_instance == NULL)
		khandler_instance = new KeyboardHandler();

	return khandler_instance;
}

void KeyboardHandler::release() {
	delete khandler_instance;

	khandler_instance = NULL;
}

void KeyboardHandler::keyboard_input(const Uint8* state, Rocket& rocket, float dt) {
	SDL_PumpEvents();

	if (state[SDL_SCANCODE_UP]) {
		rocket.moveup();
	}
	if (!state[SDL_SCANCODE_UP]) {
		//Resetting placeholder speed to normal speed
		//rocket.set_speed(70.0f);
		rocket.thrust = false;
	}
	if (state[SDL_SCANCODE_DOWN]) {
		rocket.reverse = true;
		rocket.movedown();
	}
	if (!state[SDL_SCANCODE_DOWN]) {
		rocket.reverse = false;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		rocket.moveright(dt);
		//std::cout << "RIGHT" << std::endl;
	}
	if (state[SDL_SCANCODE_LEFT]) {
		rocket.moveleft(dt);
		//std::cout << "LEFT" << std::endl;
	}
	if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) {
		rocket.moveup();
		rocket.moveleft(dt);
	}
	if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) {
		rocket.moveup();
		rocket.moveright(dt);
	}
	if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT]) {
		rocket.movedown();
		rocket.moveleft(dt);
	}
	if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]) {
		rocket.movedown();
		rocket.moveright(dt);
	}

}

KeyboardHandler::KeyboardHandler(){}
KeyboardHandler::~KeyboardHandler() {}