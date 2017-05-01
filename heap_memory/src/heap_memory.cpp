//============================================================================
// Name        : heap_memory.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;



int main() {

	int * ptr = new int;
	*ptr = 9;

	delete ptr;
	ptr = 0;	// null

	return 0;
}
