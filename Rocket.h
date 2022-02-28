#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "Vector2d.h"

class Rocket: public GameEntity{

public:
	SDL_FRect rect;
	Vector2d rectvec;
	Vector2d centervec;
	Vector2d rotvec;
	Vector2d changevec;

private:
	double speed = 50.0f;
	double tspeed = 0;
	double angle = 0.0f;
	double ang_inv = 0.0f;
	double rot_speed = 50.0f;
	double degtorad = 0.017453f;
	bool thrust = false; 

	double deltax = 0;
    double deltay = 0;

	

public:
	Rocket();
	~Rocket();

	void update(double dt);
	void render(SDL_Renderer* renderer, SDL_Texture* texture,double dt);
	void moveleft(double dt);
	void moveright(double dt);
	void moveup();
	void movedown();

	void calc_rotvec();

	void calc_center();

};