#pragma once
#include "SDL.h"
#include "GameEntity.h"

class Rocket: public GameEntity{

public:
	SDL_Rect rect;
private:
	SDL_Point a = {350,300}, b = {335,340}, c = {365,340};
	int speed = 10;

	

public:
	Rocket();
	~Rocket();

	void update();
	void render(SDL_Renderer* renderer);
	void moveleft();
	void moveright();
	void moveup();
	void movedown();

};