#include <vector>
#include <iostream>
using namespace std;

vector<int> twoNumberSum(vector<int> array, int targetSum) {
	std::vector<int> match;					// I forgot how to create a vector STUDY **
	// we are going to need to go through each section of the array
	for (int i = 0; i < array.size(); i++)
	{
		// then from that index test againts any other array index
		for (int j = 0; j < array.size(); j++)
		{
			// if the index is the same ignore it
			if (j == i) {}
			else
			{
				// now we are going to test for the targetSum
				if (array[i] + array[j] == targetSum)
				{
					match.push_back(array[i]);					// I forgot how to add to a vector STUDY **
					match.push_back(array[j]);
					return match;
				}
				// no match found
				else
				{
					
				}
			}
		}
	}
  return {};
}
