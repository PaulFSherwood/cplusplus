#include "display.h"
#include <iostream>
using namespace std;

Display::Display()
{
}

void Display::showScene(Player * dude)
{
    cout << "==================\n";
    cout << dude->getHealth();
    cout << dude->getExperiance();
    cout << "==================\n";
}
