#include <iostream>
using namespace std;

// Section 3
void myFunction();
void myFunction2();
int getInteger();

int main()
{
	// Section 1
	// cout << "Here is some text \n";
	// cout << "Here is a number: ";
	// cout << 10 << endl;

	// cout << "10 + 7 = " << 10+7 << endl;
	// 
	// int x, y = 0;
	// x = 7;
	// y = 10;

	// cout << x << " + " << y << " = " << x+y << endl;

	// Section 2
	// float a = 5.1234567890;  // 5.123456
	// double b = 6.1234567890; // 6.123456

	// cout << "a:" << a << "\nb:" << b << endl;

	// int x = 3;    //   3
	// char y = 'u'; // 117
	// cout << x+y <<endl;

	// if (x == 3)
	// {
	// 	cout << "X is three" << endl;
	// }
	// 
	// int  number = 76;
	// int  playerNumber = 0;
	// bool isRunning = true;
	// int  maxGuesses = 10;

	// while (isRunning)
	// //while(isRunning || playerNumber != number)
	// {
	// 	cout << "Guess a number: ";
	// 	cin >> playerNumber;
	// 	if(playerNumber == number)
	// 	{
	// 		isRunning = false;
	// 		cout << "You guessed the number" << endl;
	// 	}
	// 	else
	// 	{
	// 		if (playerNumber <= number)
	// 		{
	// 			cout << "Your number is too low: " << maxGuesses << " left" << endl;
	// 		}
	// 		if (playerNumber >= number)
	// 		{
	// 			cout << "Your number is too high " << maxGuesses << " left" << endl;
	// 		}
	// 	}
	// 	maxGuesses -= 1;
	// 	if(maxGuesses <= 0)
	// 	{
	// 		isRunning = false;
	// 	}
	// }
	
	// Section 3
	myFunction();
	getInteger();
	cout << getInteger() << endl;
	return 0;
}

// Section 3
void myFunction()
{
	cout << "My function" << endl;
	myFunction2();
}
void myFunction2()
{
	cout << "My function2" << endl;
	int x = 1;
	cout << "Scope1: " << x << endl;
	{
		int x = 2;
		cout << "Scope2: " << x << endl;
	}
	cout << "Scope1: " << x << endl;
}
int getInteger()
{
	return 5;
}
