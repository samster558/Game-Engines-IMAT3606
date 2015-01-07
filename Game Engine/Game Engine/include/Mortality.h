#ifndef MORTALITY_H
#define MORTALITY_H

class Mortality
{
protected:
	int health;

public:
	Mortality();
	~Mortality();

	int getHealth();
	void setHealth(int a);


};

#endif // MORTALITY_H