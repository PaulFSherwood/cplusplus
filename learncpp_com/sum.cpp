#include <iostream>
using namespace std;

int sumTo(int iSum)
{
	int newSum = 0;
	for (int i = 1; i <= iSum; i++)
	{
		newSum = newSum + i;
	}
	return newSum;

}

main ()
{
	cout << sumTo(5) << endl;
}
