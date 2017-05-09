#include "ogre.h"
#include <iostream>
using namespace std;

int Ogre::getHealth() const
{
    return health;
}

void Ogre::setHealth(int value)
{
    health = value;
}

void Ogre::talk()
{
    cout << "im attacking" << endl;
    cout << "health: " << health << endl;
    cout << "strength: " << strength << endl;
}

Ogre::Ogre()
{
        health = 5;
        strength = 10;
}
