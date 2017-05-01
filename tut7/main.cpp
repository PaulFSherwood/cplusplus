#include <iostream>
#include "Map.h"

using namespace std;

int main() {
	int x = 0;

	Map john(90,100);

	john.attack();
	john.beAttacked();
	john.heal(3);
	x = john.GetHealth();
	cout << john.GetHealth();
	cout << endl << x << endl;
	
	char mainarray[2][2];
	
	mainarray[2][2] = john.GetMap();
	
	// these two loops print the array.
	int a, b;
	for (a = 0; a <= 2; a++)
	{
		for (b = 0; b <= 2; b++)
		{
			printf("%c", mainarray[a][b]);
		}
		printf("\n");
	}
	
	
	system("PAUSE");

	return 0;
}
