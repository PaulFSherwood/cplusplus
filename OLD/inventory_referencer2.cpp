// Inventory Referencer
// Demonstrates returning a reference

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// returns a reference to a string
string& reftoElement(vector<string>& vec, int i);

int main()
{
 	int rStr;
 	int str;
 	int Rstr;
 	int rstr;
 	
 	vector<string> inventory;
 	inventory.push_back("sword");
 	inventory.push_back("armor");
 	inventory.push_back("shield");
 	inventory.push_back("null");
 	
 	cout << "inv 1:";
 	cin >> rStr;
 	cout << "inv 2:";
 	cin >> str;
 	cout << "inv 3:";
 	cin >> Rstr;
 	cout << "inv 4:";
 	cin >> rstr;
 	
 	// displays string that the returned reference refers to
 	cout << "\n\ninventory:\n";
 	cout << reftoElement(inventory, 0) << "\n";
 	string& rStr = reftoElement(inventory, 1);
 	cout << rStr << "\n";
 	string Rstr = reftoElement(inventory, 2);
 	cout << Rstr << "\n";
 	string rstr = reftoElement(inventory, 3);
 	cout << rstr << "\n";
 	
 	// altering the string ovject through a returned reference
 	cout << "Altering an object through a returned reference.\n";
 	rStr = "Healing Potion";
 	cout << "Sending the altered object to cout:\n";
 	cout << inventory[1] << endl;
 	return 0;
}

// returns a reference to a string
string& reftoElement(vector<string>& vec, int i)
{
 		return vec[i];
}
