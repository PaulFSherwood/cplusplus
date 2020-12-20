#include <vector>
#include <algorithm>
using namespace std;

void swap(int* x, int* y)
{
	// direct address altering
	int temp = *x;
	*x = *y;
	*y = temp;
}
vector<int> bubbleSort(vector<int> array) {
  // geeksforgeeks
	// search through array
	for (int i = 0; i < array.size() - 1; i++)
	{
		// on each element compare
		for (int j = 0; j < array.size() - i - 1; j++)
		{
			// if the next index is larger swap them
			if (array[j] > array[j + 1])
			{
				swap(&array[j], &array[j + 1]);
			}
		}
	}
	return array;
}
