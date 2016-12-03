#ifndef POINTER_H
#define POINTER_H

#include <SFML\Graphics.hpp>
#include "Entity.h"

using namespace sf;

class Pointer
{
public:
	Pointer();
	Pointer(RenderWindow* _window, View* _view, Entity* _focus);

	void init(RenderWindow* _window, View* _view, Entity* _focus);

	void update();

	const inline RectangleShape getCursor() { return cursor; }
	inline void setLimit(Vector2f limit) { lvlSize = limit; }
	inline void setColor(Color c) { color = c; }

private:
	RectangleShape cursor;
	View* view;
	RenderWindow* window;
	Entity* focus;

	Vector2f pos,
		ppos,
		pview, //previous view position
		lvlSize;

	const Vector2f SIZE = Vector2f(10, 10);
	Color color = Color::Red;

	void checkEdges();
};

#endif