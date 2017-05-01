/*
 * Soldier.hpp
 * Purpose:  DECLIRATION OF THE SOLDIER CLASS
 *  Created on: May 6, 2011
 *      Author: grrwood
 */

#ifndef SOLDIER_H_
#define SOLDIER_H_

class Soldier
{
public:
	int health;
	int strength;
	int agility;

	Soldier();
	void move();
	void attackMonster();
	void getTreasure();

	~Soldier();
};

#endif /* SOLDIER_H_ */
