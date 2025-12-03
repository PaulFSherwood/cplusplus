#include <print>

void f(auto x) {

	return x % 2;
}

int main() {

	std::print("Result of 5 % 2: {}\n",f(5));
	std::print("Result of 5.8 % 2: {}\n",f(5.8));

	return 0;
}
