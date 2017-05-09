#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <iostream>
#include "ogre.h"
#include "display.h"
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Ogre t;
    Display scene;

    t.talk();

    cout << "\nt Health: " << t.getHealth();
    t.setHealth(88);
    cout << "\nt Health: " << t.getHealth();

    t.setHealth(101);
    cout << endl;
    scene.showScene(t);
    bool isRunning = true;
    while(isRunning) {
        QTextStream qtin(stdin);
        QString line = qtin.readLine();  // this is how you read
    //    QString word;
    //    qtin >> word;
        qDebug() << "\n LINE: " << line << endl;
        if (line == "false") {
            qDebug() << "rEADY TO eXiT" << endl;
            isRunning = false;
        } else {
            QString str = line;
            bool ok;
            int numBer = str.toInt(&ok, 10);
            t.setHealth(numBer);
            cout << "\ngetHealth: " << t.getHealth();
        }
    }
    return a.exec();
}
