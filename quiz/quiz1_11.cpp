#include <iostream>
using namespace std;

int ReadNumber(int i);
void WriteAnswer(int x);

int main()
{
	int x = ReadNumber(1);
	int y = ReadNumber(2);
	WriteAnswer(x+y);
	return 0;
}

