#include <iostream>
using namespace std;

int main()
{
	int integerOne = 10;
	int *pointerOne = &integerOne;

	cout << "int integerOne = 10;" << endl;
	cout << "int *pointerOne = &integerOne;" << endl;

	cout << "integerOne " << integerOne << " integer" << endl;
	cout << "&integerOne " << &integerOne << " address of integer" << endl;

	cout << "pointerOne " << pointerOne << " pointer holding address of integer" << endl;
	cout << "*pointerOne " << *pointerOne << " pointer now can grab the integer value" << endl;
	cout << "&pointerOne " << &pointerOne << " actual address of the pointer" << endl;
}
