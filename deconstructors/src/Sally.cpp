/*
 * Sally.cpp
 *
 *  Created on: May 6, 2011
 *      Author: grrwood
 */
#include <iostream>
#include "Sally.h"
using namespace std;

Sally::Sally()
{
	cout << "i am the constructor" << endl;
}
void Sally::dance()
{
	cout << "sally is dancing " << endl;
}
void Sally::talk()
{
	cout << "sally is talking " << endl;
}
void Sally::talk2() const
{
	cout << "constant function talking " << endl;
}
Sally::~Sally() {
	cout << "i am the deconstructor" << endl;
}

Pally::Pally(int a, int b)
: regVar(a), constVar(b)
{}
void Pally::print()
{
	cout << "regular var is: " << regVar << endl;
	cout << "const var is: " << constVar << endl;
}
