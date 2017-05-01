// pointer test
#include <iostream>
using namespace std;

int main()
{
	int firstvalue = 100;
	int secondvalue = 200;
	int *firstpointer = &firstvalue;
	int *secondpointer = &secondvalue;

	cout << "firstvalue: " << firstvalue << endl;
	cout << "&firstvalue: " << &firstvalue << endl;
	cout << "firstpointer: " << firstpointer << endl;
	cout << "*firstpointer: " << *firstpointer << endl;
	cout << "&firstpointer: " << &firstpointer << "\tThis address is the address of the pointer not the firstvalue" << endl;
	
	cout << "secondvalue: " << secondvalue << endl;
	cout << "&secondvalue: " << &secondvalue << endl;
	cout << "secondpointer: " << secondpointer << endl;
	cout << "*secondpointer: " << *secondpointer << endl;
	cout << "&secondpointer: " << &secondpointer << "\tThis addres is the addres of the pointer not the secondvalue" << endl;
	return 0;
}
