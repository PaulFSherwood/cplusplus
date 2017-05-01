//============================================================================
// Name        : grant_game.cpp
// Author      : sherwood
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "menu.h"
#include "grant.h"

using namespace std;

int main() {
	printf("\033[2J\033[1;1H");		// clear screen
	printf("\033[22;34m"); 			// - blue screen

		menu menuObject;
		menuObject.getmenu();

		int x = 1;
		while (x != 0){
		cout << "pic a number: ";
		cin >> x;
		menuObject.arrowtest(x);

		grant grantObject;

		grantObject.setHunger(50);

		cout << grantObject.getHunger() << endl;

	}

	printf("\033[2J\033[1;1H");		// clear screen
	printf("\033[01;37m");			// white/regular text
	return 0;
}
