//============================================================================
// Name        : Composition.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "People.h"
#include "Birtday.h"
using namespace std;

int main() {
	Birthday birthObject(12,28,1986);

	People buckyRoberts("bucky", birthObject);

	buckyRoberts.printInfo();

	return 0;
}
