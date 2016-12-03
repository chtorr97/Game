#include "Displayable.h"



Displayable::Displayable()
{
	rect.setSize(getSize());
	tex = NULL;
	update();
}


Displayable::~Displayable()
{
}

void Displayable::update()
{
	rect.setPosition(getPos() - getSize() / 2.f);
	sprite.setPosition(rect.getPosition());
}

void Displayable::draw(RenderWindow& win)
{
	Transform t;
	t.rotate(getAngle(), getPos());
	/*CircleShape c;
	c.setRadius(rect.getSize().x);
	c.setOrigin(c.getPosition() + Vector2f(c.getRadius(), c.getRadius()));
	c.setPosition(getPos());
	win.draw(c);*/
	win.draw(sprite, t);
}