#include <iostream>
#include<cmath>
using namespace std;

int main(){
	double num1;	// should be for numbers with points lik 2.1  4.8
	cout << "Pick your number..." << endl;
	cin >> num1;
	double num2;
	num2 = sqrt(num1);
	cout << "The square root of " << num1 << " is " << num2 << endl;
	
	
	return 0;
}
