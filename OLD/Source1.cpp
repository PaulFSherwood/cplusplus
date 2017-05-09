#include <iostream>

void main() {
	double x = -2;
	double y = 3;
	int iCount = 0;
	if (y >= x) {
		std::cout << "y >= x" << std::endl;
	} else {
		std::cout << "y <= x" << std::endl;
	}
	do {
		std::cout << iCount << std::endl;
		++iCount;
	}while (iCount < 5);
}