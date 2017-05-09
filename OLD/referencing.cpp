// Referencing
// demonstrates using references

#include <iostream>

using namespace std;

int main()
{
 	int myscore = 1000;
 	int& mikesscore = myscore; //create a reference
 	
 	cout << "myscore is: " << myscore << "\n";
 	cout << "mikescore is: " << mikesscore << "\n\n";
 	
 	cout << "Adding 500 to myscore\n";
 	myscore += 500;
 	cout << "myscore is: " << myscore << "\n";
 	cout << "mikesscore is " << mikesscore << "\n\n";
 	
 	cout << "Adding 500 to mikesscore\n";
 	mikesscore += 500;
 	cout << "myscore is: " << myscore << "\n";
 	cout << "mikesscore is " << mikesscore << "\n\n";
 	
 	return 0;
}
