#pragma once
#include "SDL.h"


class TimeSetting {

public:
	float getDeltaTime();

private:
	float deltatime= 0.f;
	float currenttime = 0.f;
	float previoustime = 0.f;
};