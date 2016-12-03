#include "Displayable.h"


Displayable::Displayable()
{
	rect.setSize(getSize());
	rect.setOrigin(getSize() / 2.f);
	rect.setPosition(getPos());
	//sprite.setOrigin(getSize() / 2.f);
	sprite.setPosition(getPos());
	//rect.setOrigin(getPos());// / 2.f);
	//rect.setSize(getSize());
	//sprite.setOrigin(getSize() / 2.f);
	tex = NULL;
	update();
}

Displayable::~Displayable()
{
}

void Displayable::update()
{
	rect.setOrigin(getSize() / 2.f);
	rect.setPosition(getPos());
	rect.setRotation(getAngle());
	sprite.setOrigin(getSize() / 2.f);
	sprite.setPosition(getPos());
	sprite.setRotation(getAngle());
	//rect.setPosition(getPos());// - getSize() / 2.f);
	//sprite.setPosition(rect.getPosition());
	//sprite.setRotation(getAngle());
}

void Displayable::draw(RenderWindow& win)
{
	//Transform t;
	//t.rotate(getAngle(), getPos());
	/*CircleShape c;
	c.setRadius(rect.getSize().x);
	c.setOrigin(c.getPosition() + Vector2f(c.getRadius(), c.getRadius()));
	c.setPosition(getPos());
	win.draw(c);*/
	win.draw(sprite);// , t);
}