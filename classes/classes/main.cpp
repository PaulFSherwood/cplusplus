#include <QCoreApplication>
#include <iostream>
#include "ogre.h"
#include "display.h"
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

    return a.exec();
}
