#pragma once
#include "SDL.h"
#include "GameEntity.h"
#include "..\VectorMath\Vector2d.h"
#include "..\Utils\CustomEnums.h"

class Rocket : public GameEntity
{

public:
	SDL_FRect rect;
	Vector2d rectvec;
	Vector2d centervec;
	Vector2d rotvec;
	Vector2d dirvec; // Direction vector
	Vector2d changevec;

	bool thrust = false;
	bool reverse = false;
	float healthPercent = 1.0f;

private:
	float speed = 70.0f;
	float score = 0.0f;
	float max_speed = 200.0f;
	float speed_ph = 70.0f;
	float tspeed = 0;
	float angle = 0.0f;
	float ang_inv = 0.0f;
	float rot_speed = 120.0f; // 90.0f 150.0f
	float degtorad = 0.017453f;

	float deltax = 0;
	float deltay = 0;
	float health = 50.0f;
	float healthMax = 20.0f;
	/* float dPacket=0;
	float bPacket=0;
	float vPacket=0; */

public:
	Rocket();
	~Rocket();
	float dPacket = 0;
	float bPacket = 0;
	float vPacket = 0;
	void takeHit(CustomEnums::Entity e);
	void update(double dt);
	void render(SDL_Renderer *renderer, SDL_Texture *texture, double dt);
	void renderHealthBar(SDL_Renderer *renderer);
	void reset();
	void addHealth(float add);

	void moveleft(double dt);
	void moveright(double dt);
	void moveup();
	void movedown();
	float getAngle();
	void set_speed(float sp);
	void aimPoint();
	void calcHealthP();
	bool collision(SDL_FRect other);
	bool gameOver();

	Vector2d getDirection();

	void Fdirection(float &sx, float &sy);

	void calc_rotvec();

	void calc_center();
};