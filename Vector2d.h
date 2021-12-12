#pragma once
#include "cmath"
class Vector2d {

private:
	struct Vector {
		int x;
		int y;

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
		double angle = 0;

		int x1 = cos(angle);
		int y1 = -sin(angle);
		int x2 = sin(angle);
		int y2 = cos(angle);

		void calcrotation(double ang) {
			angle = ang;
			x1 = cos(angle);
			y1 = -sin(angle);
			x2 = sin(angle);
		    y2 = cos(angle);
		}
	};
	Vector vec;
	Matrix rotmat;




public:

	Vector2d(int x, int y);
	Vector2d();

	int magnitude();
	Vector normalize();
	void rotate(double angle);
	void setvector(int x, int y);
};