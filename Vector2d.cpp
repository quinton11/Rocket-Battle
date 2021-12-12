#include "Vector2d.h"
#include "cmath"


int Vector2d::magnitude() {
	//find magnitude of vector
	//sqrt(x^2 + y^2)
	int mag =  0;
	mag = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return mag;
}


Vector2d::Vector Vector2d::normalize() {
	//return vector divided by its magnitude
	int mag = magnitude();
	Vector vnorm = { vec.x/mag, vec.y/mag };

	return vnorm;
}

void Vector2d::rotate(double angle) {
	rotmat.calcrotation(angle);
	// x' = xcos(angle) - ysin(angle) 
	int xrot = (vec.x * rotmat.x1) + (vec.y * rotmat.y1);

	// y' = xsin(angle) - ycos(angle)
	int yrot = (vec.x * rotmat.x2) + (vec.y * rotmat.y2);

	vec.x = xrot;
	vec.y = yrot;
}

void Vector2d::setvector(int x, int y) {
	vec.x = x;
	vec.y = y;
}


Vector2d::Vector2d(int x, int y) {
	vec.x = x;
	vec.y = y;
}

Vector2d::Vector2d(){}