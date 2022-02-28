#include "Rocket.h"
#include "iostream"
#include "cmath"
#include "tuple"

void Rocket::update(double dt) {

	//Speed after multiplying with deltatime
	tspeed = (speed * (dt / 1000.0f));

	//if (thrust) 
		//std::cout << "Rect before movement: (" << rect.x << "," << rect.y << ")" << std::endl;
	

	rect.x = rect.x + deltax;
	rect.y = rect.y + deltay;
	
	//if (thrust)
		//std::cout << "Rect after movement: (" << rect.x << "," << rect.y << ")" << std::endl;

		
	calc_center();
	
	//Zeroing out changes in x and y
	deltax = 0;
	deltay = 0;
	thrust = false;
	//tspeed = 0;
	changevec.setvector(deltax, deltay);

}

void Rocket::render(SDL_Renderer* renderer, SDL_Texture* texture,double dt) {
	
	update(dt);
	//angle in degrees
	SDL_RenderCopyExF(renderer, texture, nullptr, &rect, angle, NULL, SDL_FLIP_NONE);

}


void Rocket::calc_rotvec() {

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



void Rocket::moveleft(double dt) {
	

	if (angle <= 0) {
		angle = 360;
	}

	angle -= rot_speed * (dt/1000 );

}

void Rocket::moveright(double dt) {

	if (angle >= 360.f)
		angle = 0;

	angle += rot_speed * (dt/1000);

}

void Rocket::movedown() {
	
	thrust = true;

	deltax = -(tspeed * sin(angle * degtorad));
	deltay = 1 * (tspeed * cos(angle * degtorad));
		
}

void Rocket::moveup() {
	
	thrust = true;
	
	deltax = (tspeed * sin(angle * degtorad));
	deltay = -1 * (tspeed * cos(angle * degtorad));

}

void Rocket::calc_center() {
	int cx = 0;
	int cy = 0;

	//Setting rectvector
	rectvec.setvector(rect.x, rect.y);

	cx = (rect.x + rect.w/2);
	cy = (rect.y + rect.h/2);
	centervec.setvector(cx, cy);
}


Rocket::Rocket() {
	rect.x = 300;
	rect.y = 350;
	rect.w =50;
	rect.h = 45;

	rectvec.setvector(rect.x, rect.y);
	rotvec.setvector(rect.x, rect.y); 
}

Rocket::~Rocket() {

}