#ifndef FLOATING_TEXT_H
#define FLOATING_TEXT_H

#include <SFML\Graphics.hpp>
#include "Counter.h"
#include "utility.h"

using namespace std;
using namespace sf;

class FloatingText
	: public Drawable, public Transformable
{
public:
	FloatingText();
	FloatingText(string s, float duration, float velocity);

	void init(string s, float duration, float velocity);
	void init(string s, Vector2f position);

	void update(Time& elapsed);

	inline void setString(string s) { text.setString(s); }
	inline void setSize(int s) { text.setCharacterSize(s); }
	inline void setFont(Font& f) { text.setFont(f); }
	inline void setColor(Color c) { text.setColor(c); }
	inline void setDuration(float millis) { counter.setTot(millis); }
	inline void setSpeed(float velocity) { speed = velocity; }
	inline bool isDestroyed() { return counter.isFull(); }

private:
	Text text;
	Counter counter;
	float speed;

	void draw(RenderTarget& target, RenderStates states) const;
};

#endif