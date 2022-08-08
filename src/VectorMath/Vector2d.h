#pragma once
#include "cmath"
#include "iostream"
class Vector2d {

private:
	struct Vector {
		float x;
		float y;

		Vector operator+(Vector& obj) {
			Vector res = { 0,0 };
			res.x = this->x + obj.x;
			res.y = this->y + obj.y;
		};

		Vector operator-(Vector& obj) {
			Vector res = { 0,0 };
			res.x = this->x - obj.x;
			res.y = this->y - obj.y;
		};
	};

	//Matrix
	/*
	     x1 y1
		 x2 y2
	*/
	struct Matrix {
		float angle = 0;

		float x1 = cos(angle);
		float y1 = -sin(angle);
		float x2 = sin(angle);
		float y2 = cos(angle);

		void calcrotation(double ang) {
			angle = (float)(ang);
			x1 = cos(angle);
			y1 = -sin(angle);
			x2 = sin(angle);
		    y2 = cos(angle);
		}
	};
	Vector vec = {0,0};
	Matrix rotmat;




public:

	Vector2d(float x, float y);
	Vector2d();

	float magnitude();
	Vector2d normalize();
	void rotate(double angle);
	void setvector(float x, float y);
	std::tuple<float,float> getvector();
	float getx();
	float gety();
	void printvector();
};