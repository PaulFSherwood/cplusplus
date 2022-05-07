#include <vector>
using namespace std;

void printVector(vector<int> const &array);

vector<int> insertionSort(vector<int> array) {
  // setup
	int index, key, j;
	int size = array.size();
	for (index = 1; index < size; index++)
	{
		// save the current index
		key = array[index];
		// save the previous index (0 the smallest)
		j = index - 1;
		
		// move elemetns
		// if we are not at the front of the array and 
		// the array "j" is greater then the key
		// the while loop is conserced with push values to the right
		while ( j >= 0 && array[j] > key) // if the previous is larger than the current number
		{
			// printVector(array);
			// copy to next spot
			array[j + 1] = array[j];
			// go backwards
			j = j - 1;
		}
		// put the key in the previous slot
		// due the while exit j could be -1
		// after the while loop is concerned with pushing values to the left.
		array[j + 1] = key;
		
		cout << "==============================\n";
		printVector(array);
	}
  return array;
}

void printVector(vector<int> const &array)  
{  
	for(int i=0; i < array.size(); i++)
	{
		cout << array.at(i) << ' ';
	} cout << endl;
} 
