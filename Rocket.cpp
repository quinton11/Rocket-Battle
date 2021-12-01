#include "Rocket.h"

void Rocket::update() {
	//connect lines
	
}

void Rocket::render(SDL_Renderer* renderer) {
	//Setting Draw Color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


	SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
	SDL_RenderDrawLine(renderer, a.x, a.y, c.x, c.y);
	SDL_RenderDrawLine(renderer, b.x, b.y, c.x, c.y);
}

void Rocket::movedown() {
	//adjust all y values by speed
	/*a.y += speed;
	b.y += speed;
	c.y += speed;*/
	rect.y += speed;
}

void Rocket::moveup() {
	/*a.y -= speed;
	b.y -= speed;
	c.y -= speed;*/
	rect.y -= speed;
}

void Rocket::moveleft() {
	/*a.x -= speed;
	b.x -= speed;
	c.x -= speed;*/
	rect.x -= speed;
}

void Rocket::moveright() {

	/*a.x += speed;
	b.x += speed;
	c.x += speed;*/
	rect.x += speed;
}

Rocket::Rocket() {
	rect.x = 200;
	rect.y = 400;
	rect.w = 70;
	rect.h = 60;
}

Rocket::~Rocket() {

}