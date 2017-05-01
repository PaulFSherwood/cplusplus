//============================================================================
// Name        : arrays2.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : ***** ***** in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void printArray(string theArray[][5], int rowOfArray);

int main() {
	string bucky[3][5] = {{"zero", "one", "two", "three", "four"},
			{"2zero", "2one", "2two", "2three", "2four"},
			{"3zero", "3one", "3two", "3three", "3four"}};
	/*
	for (int x = 0; x < 5; x++){
		cout << "bucky[" << x << "] = " << bucky[x] << endl;
	}
	*/

	printArray(bucky, 3);

	return 0;
}

void printArray(string theArray[][5], int rowOfArray){
	for (int y = 0; y < rowOfArray; y++){
		for (int x = 0; x < 5; x++){
			cout << "array[" << x << "][" << y << "] = " << theArray[y][x]<< endl;
		}
		cout << endl;
	}
}
