#include <QCoreApplication>
#include "feline.h"
#include "canine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Canine dog;
    Feline cat;

    return a.exec();
}
