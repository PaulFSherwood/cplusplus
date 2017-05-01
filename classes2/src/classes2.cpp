//============================================================================
// Name        : classes2.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Soldier.h"

using namespace std;

int main() {
	int x = 0;

	Soldier john(90,100);

	john.attack();
	john.beAttacked();
	john.heal(3);
	x = john.GetHealth();
	cout << john.GetHealth();

	return 0;
}

