#include <iostream>

void foo() {
}

int main() {
	int x = 42;
	float y = 72;
	char a = 'a';
	signed char b = 'b';
	unsigned char c = 'c';

	std::cout << "x: " << &x << " size: " << sizeof(x) << std::endl;
	std::cout << "y: " << &y << " size: " << sizeof(y) << std::endl;
	std::cout << "a: " << &a << " size: " << sizeof(a) << std::endl;
	std::cout << "a: " << (void*)&a << " size: " << sizeof(a) << std::endl;
	std::cout << "b: " << &b << " size: " << sizeof(b) << std::endl;
	std::cout << "b: " << (void*)&b << " size: " << sizeof(b) << std::endl;
	std::cout << "c: " << &c << " size: " << sizeof(c) << std::endl;
	std::cout << "c: " << (void*)&c << " size: " << sizeof(c) << std::endl;

	return 0;
}
