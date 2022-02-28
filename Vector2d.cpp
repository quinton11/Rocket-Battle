#include "Vector2d.h"
#include "cmath"
#include "iostream"
#include "tuple"


int Vector2d::magnitude() {
	//find magnitude of vector
	//sqrt(x^2 + y^2)
	float mag =  0;
	mag = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return mag;
}


Vector2d Vector2d::normalize() {
	//return vector divided by its magnitude
	float mag = magnitude();
	//Vector vnorm = { vec.x/mag, vec.y/mag };
	Vector2d vnorm;
	vnorm.setvector(vec.x / mag, vec.y / mag);

	return vnorm;
}

void Vector2d::rotate(double angle) {
	rotmat.calcrotation(angle);
	// x' = xcos(angle) - ysin(angle) 
	float xrot = (vec.x * rotmat.x1) + (vec.y * rotmat.y1);

	// y' = xsin(angle) - ycos(angle)
	float yrot = (vec.x * rotmat.x2) + (vec.y * rotmat.y2);

	vec.x = xrot;
	vec.y = yrot;
}

void Vector2d::setvector(float x, float y) {
	vec.x = x;
	vec.y = y;
}

void Vector2d::printvector() {
	std::cout <<"("<< vec.x << ", " << vec.y << ")" << std::endl;
}

float Vector2d::getx() {
	return vec.x;
}

float Vector2d::gety() {
   
	return vec.y;
}


std::tuple<float,float> Vector2d::getvector() {
	float x = getx();
	float y = gety();
	return std::make_tuple(x, y);
}


Vector2d::Vector2d(float x, float y) {
	vec.x = x;
	vec.y = y;
}

Vector2d::Vector2d() {};