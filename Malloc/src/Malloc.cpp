//============================================================================
// Name        : Malloc.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Bank
{
public:
	int BuyShares();
	int GetMoney();

	const int * GetInformation()
		{
		return & delicateInformation;
		}

private:
	int amountMoney;
	int stockValue;
	int delicateInformation;
};

class Company
{

};

int main() {

	int x = 0;
	const int y = 1;	// you have to declare right away.

	int * ptr1 = 0;

	const int * ptr2 = 0;

	ptr2 = &y;

	cout << ptr2 << "\t" << &y << endl;
	cout << *ptr2 << "\t\t" << &y << endl;

	//int * const ptr5 = &x;

	//const int * const ptr5 = &x;
	cout << y << "\t\t"  << x << endl;
	cout << &ptr1 << "\t" << &ptr2 << endl;

	return 0;
}

/*
#include <iostream>

using namespace std;
int * Action(int * ptr);

int main()
{
	int y = 0;						// integer y

	int * pointer = Action( &y );	// integer pointer (points to what ever is returned by the action function
									// pass address of y
	return 0;
}

int * Action(int * ptr)				// address of y is now the pointer variable
{
	*ptr++;							// address of y gets increased and returned?
	return ptr;
}
*/
