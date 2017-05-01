/*
 * Soldier.cpp
 * Purpose:  DEFINITION OF THE SOLDIER CLASS
 *  Created on: May 6, 2011
 *      Author: grrwood
 */

#include "Soldier.h"

Soldier::Soldier()
{
	strength = 10;
	agility = 10;
	health = 10;

	void move();
	void attackMonster();
	void getTreasure();
}

Soldier::~Soldier()
{
}
