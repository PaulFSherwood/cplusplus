#include <iostream>
#include <string>
using namespace std;

void printArray(int theArray[], int sizeOfArray);

void printArray(string theArray[], int sizeOfArray);

void printArray(int theArray[3][2]);

int main()
{
	int bucky[3] = {20, 54, 675};
	string jessica[6] = {"Mary", "Linda", "Jennifer", "Maria", "Susan", "Lisa"};
	int multArray[3][2] = {{2,3},{1,2},{14,18}};
	
	printArray(bucky, 3);
	printArray(jessica, 6);
	printArray(multArray);
}

void printArray(int theArray[], int sizeOfArray)
{
	for (int x = 0; x < sizeOfArray; x++)
	{
		cout << theArray[x] << endl;
	}
}

void printArray(string theArray[], int sizeOfArray)
{
	for (int x = 0; x < sizeOfArray; x++)
	{
		cout << theArray[x] << endl;
	}
}

void printArray(int theArray[3][2])
{
	for (int x = 0; x < 3; x ++)
	{
		for (int y = 0; y < 2; y++)
		{
			cout << theArray[x][y] << " ";
		}
		cout << endl;
	}
}
