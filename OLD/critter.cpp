//
#include <iostream>
using namespace std;

class Critter
{
public:
	void Greet();
};

void Critter::Greet()
{
	cout << "Hi. I'm a critter.\n";
}

int main()
{
	cout << "Instantiating a Critter object.\n\n";

	Critter crit;
	crit.Greet();

	return 0;
}
