//============================================================================
// Name        : pointer.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
using namespace std;

int increment(int x);
void incrementP(int * ptr);

int main() {
	/*
	 * &x			// ADDRESS OF <WHATEVER>
	 * char * ptr	// <TYPE> OF POINTER CALLED <WHATEVER>
	 * *ptr			// DEREFERENCE THE POINTER CALLED <WHATEVER>
	 */
	int var = 0;
	cout << "var: " << var << endl;

	int *pointer1 = &var;
	cout << "the stuff pointer1 is pointing to: " << *pointer1 << endl;

	increment(var);
	cout << "has it incremented?: " << *pointer1 << endl;

	incrementP(pointer1);
	cout << "has it incremented?: " << *pointer1 << endl;

	increment(var);
	cout << "increment(var): " << var << endl;
	cout << "*pointer1:::::: " << *pointer1 << endl;

	return 0;
}

int increment(int x)
{
	x++;//1
	cout << "x's value inside increment function: " << x << endl;
	return x;
}

void incrementP(int * x)
{
	(*x)++;
}
