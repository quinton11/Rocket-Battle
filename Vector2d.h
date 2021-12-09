#pragma once
class Vector2d {

private:
	struct Vector {
		int x;
		int y;
	};



public:

	int magnitude();
	Vector normalize();
	Vector add();
	Vector subtract();
	Vector rotate(double angle);
	Vector getvector();
};