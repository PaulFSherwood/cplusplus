#include <iostream>
#include <stdio.h>
#include "io.h"
using namespace std;

int main()
{
	// set up variables for user input
	int inputOne;
	int inputTwo;
	//char mathSymbol;
	
	// using getInput function .. get user input
	inputOne = getInput(1);
	inputTwo = getInput(2);
	//mathSymbol = getMathSymbol();

	// print out the answer
	cout << doMath(inputOne, inputTwo) << endl;
}

