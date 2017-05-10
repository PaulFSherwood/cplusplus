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
    cout << "(F)ight" << endl;
    cout << "(H)eal" << endl;

}

void Display::showFight(Player *dude)
{
    Ogre *baddie = new Ogre(90, 15);

    cout << "++++++++++" << endl;
    cout << "++++++++++" << endl;
    cout << "fight is as follows" << endl;
    cout << "you get first strike" << endl;

    while (dude->getHealth() >= 0 || baddie->getHealth() >= 0) {
        cout << "Player HP: " << dude->getHealth() << "Player Str: " << dude->getStrength() << endl;
        cout << "Baddie HP: " << baddie->getHealth() << "Baddie Str: " << baddie->getStrength() << endl;
        baddie->setHealth(baddie->getHealth() - dude->getStrength());
        cout << "You hit for " << dude->getStrength()<< endl;
        dude->setHealth(dude->getHealth() - baddie->getStrength());
        cout << "Baddie hit for " << baddie->getStrength()<< endl;
        if (baddie->getHealth() <= 0){
            cout << "==============================" << endl;
            cout << "Player HP: " << dude->getHealth() << "Player Str: " << dude->getStrength() << endl;
            cout << "Baddie HP: " << baddie->getHealth() << "Baddie Str: " << baddie->getStrength() << endl;
            cout << "YOU WIN!!!" << endl;
            dude->setExperiance(dude->getExperiance()+10);
            if (dude->getExperiance() > 100) {
                dude->setHealth(dude->getHealth() + 10);
                dude->setStrength(dude->getStrength() + 2);
            }
            cout << "Xp awarded" << endl;
            cout << endl;
            break;
        }
    }
    showScene(dude);
}

void Display::showHeal(Player *dude)
{
    // THIS IS pretty much broken
    cout << "+=+=+=+=+=+=+=+=+=+=+" << endl;
    cout << "cleansing your booboos" << endl;
    dude->setHealth(100);
    showScene(dude);
}
