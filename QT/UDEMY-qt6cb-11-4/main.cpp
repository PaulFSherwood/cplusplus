/*
 * What
 * Connecting
 *
 * Why
 * We want to connect signals and slots
 *
 * How
 * See below
 */

#include <QCoreApplication>
#include <QDebug>
#include "source.h"
#include "destination.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Source oSource;
    Destination oDestination;

    QObject::connect(&oSource,     &Source::mySignal,
                     &oDestination,&Destination::mySlot);
    oSource.test();
    oDestination.mySlot("HI!");



    return a.exec();
}
