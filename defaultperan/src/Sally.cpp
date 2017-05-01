#include "Sally.h"
#include <iostream>
using namespace std;

Sally::Sally(int a, int b)
: regVar(a), constVar(b)
{}

void Sally::printCrap()
{
	cout << "regVar: " << regVar << "\tconstVar: " << constVar << endl;
}
/*
void Sally::printCrap2() const
{
	cout << "const function\n";
}*/
