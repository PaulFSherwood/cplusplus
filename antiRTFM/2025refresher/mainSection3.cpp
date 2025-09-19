#include <iostream>
#include <random>  // For rand() and srand()
using namespace std;

// Section 3
void myFunction();
int myFunction2(int var);
int getInteger();

int main()
{
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
	myFunction2(10);
}
int myFunction2(int var)
{
	cout << "My function2: " << var << endl;
	// int x = 1;
	cout << "Scope1: " << var << endl;
	{
		var = 2;
		cout << "Scope2: " << var << endl;
	}
	cout << "Scope1: " << var << endl;

	return var;
}
int getInteger()
{
	static mt19937 gen(random_device{}()); // Seed once
	static uniform_int_distribution<int> dist(1, 100);

	int ranNum = dist(gen);
	(ranNum % 2 == 0) ? std::cout << ranNum << " good\n" : std::cout << ranNum << " bad\n";

	return 5;
}
