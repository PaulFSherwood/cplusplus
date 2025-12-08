#include <iostream>

int main() {

	int x = 7;
	int* px = &x;

	std::cout << "x stores : " <<   x << std::endl;
	std::cout << "x address: " <<  &x << std::endl;
	std::cout << "px stores: " <<  px << std::endl;
	std::cout << "px deref : " << *px << std::endl;

	return 0;
}
