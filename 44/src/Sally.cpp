/*
 * Sally.cpp
 *
 *  Created on: May 17, 2011
 *      Author: grrwood
 */

#include "Sally.h"
#include <iostream>
using namespace std;

Sally::Sally(){}

void Sally::printstuff(){
	cout << "regular function" << endl;
}

void Sally::printconst() const{
	cout << "const function" << endl;
}
