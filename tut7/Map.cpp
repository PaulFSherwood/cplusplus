#include <iostream>
#include "Map.h"
using namespace std;

Map::Map(int startHealth, int startSrength)
:health(startHealth),strength(startSrength)
{}

void Map::attack()
{
	cout << "\nAttacking with " << strength << " strength\n";
}

void Map::heal(int amountHealth)
{
	health += amountHealth;
}

void Map::beAttacked()
{
	cout << "\naaaargh!!\n";
	health -= 1;
}

int Map::GetHealth()
{
	return health = 5;
}

char Map::GetMap()
{
     return myArray[2][2];/* = {
            {'1', '2'}, 
            {'3', '4'}
            };*/
}
