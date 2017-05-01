/*
 * Birtday.cpp
 *
 *  Created on: May 6, 2011
 *      Author: grrwood
 */
#include "Birtday.h"
#include <iostream>
using namespace std;

Birthday::Birthday(int m, int d, int y)
{
	month = m;
	day = d;
	year = y;
}

void Birthday:: printDate(){
	cout << month << "/" << day << "/" << year << endl;
}
