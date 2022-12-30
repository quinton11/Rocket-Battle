#include "Rocket.h"
#include "iostream"
#include "cmath"
#include "tuple"

void Rocket::update(double dt)
{

	// Speed after multiplying with deltatime
	// If thrust increase speed gradually till maximum speed
	if (thrust)
	{
		// std::cout << "Rocket thrust" << "\n";
		if (speed_ph < max_speed)
		{
			speed_ph += .2f;
			// std::cout << "Speed Increasing: " << speed_ph << "\n";
		}
	}
	else
	{
		// Check if speed place holder is greater than normal speed
		// If yes reduce speed gradually
		if (speed_ph > speed)
		{
			speed_ph -= .1f;
			tspeed = (speed_ph * (dt / 1000.0f));
			deltax = (tspeed * sin(angle * degtorad));
			deltay = -1 * (tspeed * cos(angle * degtorad));
		}
		if ((speed_ph > speed) && reverse)
		{
			speed_ph -= .2f;
			tspeed = (speed_ph * (dt / 1000.0f));
			deltax = (tspeed * sin(angle * degtorad));
			deltay = -1 * (tspeed * cos(angle * degtorad));
		}
		// speed_ph = speed;
	}

	tspeed = (speed_ph * (dt / 1000.0f));

	rect.x = rect.x + (float)(deltax);
	rect.y = rect.y + (float)(deltay);

	calc_center();

	// Zeroing out changes in x and y
	deltax = 0;
	deltay = 0;
	thrust = false;
	// tspeed = 0;
	// changevec.setvector(deltax, deltay);
}

void Rocket::aimPoint()
{
	// calculate rotated point using angle and centre of rect
	// formula for rotated point
}

void Rocket::takeHit(CustomEnums::Entity e)
{
	if (e == CustomEnums::Entity::Bullet)
	{
		// Bullet collision
		if (health >= 0)
		{
			health -= 0.05;
		}
	}
	else if (e == CustomEnums::Entity::Rock)
	{
		// Rock collision
	}
	else if (e == CustomEnums::Entity::Enemy)
	{
		// Enemy collision
	}
}

void Rocket::calcHealthP()
{
	//
	if (health > healthMax)
	{
		health = healthMax;
	}
	else if (health < 0.0f)
	{
		health = 0.0f;
	}
	healthPercent = (health / healthMax) * 1.0f;
}

bool Rocket::gameOver()
{
	if (health <= 0.0f)
	{
		Mix_PlayChannel(2, SoundManager::player_dead, 0);
		return true;
	}
	return false;
};

void Rocket::renderHealthBar(SDL_Renderer *renderer)
{
	// calc health percentage
	calcHealthP();

	// use percentage to render life
	// RED BACKGROUND
	float bgx = rect.x - 10;
	float bgy = rect.y + rect.h + 10;
	float bgw = rect.w + 20;
	float bgh = 2;
	SDL_FRect bgrect = {bgx, bgy, bgw, bgh};
	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	// SDL_RenderFillRectF(renderer, &bgrect);
	//  GREEN FOREGROUND
	// SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	// std::cout << "In rocket " << healthPercent << std::endl;
	float fw = bgw * healthPercent;
	float fx = bgx + (bgw - fw);
	SDL_FRect fgrect = {fx, bgy, fw, bgh};
	// SDL_RenderFillRectF(renderer, &fgrect);
	//  Setting color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Rocket::render(SDL_Renderer *renderer, SDL_Texture *texture, double dt)
{

	update(dt);

	SDL_RenderCopyExF(renderer, texture, nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	// SDL_RenderDrawLineF(renderer, (rect.x + rect.w / 2), (rect.y), (rect.x + rect.w / 2), (rect.y - 40.f));
	// SDL_RenderDrawPointF(renderer, rect.x, rect.y);

	renderHealthBar(renderer);
}
bool Rocket::collision(SDL_FRect other)
{
	// Check for collision with other rect
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	// Sides of Bullet rect
	leftA = rect.x;
	rightA = rect.x + rect.w;
	topA = rect.y;
	bottomA = rect.y + rect.h;

	// Sides of other rect
	leftB = other.x;
	rightB = other.x + other.w;
	topB = other.y;
	bottomB = other.y + other.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

void Rocket::calc_rotvec()
{

	/*//Get center of rocket
	calc_center();

	float cx=0.0;
	float cy = 0.0;
	std::tie(cx,cy) = centervec.getvector();

	//SDL 2 rotates clockwise
	ang_inv = abs(360 - angle);

	//Calculating rotvec after rotation
	float x_rot = ((rectvec.getx() - cx) * cos(ang_inv*degtorad)) - ((cy - rectvec.gety()) * sin(ang_inv*degtorad)) + cx;
	float y_rot = cy - ((cy-rectvec.gety()) * cos(ang_inv* degtorad)) + ((rectvec.getx() - cx) * sin(ang_inv* degtorad));

	rotvec.setvector(x_rot, y_rot);*/
}

void Rocket::moveleft(double dt)
{

	if (angle <= 0)
	{
		angle = 360;
	}

	angle -= rot_speed * (dt / 1000);
}

void Rocket::moveright(double dt)
{

	if (angle >= 360.f)
		angle = 0;

	angle += rot_speed * (dt / 1000);
}

void Rocket::movedown()
{

	thrust = false;
	reverse = true;

	deltax = -(tspeed * sin(angle * degtorad));
	deltay = 1 * (tspeed * cos(angle * degtorad));
}

void Rocket::Fdirection(float &sx, float &sy)
{
	sx = cos(angle * degtorad);
	sy = sin(angle * degtorad);
	float an = atan2(-deltay, -deltax) * 180 / 3.147;
	std::cout << an << ":Angle" << std::endl;
	std::cout << angle << ":angle" << std::endl;
}

void Rocket::moveup()
{

	thrust = true;

	deltax = (tspeed * sin(angle * degtorad));
	deltay = -1 * (tspeed * cos(angle * degtorad));

	dirvec.setvector(sin(angle * degtorad), (-1 * cos(angle * degtorad)));
}

Vector2d Rocket::getDirection()
{
	return dirvec;
}

void Rocket::set_speed(float sp)
{
	speed_ph = sp;
}

float Rocket::getAngle()
{
	return angle;
}

void Rocket::calc_center()
{
	int cx = 0;
	int cy = 0;

	// Setting rectvector
	rectvec.setvector(rect.x, rect.y);

	cx = (int)(rect.x + rect.w / 2);
	cy = (int)(rect.y + rect.h / 2);
	// centervec.setvector(cx, cy);
}

void Rocket::reset()
{
	rect.x = 300;
	rect.y = 350;
	health = 50.0f;
	kills = 0;
	LevelManager::changelevel(kills);
}

Rocket::Rocket()
{
	rect.x = 300;
	rect.y = 350;
	rect.w = 60;
	rect.h = 45;

	dPacket = 0;
	vPacket = 0;
	bPacket = 0;

	rectvec.setvector(rect.x, rect.y);
	rotvec.setvector(rect.x, rect.y);
}
void Rocket::addHealth(float add)
{
	health += add;
}

Rocket::~Rocket()
{
}

/* Game Over Screen if rocket health is empty */