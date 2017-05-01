//============================================================================
// Name        : templet_specialization.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


// Basic temple can take any type of data
template <class T>
class Spunky{
public:
	Spunky(T x){
		cout << x << " is not a character!" << endl;
	}
};

// Specialized template (for chars)
template<>
class Spunky<char>{
public:
	Spunky(char x){
		cout << x << " is a character!" << endl;
	}
};

int main() {

	Spunky<int> obj1(7);
	Spunky<double> obj2(3.154);
	Spunky<char> obj3('q');

	return 0;
}
