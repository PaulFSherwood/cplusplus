//============================================================================
// Name        : Friend.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class testClass{
public:
	testClass(){testClassVar=0;}
private:
	int testClassVar;

	friend void testClassFriend(testClass &testClassObject);	// gives outside access to private
};																// variable testClassVar

void testClassFriend(testClass &testClassObject){
	testClassObject.testClassVar=99;
	cout << testClassObject.testClassVar << endl;
}

int main() {
	testClass ObjectName;
	testClassFriend(ObjectName);


	return 0;
}
