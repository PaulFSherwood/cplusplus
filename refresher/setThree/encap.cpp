#include <iostream>
#include <cmath>

class Warrior
{

public:
    Warrior(int startLevel);   // I guess this will end up in the .h files
    ~Warrior();
    // I think I am doing wrong here, should this setion only be definisitons?
    int getAgility();
    int getStrength();
    int getStamina();
    int getLevel();
    // ============================
    void setAgility (int LEVEL);
    void setStrength(int LEVEL);
    void setStamina (int LEVEL);
    void setLevel   (int LEVEL);

    private:
        /* data */
        int Agility;
        int Strength;
        int Stamina;
        int Level;
};
Warrior::Warrior(int startLevel):Level(startLevel)
{
    setAgility(startLevel);
    setStrength(startLevel);
    setStamina(startLevel);
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
    Agility = (1/B)*(exp((A+LEVEL)/B));
}
void Warrior::setStrength(int LEVEL)
{   // =(1/$E$2)*(EXP(($E$2+A2)/$E$3))
    const double A = 0.06;
    const double B = 22.4;
    Strength = (1/B)*(exp((A+LEVEL)/B));
}
void Warrior::setStamina(int LEVEL)
{   // =(1/$E$2)*(EXP(($E$2+A2)/$E$3))
    const double A = 0.1;
    const double B = 22.3;
    Stamina = (1/B)*(exp((A+LEVEL)/B));
}
void Warrior::setLevel(int LEVEL)
{
    Level = LEVEL;
}
Warrior::~Warrior()
{
}

int main() {
	int x = 0;

	Warrior john(10);

    john.setStrength(10);

    std::cout << john.getAgility() << std::endl;
    std::cout << john.getStrength() << std::endl;
    std::cout << john.getStamina() << std::endl;


	return 0;
}