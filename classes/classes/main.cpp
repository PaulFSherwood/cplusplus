#include <QCoreApplication>
#include "ogre.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Ogre t;

    t.talk();

    return a.exec();
}
