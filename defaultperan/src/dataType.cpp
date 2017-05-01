#include <iostream>
using namespace std;

int main()
{
	char a;
	short int b;
	int c;
	long int d;
	bool e;
	float f;
	double g;
	long double h;
	wchar_t i;
	
	cout << "char\t\t" << sizeof(a) << endl;
	cout << "short int\t" << sizeof(b) << endl;
	cout << "int\t\t" << sizeof(c) << endl;
	cout << "long int\t" << sizeof(d) << endl;
	cout << "bool\t\t" << sizeof(e) << endl;
	cout << "float\t\t" << sizeof(f) << endl;
	cout << "double\t\t" << sizeof(g) << endl;
	cout << "long double\t" << sizeof(h) << endl;
	cout << "wchar_t\t\t" << sizeof(i) << endl;
}
