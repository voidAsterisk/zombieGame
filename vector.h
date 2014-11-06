#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdlib.h>

class Vector {

public:
	float x;
	float y;

	Vector(const float& x_, const float& y_) {
		x = x_;
		y = y_;
	}

	Vector(const Vector& vec)
	{
		x = vec.x;
		y = vec.y;
	}

	Vector()
	{
		x = 0;
		y = 0;
	}

	~Vector()
	{
	}

	Vector& operator=(const Vector& rhs);

	Vector& operator+=(const Vector& rhs);

	Vector& operator-=(const Vector& rhs);

	Vector operator+(const Vector& rhs) const;

	Vector operator-(const Vector& rhs) const;

	Vector& operator*=(const float& rhs);

	Vector& operator/=(const float& rhs);

	Vector operator*(const float& rhs) const;

	Vector operator/(const float& rhs) const;

	float magnitude();

	void normalize();

	void limit(const float& n);

	float angle();

	void random();
};

#endif
