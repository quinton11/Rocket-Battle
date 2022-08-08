#include "TimeSetting.h"


float TimeSetting::getDeltaTime() {
	previoustime = currenttime;
	currenttime = SDL_GetTicks();

	deltatime = currenttime - previoustime;

	return deltatime;
}