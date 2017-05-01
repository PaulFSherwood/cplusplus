// Inventory Pointer
// Demonstrates returning a pointer

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// returns a pointer to a string element
string* ptrtoElement(vector<string>* const pVec, int i);

int main()
{
 	vector<string> inventory;
 	inventory.push_back("sword");
 	inventory.push_back("armor");
 	inventory.push_back("shield");
 	
 	// displays string object that the returned pointer points to
 	cout << "Senging the objected pointed to by returned point:\n";
 	cout << *(ptrtoElement(&inventory, 0)) << "\n\n";
 	
 	// assigns one pointer to another -- inexpensive assignment
 	cout << "Assigning the returned pointer to another pointer.\n";
 	string* pStr = ptrtoElement(&inventory, 1);
 	cout << "Sending the object pointed to by new pointer to cout:\n";
 	cout << *pStr << "\n\n";
 	
 	// copies a string object -- expensive assignment
 	cout << "Assinging object pointed by pointer to a string object.\n";
 	string str = *(ptrtoElement(&inventory, 2));
 	cout << "Sending the new string object to cout:\n";
 	cout << str << "\n\n";
 	
 	// altering the string object through a returned pointer
 	cout << "Altering an object through a returned pointer.\n";
 	*pStr = "Healing Potion";
 	cout << "Sending the altered object to cout:\n";
 	cout << inventory[1] << endl;
 	
 	// altering the string object through a returned pointer
 	cout << "enter your item.\n";
 	cin >> *pStr;
 //	*pStr = item;
 	cout << "\n\nSending the altered object to cout:\n";
 	cout << inventory[0] << endl;
 	cout << inventory[1] << endl;
 	cout << inventory[2] << endl;
 	
 	return 0;
}

string* ptrtoElement(vector<string>* const pVec, int i)
{
 		// returns address of the string in poisition i of vector that pVec points to
 		return &((*pVec)[i]);
}

