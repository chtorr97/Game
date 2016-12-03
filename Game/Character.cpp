#include "Character.h"



Character::Character()
{
	Mover();
}


Character::~Character()
{
}

void Character::update(Time& elapsed)
{
	Mover::update(elapsed);
	coolDown.add(elapsed.asMilliseconds());
}