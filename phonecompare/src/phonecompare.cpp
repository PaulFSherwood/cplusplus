//============================================================================
// Name        : phonecompare.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int main()
{

	string areacode[4] = {"505", "506", "507", "518"};

	string userinput;
	int inputlength;

	cin >> userinput;
	inputlength = userinput.length();

	cout << inputlength << endl;

	for ( int x = 0; x < 4; x++){
		string currentcode = areacode[x];
		//cout << currentcode << endl;
		if (userinput[0] == currentcode[0])
		{
			cout << currentcode << endl;
		}
	}
	return 0;
}
