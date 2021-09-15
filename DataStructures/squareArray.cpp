// INPUT
// array = [1, 2, 3, 5, 6, 8, 9]
// 
// OUTPUT
// array = [1, 4, 9, 25, 36, 64, 81]

#include <vector>
using namespace std;

vector<int> sortedSquaredArray(vector<int> array) {
  // Write your code here.
	vector<int> muhArray;
	for (int i : array)
	{
		muhArray.push_back(i);
		cout << "I: " << i << " ";
	}
	cout << endl;
  return muhArray;
}
