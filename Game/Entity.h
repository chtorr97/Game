#ifndef ENTITY_H
#define ENTITY_H

#include<SFML\Graphics.hpp>
#include<iostream>

#include "Animator.h"

using namespace std;
using namespace sf;

class Entity
{
public:
	Entity();
	~Entity();

	bool intersects(Entity* e); //as circles

	void setPos(Vector2f newPos) { pos = newPos; }
	void move(Vector2f movement) { pos += movement; }
	Vector2f getPos() { return pos; }

	void setAngle(float newAngle) { angle = fmod(newAngle, 360); if (angle < 0) angle += 360; }
	void rotate(float rotation) { angle = fmod(angle + rotation, 360); if (angle < 0) angle += 360; }
	float getAngle() { return angle; }

	void setSize(Vector2f newSize) { size = newSize; }
	void setSizeX(float x) { size.x = x; }
	void setSizeY(float y) { size.y = y; }
	void scale(float factor) { size *= factor; }
	Vector2f getSize() { return size; }

	//add flag for intersections -> square to circle, circle to circle, etc

private:
	Vector2f pos;
	float angle;
	Vector2f size;
};

#endif