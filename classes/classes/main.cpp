#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <iostream>
#include "display.h"
#include "ogre.h"
#include "player.h"
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // create a new player set health and experience
    Player *myDude = new Player(100, 25, 0);
    Display *myDisplay = new Display();

    // display is ready push to screen
    myDisplay->showScene(myDude);

    cout << endl;
    bool isRunning = true;
    ///////////////
    // main loop //
    while(isRunning) {
        // get user input
        char input;
        cin >> input;
        myDisplay->showScene(myDude);
        /* select based on user input */
        switch( input ) {
            case 'F':   // Fight
            {
                cout << "Fighting" << endl;
                myDisplay->showFight(myDude);
                break;
            }
            case 'H': // restore health
            {
                myDisplay->showHeal(myDude);
                break;
            }
            default:
            {
                // I dont have something to put here
                break;
            }
        }

        if (input == 'X') {
            qDebug() << "eXiTiNg ThE lOoP" << endl;
            isRunning = false;
        } else {

        }
    }

    // clean up
    delete myDude;
    delete myDisplay;
    return a.exec();
}
