//============================================================================
// Name        : helloworld.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	int x;
//	short f;
//	long h;
	unsigned short int y;
	unsigned long int z;
	signed short int a;
	signed long int b;

	char h; // c++ tut 9
	h = '$';

	string str1 = "hey";

	y = 10;
	z = 1000000;
	a = -100;
	b = -1000000;

	cout << str1 << endl;
	cout << h << endl;
	cout << y << endl;
	cout << z << endl;
	cout << a << endl;
	cout << b << endl;

	cin.get();
	return 0;
}
