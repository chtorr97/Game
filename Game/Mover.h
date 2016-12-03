#ifndef MOVER_H
#define MOVER_H

#include "Animation.h"

static const float SEEK_MOVER = 0.3;

class Mover :
	public Animation
{
public:
	Mover();
	Mover(float _maxSpeed);

	~Mover();

	void init(Vector2f _position, Animator _animator);

	void update(Time& elapsed);
	void addForce(Vector2f force);
	void addForce(float x, float y);
	void look(Vector2f target, Time elapsed = milliseconds(1));
	void look(float angle, Time elapsed = milliseconds(1));
	void moveFwd();
	void seek(Vector2f target);
	void seek(Mover target);
	void steerSeek(Vector2f target);
	void steerSeek(Mover target);
	void wander();
	void arrive(Vector2f target, float range = 100);
	void arrive(Mover target, float range = 100);
	void steerArrive(Vector2f target, float range = 100);
	void steerArrive(Mover target, float range = 100);
	void evade(Vector2f target);
	void evade(Mover target);
	void steerEvade(Vector2f target);
	void steerEvade(Mover target);
	void separate(vector<Mover>* group, float separation = 150);
	void cohesion(vector<Mover>* group, float force);
	void align(vector<Mover>* group, float radius = 500, Time elapsed = milliseconds(1));
	void speedMod(float amount);

	const inline Vector2f getVelocity() { return velocity; }
	const inline Vector2f getAcceleration() { return acceleration; }
	const inline float getMaxSpeed() { return maxSpeed; }
	inline void setMaxSpeed(float _maxSpeed) { maxSpeed = _maxSpeed; }
	const inline float getAngularVelocity() { return aVelocity; }
	inline void setAngularVelocity(float angularVelocity) { aVelocity = angularVelocity; }
	const inline float getSpeedModifier() { return speedModifier; }
	inline void setSpeedModifier(float speedMod) { speedModifier = speedMod; }

private:
	Vector2f velocity;
	Vector2f acceleration;
	float maxSpeed;
	float maxForce;
	float aVelocity = 1.5;
	float speedModifier = 1;
};

#endif