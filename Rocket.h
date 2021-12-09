#pragma once
#include "SDL.h"
#include "GameEntity.h"

class Rocket: public GameEntity{

public:
	SDL_Rect rect;
private:
	double speed = 10.0f;
	double angle = 3.0f;
	double rot_speed = 10.0f;
	double DEGTORAD = 0.017453f;
	bool thrust = false; 
	double deltax = 0;
    double deltay = 0;

	

public:
	Rocket();
	~Rocket();

	void update();
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
	void moveleft(double dt);
	void moveright(double dt);
	void moveup(double dt);
	void movedown(double dt);

};