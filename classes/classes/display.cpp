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
    cout << endl;
    cout << dude->getExperiance();
    cout << endl;
    cout << "==================\n";
}
