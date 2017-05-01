/*
 * People.h
 *
 *  Created on: May 6, 2011
 *      Author: grrwood
 */
#include <string>
#include "Birtday.h"
#include <iostream>
using namespace std;

#ifndef PEOPLE_H_
#define PEOPLE_H_

class People
{
public:
	People(string x, Birthday bo);
	void printInfo();
private:
	string name;
	Birthday dateOfBirth;
};


#endif /* PEOPLE_H_ */
