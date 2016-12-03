#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "Entity.h"

class Displayable :
	public Entity
{
public:
	Displayable();
	~Displayable();

	void update();
	void draw(RenderWindow& win);

protected:
	RectangleShape rect;
	Texture* tex;
	Sprite sprite;

};

#endif