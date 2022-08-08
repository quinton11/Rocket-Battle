#pragma once
#include "SDL.h"
#include "..\Entities\Rocket.h"
class KeyboardHandler {
private:
	static KeyboardHandler* khandler_instance;


public:
	static KeyboardHandler* instance();
	static void release();
	void keyboard_input(const Uint8* state, Rocket& rocket,float dt);

private:
	KeyboardHandler();
	~KeyboardHandler();
};