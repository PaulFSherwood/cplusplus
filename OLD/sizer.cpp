//sizer.cpp
// Determines the Size of variable types on your computer

#include <iostream>

int main()
{
	std::cout << "The size of an int is:\t\t";
	std::cout << sizeof(int) << " bytes.\n";
	std::cout << "The size of a short int is:\t";
	std::cout << sizeof(short) << " bytes.\n";
	std::cout << "The size of an long is:\t";
	std::cout << sizeof(long) << " bytes.\n";
	std::cout << "The size of an char is:\t";
	std::cout << sizeof(char) << " bytes.\n";
	std::cout << "The size of an bool is:\t";
	std::cout << sizeof(bool) << " bytes.\n";
	std::cout << "The size of an float is:\t";
	std::cout << sizeof(float) << " bytes.\n";
	std::cout << "The size of an double is:\t";
	std::cout << sizeof(double) << " bytes.\n";

	return 0;
}
