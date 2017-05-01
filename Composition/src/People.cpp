/*
 * People.cpp
 *
 *  Created on: May 6, 2011
 *      Author: grrwood
 */
#include "People.h"
#include "Birtday.h"
#include <iostream>
using namespace std;


People::People(string x, Birthday bo)
: name(x), dateOfBirth(bo)
{}
void People::printInfo()
{
	cout << name << " was born on ";
	dateOfBirth.printDate();
}
