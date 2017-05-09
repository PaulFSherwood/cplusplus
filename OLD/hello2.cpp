#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	string yourName;
	
	cout << "Please type your name and press Enter: "
	cin >> yourName;

	cout << endl << "Hello, " << yourName << endl << endl;

	cout << "Press c and then Enter to continue...";

	char justWait;
	cin >> justWait;

    system("PAUSE");
    return EXIT_SUCCESS;
}
