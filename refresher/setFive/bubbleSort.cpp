#include <vector>
#include <algorithm>
using namespace std;

vector<int> bubbleSort(vector<int> array) {
  
	int n = array.size();
	bool swapped = false;
	
	while(!swapped)
	{
		for (int i = 0; i < n-1; i++)
		{
			if (array[i-1] > array[i])
			{
				iter_swap(array.begin() + i - 1, array.begin() + i);
				swapped = true;
			}
		}
	}
  return array;
}
