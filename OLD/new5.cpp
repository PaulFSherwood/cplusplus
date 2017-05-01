#include <iostream>
using namespace std;

void lessthanI()
{
	cout << "and it is less than I\n";
}
void greatthanI()
{
	cout << "and it is greater than I\n";
}

int main(){
	int i;
	cout << "pic a number between 1-100" << endl;
	cin >> i;
	cout << "your current number is " << i << endl;
	if (i < 50)
	
		lessthanI();
	else if (i > 50)
		greatthanI();
	else
		cout << "what you tinking fool";
	return 0;
}


