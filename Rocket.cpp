#include "Rocket.h"
#include "iostream"
#include "cmath"

void Rocket::update() {

	rect.x += deltax;
	rect.y += deltay;
}

void Rocket::render(SDL_Renderer* renderer, SDL_Texture* texture) {
	//Setting Draw Color
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, NULL, SDL_FLIP_NONE);

}


void Rocket::moveleft(double dt) {
	/*std::cout << "Delta Time: " << dt << std::endl;
	
	deltax = (speed * (dt / 1000.0f));


	rect.x -= deltax;*/

	if (angle == 0) {
		angle = 360;
	}

	angle -= rot_speed * (dt/10 );

}

void Rocket::moveright(double dt) {
	/*std::cout << "Delta Time: " << dt << std::endl;
	deltax = (speed * (dt / 1000.0f));

	rect.x = ceil(rect.x + deltax);*/
	std::cout << "X y position before rotation: " << rect.x << "," << rect.y << std::endl;

	if (angle == 360.f)
		angle = 0;

	angle += rot_speed * (dt/10);
	std::cout<<"X y position after rotation: " << rect.x << "," << rect.y << std::endl;

	

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

void Rocket::calc_center() {
	int cx = 0;
	int cy = 0;

	cx = rect.x / 2;
	cy = rect.y / 2;
	centervec.setvector(cx, cy);
}


Rocket::Rocket() {
	rect.x = 400;
	rect.y = 400;
	rect.w = 60;
	rect.h = 50;

	rectvec.setvector(rect.x, rect.y);
	rotvec.setvector(rect.x, rect.y); 
}

Rocket::~Rocket() {

}