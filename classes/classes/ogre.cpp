#include "ogre.h"
#include <iostream>
using namespace std;


Ogre::Ogre(int a, int b)
{
    health = a;
    strength = b;
}

void Ogre::talk()
{
    cout << "im attacking" << endl;
    cout << "health: " << getHealth() << endl;
    cout << "strength: " << getStrength() << endl;
}

int Ogre::getHealth() const
{
    return health;
}

void Ogre::setHealth(int value)
{
    health = value;
}

int Ogre::getStrength() const
{
    return strength;
}

void Ogre::setStrength(int value)
{
    strength = value;
}
