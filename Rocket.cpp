#include "Rocket.h"
#include "iostream"
#include "cmath"

void Rocket::update() {

	rect.x += deltax;
	rect.y += deltay;
}

void Rocket::render(SDL_Renderer* renderer) {
	//Setting Draw Color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}


void Rocket::moveleft(double dt) {
	std::cout << "Delta Time: " << dt << std::endl;
	
	deltax = (speed * (dt / 1000.0f));


	rect.x -= deltax;

}

void Rocket::moveright(double dt) {
	std::cout << "Delta Time: " << dt << std::endl;
	deltax = (speed * (dt / 1000.0f));

	rect.x = ceil(rect.x + deltax);

	

}

void Rocket::movedown(double dt) {
	std::cout << "Delta Time: " << dt << std::endl;
	deltay = (speed * (dt / 1000.0f));

	

	rect.y = ceil(rect.y + deltay);

	
}

void Rocket::moveup(double dt) {
	std::cout << "Delta Time: " << dt << std::endl;
	deltay = (speed * (dt / 1000.0f));


	rect.y -= deltay;

}


Rocket::Rocket() {
	rect.x = 400;
	rect.y = 400;
	rect.w = 60;
	rect.h = 50;
}

Rocket::~Rocket() {

}