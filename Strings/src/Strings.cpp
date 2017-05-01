//============================================================================
// Name        : Strings.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {

	string s1("hampster ");
	string s2;
	string s3;
	string s4("OMG i think i am preggy!!");
	string one("apples ");
	string two("beans ");
	string s5("ham is spam oh yes i am!");

	s2 = s1;
	s3.assign(s1);

	cout << s1 << s2 << s3 << endl;

	for (unsigned int x = 1; x < s1.length(); x++){
		cout << s1.at(x);
		cout << s1.length() << endl;
	}
	// substrings make a string from a string
	cout << s4.substr(17, 7) << endl;

	// swap string function
	cout << one << two << endl;
	one.swap(two);
	cout << one << two << endl;

	cout << s5 << endl;
	// give starting location of the first occurrence of "am"
	cout << "first am is at position: " << s5.find("am") << endl;
	// last occurrence
	cout << "last am is at position: " << s5.rfind("am") << endl;

	//s5.erase(11);
	s5.replace(14, 5, "samuel jacoson");
	cout << s5 << endl;

	s5.insert(14, " ");
	s5.insert(29, " ");
	cout << s5 << endl;

	return 0;
}
