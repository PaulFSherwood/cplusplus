/*
 * menu.cpp
 *
 *  Created on: May 18, 2011
 *      Author: sherwood
 */

#include <iostream>
#include <stdio.h>
#include "menu.h"
using namespace std;

menu::menu()
{}
// Setters
void menu::getmenu()
{
	cout << "Welcome to the Grant wildlife preserve..." << endl;
	sleep(1);
	cout << "Some things you need to know." << endl;
	sleep(2);
	cout << "We are here to keep our Grant Happy :) " << endl;
	sleep(2);
	cout << "You need to do the following to keep Grant happy " << endl;
	sleep(2);
	cout << "1. Feed your Grant." << endl;
	sleep(1);
	cout << "2. Teach your Grant. " << endl;
	sleep(1);
	cout << "3. Give your Grant money. " << endl;
	sleep(1);
	cout << "4. Let your grant have fun. " << endl;
	sleep(2);
	cout << "5. Monitor your Grant's Happieness. " << endl;

}
void menu::arrowtest(int x)
{
	printf("\033[2J\033[1;1H");
	cout << "->\tone " << endl;
	cout << "\ttwo" << endl;

	if (x == 1){
		printf("\033[2J\033[1;1H");
		cout << "->\tone " << endl;
		cout << "\ttwo" << endl;
	}
	else if (x == 2){
		printf("\033[2J\033[1;1H");
		cout << "\tone " << endl;
		cout << "->\ttwo " << endl;
	}
	else {
		printf("\033[2J\033[1;1H");
		cout << "~~~~~Error~~~~~" << endl;
		sleep(2);
		printf("\033[2J\033[1;1H");
		cout << "->\tone " << endl;
		cout << "\ttwo" << endl;
	}
}
