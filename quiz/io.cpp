#include <iostream>
using namespace std;

int ReadNumber(int i)
{
	int x;
	if (i == 1)
	{
		cout << "Please enter first number" << endl; 
		cin >> x;
	}
	else
	{
		cout << "Please enter second number" << endl;
		cin >> x;
	}
	return x;
}
void WriteAnswer(int x)
{
	cout << "The aswer is " << x << endl;
}

