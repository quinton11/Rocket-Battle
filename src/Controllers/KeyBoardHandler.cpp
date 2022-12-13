#include "KeyBoardHandler.h"
#include "..\Screens\PauseScreen.h"

KeyboardHandler *KeyboardHandler::khandler_instance = NULL;

KeyboardHandler *KeyboardHandler::instance()
{
	if (khandler_instance == NULL)
		khandler_instance = new KeyboardHandler();

	return khandler_instance;
}

void KeyboardHandler::release()
{
	delete khandler_instance;

	khandler_instance = NULL;
}

void KeyboardHandler::keyboard_input(const Uint8 *state, Rocket *rocket, float dt)
{
	SDL_PumpEvents();
	SDL_Event event;
	if (state[SDL_SCANCODE_UP])
	{
		rocket->moveup();
	}
	if (!state[SDL_SCANCODE_UP])
	{
		// Resetting placeholder speed to normal speed
		// rocket.set_speed(70.0f);
		rocket->thrust = false;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		rocket->reverse = true;
		rocket->movedown();
	}
	if (!state[SDL_SCANCODE_DOWN])
	{
		rocket->reverse = false;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		rocket->moveright(dt);
		// std::cout << "RIGHT" << std::endl;
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		rocket->moveleft(dt);
		// std::cout << "LEFT" << std::endl;
	}
	if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
	{
		rocket->moveup();
		rocket->moveleft(dt);
	}
	if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
	{
		rocket->moveup();
		rocket->moveright(dt);
	}
	if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT])
	{
		rocket->movedown();
		rocket->moveleft(dt);
	}
	if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT])
	{
		rocket->movedown();
		rocket->moveright(dt);
	}
}

void KeyboardHandler::keyboard_events(SDL_Event &event, bool &isDone, Rocket *rocket, BulletManager *bm)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isDone = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				PauseScreen::active = true;
			}
		}
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_s))
		{
			// std::cout << "Shoot" << std::endl;
			//  Calculate bullets starting position which will be the rockets top middle
			//  the rockets top middle with respect to its angle of rotation
			// std::cout << rocket->rect.x << "," << rocket->rect.y << std::endl;
			float cx = ((rocket->rect.x) + (rocket->rect.w / 2));
			float cy = ((rocket->rect.y) + (rocket->rect.h / 2));
			float angle = rocket->getAngle();
			// std::cout <<"Making bullet with centres: "<< cx << "," << cy << std::endl;
			bm->makeBullet(cx, cy, angle, true);

			// the bullets direction will be the direction the rocket is facing

			// For player,when key is pressed,
			// Call make bullet function which adds a new bullet with
			// its starting position and direction
			// then in game manager, every iteration,the bullets position
			// are updated and rendered
		}
	}
}

KeyboardHandler::KeyboardHandler()
{
}
KeyboardHandler::~KeyboardHandler() {}