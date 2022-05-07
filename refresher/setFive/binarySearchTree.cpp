#include <vector>
using namespace std;

int binarySearch(vector<int> array, int target) {
	// setup
	int L = 0;
	int R = array.size() - 1;
	int current = 0;
	for (int i = 0; i < array.size(); i++) { cout << array[i] << " "; }
	while (L <= R) {
		cout << "\nL: " << L << " R: " << R << " Current: " << current << " No: " << array[current] << " target: " << target;
		current = floor((L + R) / 2); //floor(L + (R - 1)/2); //
		if (array[current] == target)
		{
			cout << "\nL: " << L << " R: " << R << " Current: " << current << " No: " << array[current] << " target: " << target;
			return current;
		}			
		else if (array[current] < target)
		{
			L = current + 1;
		}	else {
			R = current - 1;
		}
  }
	return -1;
}
