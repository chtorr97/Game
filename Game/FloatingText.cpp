#include "FloatingText.h"

FloatingText::FloatingText()
{
	setString("Default");
	setDuration(1000);
	speed = 1;
	setOrigin({ text.getLocalBounds().width / 2, text.getLocalBounds().height / 2 });
}

FloatingText::FloatingText(string s, float duration, float velocity)
{
	setString(s);
	setDuration(duration);
	speed = velocity;
	setOrigin({ text.getLocalBounds().width / 2, text.getLocalBounds().height / 2 });
}

void FloatingText::init(string s, float duration, float velocity)
{
	setString(s);
	setDuration(duration);
	speed = velocity;
	setOrigin({ text.getLocalBounds().width / 2, text.getLocalBounds().height / 2 });
}

void FloatingText::init(string s, Vector2f position)
{
	setString(s);
	setOrigin({ text.getLocalBounds().width / 2, text.getLocalBounds().height / 2 });
	setPosition(position);
}

void FloatingText::update(Time& elapsed)
{
	move(0, -speed * elapsed.asMilliseconds());
	counter.add(elapsed.asMilliseconds());
	text.setColor({ text.getColor().r, text.getColor().g, text.getColor().b, (Uint8)(255 * (100 - (counter.getPerc())) / 100) });
}

void FloatingText::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(text, states);
	//target.draw(text, getTransform());
}