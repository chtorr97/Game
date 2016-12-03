#ifndef UTILITY_H
#define UTILITY_H

#include<SFML\Graphics.hpp>
#include "Counter.h"

using namespace sf;

namespace ut
{
	float mag(const Vector2f& v);
	float magP2(const Vector2f& v);
	//0 -> 360
	float angle(Vector2f& v); // degree
	void limit(Vector2f& v, const float max);
	float angleBetween(const Vector2f& v1, const Vector2f& v2);
	void normalize(Vector2f& v);
	float dist(Vector2f v1, Vector2f v2);
	float distP2(Vector2f v1, Vector2f v2);
	Vector2f toVector(float mag, float angle);
	float map(float value, float startMin, float startMax, float endMin, float endMax);

	const float TO_DEGREE = 180 / 3.14159265358979f;
	const float TO_RADIAN = 3.14159265358979f / 180;
	const Vector2f ZERO_VECTORf = Vector2f(0, 0);
	const Vector2i ZERO_VECTORi = Vector2i(0, 0);
	const Vector2f UNIT_VECTORf = Vector2f(1, 1);
	const Vector2i UNIT_VECTORi = Vector2i(1, 1);
}

#endif