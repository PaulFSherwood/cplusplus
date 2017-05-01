#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class baseball
{
public:
	void team(string city, string state);
};

int main()
{

baseball bObject;
bObject.team("denver", "colorado");

}

void baseball::team(string city, string state)
{
	cout <<  city << " " << state << endl;
}
