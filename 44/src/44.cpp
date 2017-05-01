//============================================================================
// Name        : 44.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Sally.h"
using namespace std;

int main() {

	Sally salObj;
	salObj.printstuff();

	const Sally constObj;
	constObj.printconst();

	return 0;
}
