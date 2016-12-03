#include "Mover.h"

Mover::Mover()
{
	Animation();
	maxSpeed = 0;
	maxForce = 0;
	acceleration = ut::ZERO_VECTORf;
	velocity = ut::ZERO_VECTORf;
}

Mover::Mover(float _maxSpeed)
{
	Mover();
	maxSpeed = _maxSpeed;
}

Mover::~Mover()
{
}

void Mover::init(Vector2f _position, Animator _animator)
{
	Animation::init(_position, _animator);
}

void Mover::update(Time& elapsed)
{
	Animation::update(elapsed);
	if (acceleration == ut::ZERO_VECTORf)
	{
		Animation::update(0);
	}
	else
	{
		Animation::update(elapsed);
	}

	velocity += acceleration;
	ut::limit(velocity, maxSpeed);
	velocity += velocity * -0.1f;
	velocity *= speedModifier;
	move(velocity * (float)elapsed.asMilliseconds());
	acceleration *= 0.f;
	speedModifier = 1;
}

void Mover::addForce(Vector2f force)
{
	//cout << "Force: " << force.x << " " << force.y << endl;
	acceleration += force;
	//cout << "Acceleration: " << acceleration.x << " " << acceleration.y << endl;
}

void Mover::addForce(float x, float y)
{
	addForce(Vector2f(x, y));
}

void Mover::look(Vector2f target, Time elapsed)
{
	float heading = 180 - atan2(target.x - getPos().x, target.y - getPos().y) * ut::TO_DEGREE;

	look(heading, elapsed);
}

void Mover::look(float angle, Time elapsed)
{
	while (angle < 0)
	{
		angle += 360;
	}

	if (abs(angle - getAngle()) > aVelocity * elapsed.asMilliseconds())
	{
		setAngle(getAngle() + aVelocity * (sin((angle - getAngle()) * ut::TO_RADIAN) >= 0 ? 1 : -1) * elapsed.asMilliseconds());
	}
	else
	{
		setAngle(angle);
	}
}

void Mover::moveFwd()
{
	addForce(ut::toVector(maxSpeed, getAngle() - 90));
}

void Mover::seek(Vector2f target)
{
	Vector2f desired = target - getPos();
	ut::normalize(desired);
	desired *= maxSpeed;
	addForce(desired);
}

void Mover::seek(Mover target)
{
	//seek current position + velocity * k * distance / own velocity
	Vector2f newPos = target.getPos() + target.velocity * (SEEK_MOVER * ut::dist(getPos(), target.getPos())) / (ut::mag(velocity) == 0 ? 1 : ut::mag(velocity));
	seek(newPos);
}

void Mover::steerSeek(Vector2f target)
{
	Vector2f steer = target - getPos();
	ut::normalize(steer);
	steer *= maxSpeed;
	steer -= velocity;
	look(target);
	ut::limit(steer, maxForce);
	addForce(steer);
}

//void Mover::steerSeek(Mover target);
//void Mover::wander();

void Mover::arrive(Vector2f target, float range)
{
	Vector2f desired = target - getPos();

	float d = ut::mag(desired);
	ut::normalize(desired);
	if (d < range) {
		float m = ut::map(d, 0, range, 0, maxSpeed);
		desired *= m;
	}
	else {
		desired *= maxSpeed;
	}

	addForce(desired);
}

void Mover::arrive(Mover target, float range)
{
	Vector2f newPos = target.getPos() + target.velocity * (SEEK_MOVER * ut::dist(getPos(), target.getPos())) / (ut::mag(velocity) == 0 ? 1 : ut::mag(velocity));
	arrive(newPos);
}

//void Mover::steerArrive(Vector2f target, float range = 100);
//void Mover::steerArrive(Mover target, float range = 100);

void Mover::evade(Vector2f target)
{
	Vector2f desired = (target - getPos()) * -1.f;
	ut::normalize(desired);
	desired *= maxSpeed;
	addForce(desired);
}


//void Mover::evade(Mover target);
//void Mover::steerEvade(Vector2f target);
//void Mover::steerEvade(Mover target);

void Mover::separate(vector<Mover>* group, float separation)
{
	Vector2f sum,
		diff;
	int count = 0;
	for (Mover& other : *group) {
		float d = ut::dist(getPos(), other.getPos());
		if ((&other != this) && (d < separation)) {
			diff = getPos() - other.getPos();
			ut::normalize(diff);
			diff /= d;
			sum += diff;
			count++;
		}
	}
	if (count > 0) {
		sum /= (float)count;
		ut::normalize(sum);
		sum *= maxSpeed;
		Vector2f steer = sum - velocity;
		ut::limit(steer, maxForce * 1000);
		addForce(steer);
	}
}

//void Mover::cohesion(vector<Mover>* group, float force);

void Mover::align(vector<Mover>* group, float radius, Time elapsed)
{
	float sum = 0,
		count = 0;
	for (Mover& m : *group)
	{
		if (ut::dist(getPos(), m.getPos()) < radius)
		{
			while (m.getAngle() < 0)
				m.setAngle(m.getAngle() + 360);
			sum += m.getAngle();
			count++;
		}
	}

	sum /= count;

	look((sum + getAngle() * 20) / 21, elapsed);
}

void Mover::speedMod(float amount)
{
	speedModifier = amount;
}