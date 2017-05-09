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
    Player *myDude = new Player(100, 0);
    Display *myDisplay = new Display();

    cout << endl;
    bool isRunning = true;
    while(isRunning) {
        QTextStream qtin(stdin);
        QString line = qtin.readLine();
        myDisplay->showScene(myDude);
        if (line == "false") {
            qDebug() << "rEADY TO eXiT" << endl;
            isRunning = false;
        } else {

        }
    }

    // clean up
    delete myDude;
    delete myDisplay;
    return a.exec();
}
