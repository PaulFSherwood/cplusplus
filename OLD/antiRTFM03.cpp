#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
	int num1 = 0;
	while (num1 == 0)
	{
		cout << "Hey" << endl;  // cout is in the package std thats in iostream
		cin >> num1;	// cin is in the package std thats in iostream
	}
	return 0;
}
