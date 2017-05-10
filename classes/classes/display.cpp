#include "display.h"
#include <iostream>
using namespace std;

Display::Display()
{
}

void Display::showScene(Player * dude)
{
    cout << "==================\n";
    cout << "Health: " << dude->getHealth();
    cout << endl;
    cout << "Strength: " << dude->getStrength();
    cout << endl;
    cout << "Exeperiance" << dude->getExperiance();
    cout << endl;
    cout << "==================\n\n";

}

void Display::showFight(Player *dude)
{
    Ogre *baddie = new Ogre(90, 15);

    cout << "++++++++++" << endl;
    cout << "++++++++++" << endl;
    cout << "fight is as follows" << endl;
    cout << "you get first strike" << endl;

    while (dude->getHealth() >= 0 || baddie->getHealth() >= 0) {
        baddie->setHealth(baddie->getHealth() - dude->getStrength());
        cout << "You hit for " << dude->getStrength();
        cout << endl;
        dude->setHealth(dude->getHealth() - baddie->getStrength());
        cout << "Baddie hit for " << baddie->getStrength();
        cout << endl;
    }
    if (baddie->getHealth() <= 0){
        cout << "YOU WIN!!!" << endl;
        cout << endl;
    }
}
