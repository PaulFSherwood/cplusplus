#include <iostream>
#include <string>
using namespace std;

// Class Prototyping
class MathClass
{
	public:
		// Setters
		void setNum1(int Num1)
		{
			number1 = Num1;
		}
		void setNum2(int Num2)
		{
			number2 = Num2;
		}
		// Getters
		int getNum1()
		{
			return number1;
		}
		int getNum2()
		{
			return number2;
		}
		// Math portion
		void Addition(int num1, int num2)
		{
			setNum1(num1);
			setNum2(num2);
			int answer = getNum1() + getNum2();
			cout << getNum1() << " plus " << getNum2() << " is " << answer << endl;
		}
		void Subtraction(int num1, int num2)
		{
			setNum1(num1);
			setNum2(num2);
			int answer = getNum1() - getNum2();
			cout << getNum1() << " minus " << getNum2() << " is " << answer << endl;
		}
		void Division(int num1, int num2)
		{
			setNum1(num1);
			setNum2(num2);
			int answer = getNum1() / getNum2();
			cout << getNum1() << " divided by " << getNum2() << " is " << answer << endl;
		}
		void Multiplication(int num1, int num2)
		{
			setNum1(num1);
			setNum2(num2);
			int answer = getNum1() * getNum2();
			cout << getNum1() << " multiplied by " << getNum2() << " is " << answer << endl;
		}
		private:
		int number1;
		int number2;
};

// Function Prototyping
void Greatings();
char Choices(char WhatToDo);

int main()
{
	char WhatToDo;
	cout << "Please choice an operation\n";
	Choices(WhatToDo);
	return 0;
}
void Greatings()
{
	cout << "Please enter your two numbers: \n";
}
char Choices(char WhatToDo)
{
	int num1, num2;
	MathClass MathObject;
	cin >> WhatToDo;
	switch(WhatToDo) 
	{
		case '+':
			Greatings();
			cin >> num1;
			cin >> num2;
			MathObject.Addition(num1, num2);
			break;
		case '-':
			Greatings();
			cin >> num1;
			cin >> num2;
			MathObject.Subtraction(num1, num2);
			break;
		case '/':
			Greatings();
			cin >> num1;
			cin >> num2;
			MathObject.Division(num1, num2);
			break;
		case '*':
			Greatings();
			cin >> num1;
			cin >> num2;
			MathObject.Multiplication(num1, num2);
			break;
		default:
			cout << "you just wasted our time pick the right thing nextime\n";
			break;
	}
	system("PAUSE");
}



