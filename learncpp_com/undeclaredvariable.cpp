#include <iostream>
using namespace std;

int findVolume(int l, int w, int h);

int main()
{
	int x;

	cout << x << endl;
	
	cout << "Find volume 2,3,5: ";
	cout << findVolume(2,3,5) << endl;
}


int findVolume(int l, int w, int h)
{
	return l * w * h;
}
