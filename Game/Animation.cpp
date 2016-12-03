#include "Animation.h"

Animation::Animation() : Displayable()
{
}

Animation::~Animation()
{
}

void Animation::init(Vector2f _position, Animator _animator)
{
	setPos(_position);
	animator = _animator;
	setSize(animator.getSize());
	rect.setSize(getSize());
	tex = animator.getTexture();
	sprite.setTexture(*tex);
	Displayable::update();
	sprite.setTextureRect(animator.get(0));
}

void Animation::update(Time& elapsed)
{
	Displayable::update();
	sprite.setTextureRect(animator.get(elapsed));
}

void Animation::update(int frame)
{
	Displayable::update();
	sprite.setTextureRect(animator.get(frame));
}