#include <iostream>
using namespace std;

void CountDown(int nValue)
{
	cout << nValue << "---";
	
	if (nValue > 0)
	CountDown(nValue -1);
}

int main(void)
{
	CountDown(10);
}
