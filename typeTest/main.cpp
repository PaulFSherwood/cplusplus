#include <iostream>
#include <typeinfo>

int main() {
	char one = 1;
	char two = 2;
	auto x = one + two;

	std::cout << "Type of one: " << typeid(one).name() << std::endl;
	std::cout << "Type of two: " << typeid(two).name() << std::endl;

	std::cout << "Type of x: " << typeid(x).name() << std::endl;
	std::cout << "Type of x: " << typeid(decltype(x)).name() << std::endl;

	return 0;
}
