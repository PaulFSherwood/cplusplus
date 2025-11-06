#include "tools.hpp"
#include <iostream>
#include <limits>

int returnMe(int bacon) {
	int ret = bacon * 2;
	return ret;
}

void f() {
	static int counter = 0;
	int cnt = 0;
	counter++;
	cnt++;
	std::cout << &counter << " " << counter << std::endl;
	std::cout << &cnt << " " << cnt << std::endl;
}

int main() {
 	std::cout << "Hello World!" << std::endl;
	MakeItRain();
	MakeItSunny();
	std::cout << returnMe(2) << std::endl;
	f();
	f();
	int num[100] = {1,2,3,4,5,6,7,8,9,10};	
	int num1[100] = {1,2,3,4,5,6,7,8,9,10};	
	int num2[100] = {1,2,3,4,5,6,7,8,9,10};	
	int num3[100] = {1,2,3,4,5,6,7,8,9,10};	
	f();
	f();

	return 0;
}
