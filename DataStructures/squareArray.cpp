// INPUT
// array = [1, 2, 3, 5, 6, 8, 9]
// 
// OUTPUT
// array = [1, 4, 9, 25, 36, 64, 81]

#include <vector>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

vector<int> sortedSquaredArray(vector<int> array) {
  // Write your code here.
	vector<int> muhArray;
	int holder = 0;
	// set power 2 for the vector
	for (int i : array)
	{
		holder = i;
		muhArray.push_back(pow(holder, 2));
		cout << "I: " << holder << "\t I2: " << pow(holder, 2) << endl;
		holder = 0;
	}
	cout << endl;
	sort(muhArray.begin(), muhArray.end());  // they probably want me to do this by hand.
  return muhArray;
}
