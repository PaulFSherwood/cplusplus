// i/o example
//
#include <iostream>

using namespace std;

int main() // defines the beginning of the definition of the main function
{
	int i;											// variable int=number will be assigned to I
	cout << "Please enter an integer value: ";		// cout = print to screen
	cin >> i;										// get user input stuff it in I variable has to be a number
	cout << "The value you entered is " << i;		// print to screen and print the variable I 
	cout << " and its double is " << i*2 << ".\n";	// print to screen and take i times 2 and print that
	return 0;										// return nothing and exit main
}
