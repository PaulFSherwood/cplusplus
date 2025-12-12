#include <iostream>
#include "Array.hpp"

int main() {
	// Initialize all of our data up frount
	Array myArray;

	myArray.SetData(0, 100000);
	myArray.SetData(1, 777);
	myArray.SetData(2, 999);

	Array myArray2;
	myArray2 = myArray;  // Copy -Assignment operator

	myArray.PrintingData();
	myArray2.PrintingData();

	return 0;
}	
