#include <iostream>
#include <cmath>
#include "Warrior.h"

Warrior::Warrior(int startLevel):Level(startLevel)
{}
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

void Warrior::SetHpCap(int hpCap) { HpCap = hpCap; }
void Warrior::SetHpCurrent(int hpCurrent) { HpCurrent = hpCurrent; }

void Warrior::SetWeapon(int weapon) { Weapon = weapon; }
void Warrior::SetArmor(int armor) { Armor = armor; }

void Warrior::SetAtk(int atk) { Atk = atk; }
void Warrior::SetDef(int def) { Def = def; }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int Warrior::GetHpCap() { return HpCap; }
int Warrior::GetHpCurrent() { return HpCurrent; }
int Warrior::GetLvl() { return Level; }

int Warrior::GetWeapon() { return Weapon; }
int Warrior::GetArmor() { return Armor; }

int Warrior::GetAtk() { return Atk; }
int Warrior::GetDef() { return Def; }

void Warrior::PrintStats()
{
    std::cout << "HP: " <<  Warrior::GetHpCurrent() << std::endl;
    std::cout << "Lvl: " <<  Warrior::GetLvl() << std::endl;
    std::cout << "Wepon: " <<  Warrior::GetWeapon() << std::endl;
    std::cout << "Armor: " <<  Warrior::GetArmor() << std::endl;
    std::cout << "Atk: " <<  Warrior::GetAtk() << std::endl;
    std::cout << "Def: " <<  Warrior::GetDef() << std::endl;
}


Warrior::~Warrior()
{
}