#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

vector<int> findThreeLargestNumbers(vector<int> array) {
	vector<int> one;
	
	cout << "Max element: " << *max_element(array, array.size()) << "\n";
	cout << "Max element location: " <<
  distance(array, max_element(array, array.size())) << "\n";
	
  return {};
}
