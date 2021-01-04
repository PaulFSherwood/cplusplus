#include <vector>
using namespace std;

vector<int> selectionSort(vector<int> array) {
	int iMin;
	// Begin
	// for i := 0 to size-2 do //find minimum from ith location to size
	for (int i = 0; i < array.size()-2; i++)
	{
		// iMin := i;
		iMin = i;
		// for j:= i+1 to size – 1 do
		for (int j = i + 1; j < array.size(); j++)
		{
			// if array[j] < array[iMin] then
			if (array[j] < array[iMin])
			{
				// iMin := j
				iMin = j;
			}
		// done
		}
		// swap array[i] with array[iMin].
		iter_swap(array.begin() + i, array.begin() + iMin);
		// done
	}
	// End
  return {};
}
