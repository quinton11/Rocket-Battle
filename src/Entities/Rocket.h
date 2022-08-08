#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "..\VectorMath\Vector2d.h"

class Rocket: public GameEntity{

public:
	SDL_FRect rect;
	Vector2d rectvec;
	Vector2d centervec;
	Vector2d rotvec;
	Vector2d changevec;

	bool thrust = false;
	bool reverse = false;

private:
	double speed = 70.0f;
	double max_speed = 200.0f;
	double speed_ph = 70.0f;
	double tspeed = 0;
	double angle = 0.0f;
	double ang_inv = 0.0f;
	double rot_speed = 90.0f;
	double degtorad = 0.017453f;
	
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
	void set_speed(double sp);

	void calc_rotvec();

	void calc_center();

};