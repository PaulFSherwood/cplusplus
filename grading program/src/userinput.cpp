//============================================================================
// Name        : userinput.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int x = 1;
	int grade;

	while (x == 1){
		cout << "Enter your grade pls: ";
		cin >> grade;
		if (grade == 100)
			cout << "You got a perfect score" << endl;
		else if ( grade <= 99 && grade >= 90)
			cout << "you got an A but you need to work harder to get  aperfect score" << endl;
		else if (grade <= 89 && grade >= 80)
			cout << "You got a B but you need to more hardere to be more better" << endl;
		else if (grade <= 79 && grade >= 70)
			cout << "You got a C but you need to more hardere to be more better" << endl;
		else if (grade <= 69 && grade >= 60)
			cout << "You got a D are you even trying?" << endl;
		else if (grade >= 59)
			cout << "You got a F good job on that whole studing thing" << endl;
		else
			cout << "You are fail" << endl;

		cout << "keep going ? 1 = yes, 0 = no" << endl;
		cin >> x;

	}
	return 0;
}
