#ifndef ANIMATION_H
#define ANIMATION_H

#include "Displayable.h"

class Animation :
	public Displayable
{
public:
	Animation();
	~Animation();

	void init(Vector2f _position, Animator _animator);
	void update(Time& elapsed);
	void update(int frame);

	inline void randomAnimation() { animator.randomAnimation(); }

private:
	Animator animator;
};

#endif