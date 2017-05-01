//============================================================================
// Name        : pointer2.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void passByValue(int x);
void passByReference(int *x);

int main() {

	int Tyson = 5;
	cout << "Tyson: \t\t" << Tyson << endl;
	cout << "&Tyson: \t" << &Tyson << endl;

	int *TysonPointer = &Tyson;	// *TysonPointer should be = to the memory location of Tyson not 5

	cout << "TysonPointer: \t" << TysonPointer << endl;		// memory address of Tyson
	cout << "*TysonPointer: \t" << *TysonPointer << endl;	// the value of Tyson
	cout << "&TysonPointer: \t" << &TysonPointer << endl;	// memory address of TysonPointer not Tyson

	cout << "Tyson==*TysonPointer\t" << "read the variable Tyson == pointervalue of *TysonPointer" << endl;
	cout << "&Tyson==TysonPointer\t" << "read the address of Tyson == variable TysonPointer" << endl;
	int betty = 13;
	int sandy = 13;

	passByValue(betty);		// really prints out the original variable
	passByReference(&sandy);	// prints out the changed original variable?

	cout << "betty is now " << betty << endl;
	cout << "sandy is now " << sandy << endl;


	return 0;
}

void passByValue(int x){		// copy of variable
	x = 99;
}

void passByReference(int *x){ 	// direct access to the variable
								// (int *x) says im going to point to something and change it
								// we say ok change wats at the address of sandy.
	*x = 66;
}
