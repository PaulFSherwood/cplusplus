#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	long inputNumber;

	while (inputNumber != 0)
	{
		cout << "please enter a number\n";
		cin >> inputNumber;
		cout << setprecision(17);
		double dValue;
		dValue = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;
		cout << dValue << endl;
		dValue = .1 * inputNumber;
		cout << dValue << endl;
	}
}
