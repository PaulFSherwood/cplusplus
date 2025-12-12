#include <iostream>
#include "Array.hpp"

void printAnArray(Array *a) {
	// called with: printAnArray(&myArray);
	// a->PrintingData();
}
void printAnArray(Array &a) {
	// called with printAnArray(myArray);
}/*
void printAnArray(Array a) {
	// called with printAnArray(myArray);
	// a.PrintingData();
}*/

int main() {
	// Initialize all of our data up frount
	Array myArray;

	myArray.SetData(0, 1234567);
	// myArray.SetData(1, 777);
	// myArray.SetData(2, 999);

	/*Array myArray2;
	myArray2 = myArray; */  	// Two Constructors & Copy assignment operator
	Array myArray2 = myArray;	// One Constructors & Copy Constructor

	myArray.PrintingData();
	myArray2.PrintingData();

	printAnArray(&myArray);		// Will call Copy Constructor

	for (int i = 0; i < 10; i++) {
		printAnArray(myArray);
		// std::cout << std::endl;
	}
	return 0;
}	
