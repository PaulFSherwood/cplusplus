#include <QCoreApplication>
#include "feline.h"
#include "canine.h"

/*
 * From VoidRealms
 * https://github.com/voidrealms/qt6-core-beginners/tree/main/section%208/qt6cb-8-4
 */

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Canine dog;
    Feline cat;

    return a.exec();
}
