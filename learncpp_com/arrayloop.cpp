#include <iostream>
using namespace std;

int getUserNumber()
{
	int UserInput = 0;
	cout << "pls enter a number\n";
	while (!(cin >> UserInput && UserInput <= 8))
	{
		cout << "Error please try again: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
		return UserInput;
}
int printArrayIndex(int anArray[], int UserInput)
{
	int arrayIndex = anArray[UserInput];
	return arrayIndex;
}

int main()
{
	int anArray[9] = { 4, 6, 7, 3, 8, 2, 1, 9, 5};
	
	for (int x = 0; x <= 8; x++)
	{
		if (x == 8)
		{
			cout << anArray[x] << endl;
		}
		else
		{
		cout << anArray[x] << ", ";
		}
	}
	int UserInput;
	UserInput = getUserNumber();
	cout << printArrayIndex(anArray, UserInput) << endl;
}
