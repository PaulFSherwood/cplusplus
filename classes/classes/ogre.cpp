#include "ogre.h"
#include <iostream>
using namespace std;

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
