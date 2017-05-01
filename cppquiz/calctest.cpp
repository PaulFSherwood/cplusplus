#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	int num1 = 0;
	int num2 = 0;
	double answer = 0;
	char mathSymbol;

	cout << "pls enter your fist number\n";
	cin >> num1;
	cout << "pls enter your second number\n";
	cin >> num2;
	
	cout << "pls choose one +, -, *, /\n";
	cin >> mathSymbol;
	switch (mathSymbol)
	{
		case '+':
			answer = num1 + num2;
			cout << num1 << " + " << num2 << " = " << answer << endl;
			break;
		case '-':
			answer = num1 - num2;
			cout << num1 << " - " << num2 << " = " << answer << endl;
			break;
		case '*':
			answer = num1 * num2;
			cout << num1 << " * " << num2 << " = " << answer << endl;
			break;
		case '/':
			if (num2 == 0)
			{
				cout << "can not divde by zero\n";
			}
			else
			{
				answer = static_cast<double>(num1 / num2);
				cout << answer << endl;
			}
			break;
	}
}
