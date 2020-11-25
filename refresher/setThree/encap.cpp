#include <iostream>
#include <cmath>

class Warrior
{
private:
    /* data */
    int Agility;
    int Strength;
    int Stamina;
    int Level;

public:
    Warrior(/* args */);
    ~Warrior();

    int returnAgility(int LEVEL)
    {
        // =(1/$E$2)*(EXP(($E$2+A2)/$E$3))
        // B = constant of .1
        const double A = 0.095;
        const double B = 22.5;

        return (1/B)*(exp((A+LEVEL)/B));

    }
};

Warrior::Warrior(/* args */)
{
}

Warrior::~Warrior()
{
}
