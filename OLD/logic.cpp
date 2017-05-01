#include <iostream>

void main() {
	bool P = true;
	std::cout << "P = " << P << std::endl;
	std::cout << "Not P = " << !P << std::endl;
	P = !P;
	std::cout << "P = " << P << std::endl;
	std::cout << "Not P = " << !P << std::endl;
	return 0;
}
