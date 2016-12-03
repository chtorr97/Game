#include "Animator.h"

Animator::Animator()
{
	origin = ut::ZERO_VECTORf;
	size = Vector2f(32, 32);
	tex = NULL;
	disposition = ut::UNIT_VECTORi;
	counter = 0;
	inversion = false;
}

Animator::Animator(int _changeRate, Vector2f _origin, Vector2f _size, Texture* _tex, Vector2i _disposition)
{
	origin = _origin;
	size = _size;
	tex = _tex;
	disposition = _disposition;
	counter = 0;
	changer.setTot(_changeRate);
	inversion = false;
}

Animator::Animator(const Animator& other)
{
	origin = other.origin;
	counter = other.counter;
	changer = other.changer;
	disposition = other.disposition;
	size = other.size;
	tex = other.tex;
	inversion = other.inversion;
}

Animator::~Animator()
{
	tex = NULL;
	delete tex;
}

void Animator::next()
{
	inversion ? counter-- : counter++;
	if (counter > disposition.x * disposition.y - 1)
		counter = 0;
}

const IntRect Animator::get(Time elapsed)
{
	if (disposition == ut::UNIT_VECTORi)
		return IntRect(origin.x, origin.y, size.x, size.y);

	changer.add(elapsed.asMilliseconds());
	if (changer.isFull())
	{
		changer.loop();
		next();
	}
	return IntRect(origin.x + (counter % disposition.x) * size.x, origin.y + (counter / disposition.x) * size.y, size.x, size.y);
}

const IntRect Animator::get(int frame)
{
	return IntRect(origin.x + (frame % disposition.x) * size.x, origin.y + (frame / disposition.x) * size.y, size.x, size.y);
}

void Animator::randomAnimation()
{
	counter = rand() % (disposition.x * disposition.y);
}

void Animator::invert()
{
	inversion = !inversion;
}

Animator& Animator::operator=(Animator arg)
{
	origin = arg.origin;
	size = arg.size;
	counter = 0;
	changer = arg.changer;
	disposition = arg.disposition;
	tex = arg.tex;
	inversion = false;
	return *this;
}