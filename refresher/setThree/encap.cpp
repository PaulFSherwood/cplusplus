#include <iostream>
#include "Warrior.h"


int main() {
	// int x = 0;

	Warrior john(10);

    // leved up
    for (int i = 1; i < 51; i++)
    {
        john.setStrength(i);
        john.setAgility(i);
        john.setStamina(i);
        john.setLevel(i);
        std::cout << "\nAgility: " << john.getAgility() << "\tStrength: " << john.getStrength() << "\tStamina: " << john.getStamina() << "\tLevel: " << john.getLevel();
    }
    
	return 0;
}