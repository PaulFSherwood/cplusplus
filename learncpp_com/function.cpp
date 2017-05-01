#include <iostream>
using namespace std;

int getNumber()
{	
	int number;
	cout << "pls enter a number" << endl;
	cin >> number;
	return number;
}
int doubleNumber(int x)
{
	return x * 2;
}
bool isEven(int x)
{
	if(x % 2 == 0)
	{
		cout << "your number " << x << " is even" << endl;
	}
	else
	{
		cout << "your number " << x << " is odd" << endl;
	}
}
int main()
{
	int cNumber; // currnet number palces holder
	cNumber = getNumber();	// get users number
	cout << doubleNumber(cNumber) << endl;	// 

	int x, y, z, a;
	x = 6;
	y = 5 * 4;
	z = y % 3;
	a = y / 3;
	cout << a << endl;
	cout << x << "\t" << y << "\t" << a << "." << z << endl;

	cout << "ok lets check if cNumber is even" << endl;
	cout << isEven(cNumber);
}
