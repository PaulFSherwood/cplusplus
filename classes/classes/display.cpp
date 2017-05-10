#include "display.h"
#include <iostream>
using namespace std;

Display::Display()
{
}

void Display::showScene(Player * dude)
{
    // basic show all the users stats
    cout << "==================\n";
    cout << "Health: " << dude->getHealth() << endl;
    cout << "Strength: " << dude->getStrength() << endl;
    cout << "Exeperiance" << dude->getExperiance() << endl;
    cout << "==================\n\n";
    cout << "(F)ight" << endl;
    cout << "(H)eal" << endl;
    cout << "(X)it" << endl;

}

void Display::showFight(Player *dude)
{
    // create a new bad guy
    Ogre *baddie = new Ogre(90, 15);
    // get the user some info sto start
    cout << "++++++++++" << endl;
    cout << "++++++++++" << endl;
    cout << "fight is as follows" << endl;
    cout << "you get first strike" << endl;

    while (dude->getHealth() >= 0 || baddie->getHealth() >= 0) {
        // stat update
        cout << "Player HP: " << dude->getHealth() << "Player Str: " << dude->getStrength() << endl;
        cout << "Baddie HP: " << baddie->getHealth() << "Baddie Str: " << baddie->getStrength() << endl;
        // remove some health from everyone
        baddie->setHealth(baddie->getHealth() - dude->getStrength());
        dude->setHealth(dude->getHealth() - baddie->getStrength());
        // udate the player
        cout << "You hit for " << dude->getStrength()<< endl;
        cout << "Baddie hit for " << baddie->getStrength()<< endl;
        // WIN condition
        if (baddie->getHealth() <= 0){
            cout << "==============================" << endl;
            cout << "Player HP: " << dude->getHealth() << "Player Str: " << dude->getStrength() << endl;
            cout << "Baddie HP: " << baddie->getHealth() << "Baddie Str: " << baddie->getStrength() << endl;
            cout << "YOU WIN!!!" << endl;
            // give the user some expericance
            dude->setExperiance(dude->getExperiance()+10);
            // level up stats for the player if they have over 100 exp.
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
