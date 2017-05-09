#include "display.h"
#include <iostream>
using namespace std;

Display::Display()
{
}

void Display::showScene(Ogre & dude)
{
    cout << dude.getHealth();
}
