#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
#include <climits>
using namespace std;

// http://www.cplusplus.com/reference/algorithm/sort/
// http://www.cplusplus.com/reference/vector/vector/erase/

vector<int> findThreeLargestNumbers(vector<int> array) {
	vector<int> newArray;
	newArray = array;
	// if the array size is already good then just sort it
	if (array.size() == 3)
	{
		sort(newArray.begin(), newArray.end());
		// if the array size is too small just return the array
	} else if (newArray.size() < 3)
	{
		return array;
		// if the array size is larger than 3
	} else if (newArray.size() > 3) {
		// sort the array first
		sort(newArray.begin(), newArray.end());
		// keep just the last three elements
		while (newArray.size() >3 )
		{
			newArray.erase(newArray.begin());
		}
	}
	// show what the output isgoint to be
	for (int i = 0; i < newArray.size(); i++) { cout << newArray[i] << " "; } cout << "\n";
	
	return newArray;
}
