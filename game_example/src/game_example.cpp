//============================================================================
// Name        : game_example.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Soldier.h"

using namespace std;

int main() {

	cout << "success!! " << endl;
	Soldier a;
	cout << a.agility << endl;
	a.agility=20;
	cout << a.agility << endl;
	return 0;
}
