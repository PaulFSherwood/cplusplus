// INPUT 
// array = [3,5,-4,8,11,1,-1,6]
// targetSum = 10
//
// OUTPUT
//
// THIS FAILES BUT I NEED TO GOTO BED
//
#include <vector>
using namespace std;

vector<int> twoNumberSum(vector<int> array, int targetSum) {
  // Write your code here.
  vector<int> f;
	
	for (int i = 0; i < array.size(); i++)
	{
		for (int j = 0; j < array.size(); j++)
		{
			if (array[i] + array[j] == targetSum  && j != i)
			{
				// This output is not matching what is pushed
				cout << "Index[i]=" << i << "\tIndex[j]=" << j << std::endl;
				cout << "target: " << targetSum << "Total: " << array[i] << " + " << array[j] << " = " << array[j] + array[i] << endl;
				f.insert(f.end(), {array[i], array[j]});
				return f;
			}
		}
	}
  return f;
}

// [10]
// {
//   "array": [3, 5, -4, 8, 11, 1, -1, 6],
//   "targetSum": 15
// }
