// **********************************
// ** Demonstrates typedef keyword **
// **********************************

#include <iostream>

typedef unsigned short int USHORT;		// typedef defined

int main()

{
	USHORT Width = 5;
	USHORT Length;
	Length = 10;
	USHORT Area = Width * Length;
	std::cout << "Width: " << Width << "\n";
	std::cout << "Length: " << Length << std::endl;
	std::cout << "Area: " << Area << std::endl;
	return 0;
}
