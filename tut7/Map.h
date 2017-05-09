#ifndef SOLDIER_H_
#define SOLDIER_H_

class Map
{
public:

	Map(int startHealth, int startSrength);

	void attack();

	void heal(int amountHealth);

	void beAttacked();

	int GetHealth();
	
	char GetMap();

private:
	int health;
	int strength;
	char myArray[2][2];
};

#endif /* SOLDIER_H_ */
