#include <iostream>	// this is loaded from where the compiler knows
#include<stdio.h>	// if this had #include "stdio.h" then it would be local
using namespace std;

int main()
{
	// declare the variables:
	int nNumber;
	int *pPointer;
	
	// now, give a value to them:
	
	nNumber = 15;
	pPointer = &nNumber;
	printf("nNumber is equal to : %d\n", nNumber);
	
	// now, alter nNumber throught pPointer:
	
	printf("changing *pPointer to 25\n");
	*pPointer = 25;
	
	// prove that nNumber has changed as a result of the above by
	// printing its value again:
	
	printf("nNumber is equal to : %d\n", nNumber);
}
