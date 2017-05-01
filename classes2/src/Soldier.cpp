/*
 * Soldier.cpp
 *
 *  Created on: May 2, 2011
 *      Author: grrwood
 */
#include <iostream>
#include "Soldier.h"
using namespace std;

Soldier::Soldier(int startHealth, int startSrength)
:health(startHealth),strength(startSrength)
{}

void Soldier::attack()
{
	cout << "\nAttacking with " << strength << " strength\n";
}

void Soldier::heal(int amountHealth)
{
	health += amountHealth;
}

void Soldier::beAttacked()
{
	cout << "\naaaargh!!\n";
	health -= 1;
}

int Soldier::GetHealth()
{
	return health;
}
