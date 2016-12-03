#ifndef PROJECTILE_H

#define PROJECTILE_H

#include "Displayable.h"
class Projectile :
	public Displayable
{
public:
	Projectile();
	~Projectile();

	void init(Vector2f _position, float _dir, float _velocity, int _life, Texture* _tex);
	void init(Vector2f _position, float _dir, float _velocity, int _life);

	void update(Time& elapsed);
	void destroy();
	bool isDestroyed();


private:
	float dir;
	float velocity;
	Counter life;
};

#endif