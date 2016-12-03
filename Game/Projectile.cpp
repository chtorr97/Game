#include "Projectile.h"

Projectile::Projectile()
{
	Displayable();
	velocity = 0;
}

Projectile::~Projectile()
{
	tex = NULL;
	delete tex;
}

void Projectile::init(Vector2f _position, float _dir, float _velocity, int _life, Texture* _tex)
{
	life.init(_life);
	setSize({ 15, 15 });
	rect.setSize(getSize());
	setPos(_position);
	velocity = _velocity;
	dir = _dir;
	tex = _tex;
	sprite.setTexture(*tex);
}

void Projectile::init(Vector2f _position, float _dir, float _velocity, int _life)
{
	life.init(_life);
	//setPos(_position + ut::toVector(10, _dir + 30));
	setPos(_position);
	//use tovector
	velocity = _velocity;
	dir = _dir;
}

void Projectile::update(Time& elapsed)
{
	Displayable::update();

	setPos(getPos() + ut::toVector(velocity, dir) * (elapsed.asMilliseconds() * 1.f));
	setAngle(dir + 90);

	life.add(-elapsed.asMilliseconds());
}

void Projectile::destroy()
{
	life.setEmpty();
}

bool Projectile::isDestroyed()
{
	return life.isEmpty();
}