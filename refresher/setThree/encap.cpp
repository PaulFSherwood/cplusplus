#include <iostream>
#include "Warrior.h"
#include "Rogue.h"


int main() {
	// int x = 0;

	Warrior john(10);
    Rogue marry(110);
    int i = 10;
    int j = 11;

    // test run
    john.setStrength(i);
    john.setAgility(i);
    john.setStamina(i);
    john.setLevel(i);
    std::cout << "\nAgility: " << john.getAgility() << "\tStrength: " << john.getStrength() << "\tStamina: " << john.getStamina() << "\tLevel: " << john.getLevel();

    // test rogue
    marry.setAgility(i);
    marry.setLevel(j);
    marry.setStamina(j);
    marry.setStrength(j);
    std::cout << "\nAgility: " << marry.getAgility() << "\tStrength: " << marry.getStrength() << "\tStamina: " << marry.getStamina() << "\tLevel: " << marry.getLevel();

    
	return 0;
}