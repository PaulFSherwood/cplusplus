#include <iostream>
#include <vector>

using namespace std;

int main() {
	// Format: vector<DataType> nameOfVector
	// myVector.push_back(value) ==> adds an element ot the end of the vecotr (also resizes it)
	// myVector.at(index) ==> return element at specified index number
	// myVector.size() == returns an unsigned int equal top the number of elements
	// myVector.begin() == reads vecotr from first element (index 0)
	// myVector.insert(myVector.begin() + integer, new value) ==> adds element BEFORE specified index number
	// myVector.erase(myVector.begin() + interger) ==> removes elements AT specified index number
	// myVector.clear() ==> removes all elements in vecotr
	// myVector.empty() ==> returns boolean value if whether vector is empty

	vector<int> myVector;

	myVector.push_back(3);
	myVector.push_back(7);
	myVector.push_back(4);
	myVector.push_back(12);
	myVector.push_back(9);

	cout << "\nVector: ";
	
	for (unsigned int i = 0; i < myVector.size(); i++) {
		cout << myVector[i] << " ";
	}

	myVector.insert(myVector.begin(), 5);

	cout << "\nVector: ";
	
	for (unsigned int i = 0; i < myVector.size(); i++) {
		cout << myVector[i] << " ";
	}

	myVector.erase(myVector.begin() + 4);

	cout << "\nVector: ";
	
	for (unsigned int i = 0; i < myVector.size(); i++) {
		cout << myVector[i] << " ";
	}

	if (myVector.empty()) {
		cout << endl << "Is empty!\n";
	} else {
		cout << endl << "Is NOT empty\n";
	}

	myVector.clear();
	
	if (myVector.empty()) {
		cout << endl << "Is empty!\n";
	} else {
		cout << endl << "Is NOT empty\n";
	}

	cout << "\n";

	return 0;
}