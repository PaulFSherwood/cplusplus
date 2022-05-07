#include <vector>
using namespace std;

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
} 

vector<int> selectionSort(vector<int> array) {
	int iMin;
	// Begin
	// for i := 0 to size-2 do //find minimum from ith location to size
	for (int i = 0; i < array.size()-1; i++)
	{
		// iMin := i;
		iMin = i;
		// for j:= i+1 to size – 1 do
		// counter shifter
		for (int j = i + 1; j < array.size(); j++)
		{
			// if array[j] < array[iMin] then
			// Selection
			if (array[j] < array[iMin])
			{
				// iMin := j
				iMin = j;
			}
			// done
		}
		// swap
		swap(&array[iMin], &array[i]);  
		// swap array[i] with array[iMin].
		// swap(array.begin() + i, array.begin() + iMin);
		
		// done
	}
	// End
  return array;
}
