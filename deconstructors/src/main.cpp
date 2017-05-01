//============================================================================
// Name        : deconstructors.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Sally.h"
using namespace std;

int main() {

	Sally so;
	const Sally cso;
	Pally so2(3,87);
	so2.print();
	so.talk();
	cout << "omg wtf is this on my shoe?" << endl;
	cso.talk2();
	return 0;
}
