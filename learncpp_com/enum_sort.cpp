#include <iostream>
#include <string>
using namespace std;

int printArray(int numArray[], int index)
{
	for (int x = 0; x < index; x++)
	{
		if (x == index)
		{
			cout << numArray[x] << endl;
		}
		else
		{
			cout << numArray[x] << ", ";
		}
	}
	return numArray[index];
}

int main()
{
	const int nSize = 5;
	int anArray[nSize] = { 30, 50, 20, 10, 40 };
	cout << printArray(anArray, nSize-1) << endl;

	for (int nStartIndex = 0; nStartIndex < nSize; nStartIndex++)
	{
		int nSmallestIndex = nStartIndex;

		for (int nCurrentIndex = nStartIndex + 1; nCurrentIndex < nSize; nCurrentIndex++)
		{
			if(anArray[nCurrentIndex] < anArray[nSmallestIndex])
				nSmallestIndex = nCurrentIndex;
		}
		swap(anArray[nStartIndex], anArray[nSmallestIndex]);
		cout << printArray(anArray, nSize-1) << endl;
	}
	cout << printArray(anArray, nSize-1) << endl;
}
