/*
 * Soldier.h
 *
 *  Created on: May 2, 2011
 *      Author: grrwood
 */

#ifndef SOLDIER_H_
#define SOLDIER_H_

class Soldier
{
public:

	Soldier(int startHealth, int startSrength);

	void attack();

	void heal(int amountHealth);

	void beAttacked();

	int GetHealth();

private:
	int health;
	int strength;
};

#endif /* SOLDIER_H_ */
