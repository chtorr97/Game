#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
public:
	Weapon();
	~Weapon();

private:
	int damage;
	int coolDown;
	float speed;
};

#endif