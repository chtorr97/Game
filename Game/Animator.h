#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "utility.h"

using namespace std;
using namespace sf;

class Animator
{
public:
	Animator();
	Animator(int _changeRate, Vector2f _origin, Vector2f _size, Texture* _tex, Vector2i _disposition);
	Animator(const Animator& other);
	~Animator();

	void next();
	const IntRect get(Time elapsed);
	const IntRect get(int frame);

	void randomAnimation();
	void invert();

	Texture* getTexture() { return tex; }
	Vector2f getSize() { return size; }

	Animator& operator=(Animator arg);

private:
	Vector2f origin; //starting point
	int counter; //current pic
	Counter changer;
	Vector2i disposition; //frame disposition
	Vector2f size;
	Texture* tex;
	bool inversion; //make the animation run backward
};

#endif