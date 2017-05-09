#include <QCoreApplication>
#include "ogre.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Ogre t;

    t.talk();

    cout << "\nt Health: " << t.getHealth();
    t.setHealth(88);
    cout << "\nt Health: " << t.getHealth();

    return a.exec();
}
