// cin with strings
//
#include <iostream>					// i think this has to do with getting user input "cin"
#include <string>					// so we can use stings
	
using namespace std;				// have been told this several times and still dont remember

int main()
{
	string mystr;					// made a string variable and assigned it to mystr;
	cout << "What's your name? ";	// print to screen
	getline (cin, mystr);
	cout << "hello " << mystr << ".\n";
	cout << "what is your favorite team? ";
	getline (cin, mystr);
	cout << "I like " << mystr << " too!\n";
	return 0;
}
