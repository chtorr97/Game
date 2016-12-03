#ifndef COUNTER_H
#define COUNTER_H

//Perc = %

class Counter
{
public:
	Counter();
	Counter(float _tot);

	void init(float _tot);
	void add(float amount);
	void addPerc(float amount);
	void set(float amount);
	float get() const;
	float getPerc();
	void setPerc(float amount);
	void setTot(float _tot);
	float getTot();
	void loop();
	void setFull();
	void setEmpty();
	bool isFull();
	bool isEmpty();

	inline Counter& operator++() { part++; return *this; }
	inline Counter& operator--() { part--; return *this; }

private:
	float part;
	float tot;
};

#endif