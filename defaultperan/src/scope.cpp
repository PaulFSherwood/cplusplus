#include <iostream>
using namespace std;

int tuna = 20;	// global variable

int main()
{
	int tuna = 40;	// local variable
	cout << tuna << endl;
	cout << ::tuna << endl;
}

