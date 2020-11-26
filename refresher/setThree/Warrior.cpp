#include <iostream>
#include <cmath>
#include "Warrior.h"

Warrior::Warrior(int startLevel):Level(startLevel)
{
    setAgility (startLevel);
    setStrength(startLevel);
    setStamina (startLevel);
    std::cout << "\nAgility: " << getAgility() << "\tStrength: " << getStrength() << "\nStamina: " << getStamina() << "\tLevel: " << getLevel() <<  std::endl;
}
int Warrior::getAgility()    { return Agility;   }
int Warrior::getStrength()   { return Strength;  }
int Warrior::getStamina()    { return Stamina;   }
int Warrior::getLevel()      { return Level;     }

void Warrior::setAgility(int LEVEL)
{   // =(1/$E$2)*(EXP(($E$2+A2)/$E$3))
    const double A = 0.095;
    const double B = 22.5;
    Agility = (1/A)*(exp((A+LEVEL)/B));
}
void Warrior::setStrength(int LEVEL)
{   // =(1/$E$2)*(EXP(($E$2+A2)/$E$3))
    const double A = 0.06;
    const double B = 22.4;
    Strength = (1/A)*(exp((A+LEVEL)/B));
    // std::cout << "           (1/A): " << (1/A) << std::endl;
    // std::cout << "       (A+LEVEL): " << (A+LEVEL) << std::endl;
    // std::cout << "    (A+LEVEL)/B): " << ((A+LEVEL)/B) << std::endl;
    // std::cout << "Current Strenght: " << Strength << std::endl;
}
void Warrior::setStamina(int LEVEL)
{   // =(1/$E$2)*(EXP(($E$2+A2)/$E$3))
    const double A = 0.1;
    const double B = 22.3;
    Stamina = (1/A)*(exp((A+LEVEL)/B));
}
void Warrior::setLevel(int LEVEL)
{
    Level = LEVEL;
}
Warrior::~Warrior()
{
}