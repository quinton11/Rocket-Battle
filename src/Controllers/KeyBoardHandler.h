#pragma once
#include "SDL.h"
#include "..\Entities\Rocket.h"
#include "..\Entities\BulletManager.h"
class KeyboardHandler
{
private:
	static KeyboardHandler *khandler_instance;

public:
	static KeyboardHandler *instance();
	static void release();
	void keyboard_input(const Uint8 *state, Rocket *rocket, float dt);
	void keyboard_events(SDL_Event &event, bool &isDone);

private:
	KeyboardHandler();
	~KeyboardHandler();
};