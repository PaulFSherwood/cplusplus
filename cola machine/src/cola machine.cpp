//============================================================================
// Name        : cola.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
using namespace std;

int main() {

	int drink;
	cout << "Please select a soda" << endl;
	cout << "1)Dr. Pepper | 2)Mt. Dew | 3)A&W Root Beer | 4)Pepsi | 5)Coke" << endl;
	cin >> drink;

	switch(drink){
	case 1:
		cout << "Dispensing Dr. Pepper ENJOY :)";
		break;
	case 2:
		cout << "Dispensing Mt. Dew ENJOY :)";
		break;
	case 3:
		cout << "Dispensing A&W Root Beer ENJOY :)";
		break;
	case 4:
		cout << "Dispensing Pepsi ENJOY :)";
		break;
	case 5:
		cout << "Dispensing Coke ENJOY :)";
		break;
	default:
		cout << "There is a problem pls standby";
		break;
	}
	return 0;
}
