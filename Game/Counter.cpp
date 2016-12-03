#include "Counter.h"

Counter::Counter()
{
	part = 0;
	tot = 100;
}

Counter::Counter(float _tot)
{
	part = 0;
	tot = _tot;
}

void Counter::init(float _tot)
{
	tot = _tot;
	part = tot;
}

void Counter::add(float amount)
{
	part += amount;
}

void Counter::addPerc(float amount)
{
	part += tot * amount / 100;
}

void Counter::set(float amount)
{
	part = amount;
}

float Counter::get() const
{
	return part;
}

float Counter::getPerc()
{
	return part * 100 / tot;
}

void Counter::setPerc(float amount)
{
	part = tot * part / 100;
}

void Counter::setTot(float _tot)
{
	tot = _tot;
}

float Counter::getTot()
{
	return tot;
}

void Counter::loop()
{
	while (isFull())
		part -= tot;
}

void Counter::setFull()
{
	part = tot;
}

void Counter::setEmpty()
{
	part = 0;
}

bool Counter::isFull()
{
	return part >= tot;
}

bool Counter::isEmpty()
{
	return part <= 0;
}