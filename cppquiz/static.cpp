#include <iostream>
using namespace std;

class Something
{
	public:
		static int s_nValue;
};

int Something::s_nValue = 1;

int main()
{
	Something cFirst;
	cout << cFirst.s_nValue << endl;
	cFirst.s_nValue = 2;

	Something cSecond;
	cout << cSecond.s_nValue << endl;

	return 0;
}
