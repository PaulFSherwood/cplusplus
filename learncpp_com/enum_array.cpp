#include <iostream>
#include <string>
using namespace std;

int main()
{
	enum Buisnessone
	{
		EMPLOYEES = 10,
		PAYSCALELEVEL1 = 7,
		PAYSCALELEVEL2 = 10,
		PAYSCALELEVEL3 = 17,
		VISITORS = 3,
		MAXEMPLOYEES = 10,
	};

	string employees[EMPLOYEES] = {"jim", "bob", "fred", "sarah", "jim", "paul", "jerry", "mark", "ann", "meg"};

	cout << employees[0] << endl;
}
