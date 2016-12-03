#ifndef CHARACTER_H
#define CHARACTER_H

#include "Mover.h"
class Character :
	public Mover
{
public:
	Character();
	~Character();

	void update(Time& elapsed);

	inline void setFull(int health = 15) { hp.setTot(health); hp.setFull(); }
	inline void damage(int dmg) { hp.add(-dmg); }
	inline void heal(int amount) { hp.add(amount); }
	inline int getHp() { return hp.get(); }
	inline int getTotHp() { return hp.getTot(); }
	inline bool isDead() { return hp.isEmpty(); }
	inline void setCoolDown(float amount) { coolDown.setTot(amount); };
	inline float getCoolDown() { return coolDown.getTot(); };
	inline bool useDmg() { if (coolDown.isFull()) { coolDown.setEmpty(); return true; } return false; }
	inline void setDmg(int newDmg) { dmg = newDmg; }
	inline int getDmg() { return dmg; }

private:
	int dmg = 5;
	Counter hp;
	Counter coolDown;
};

#endif