#include <QCoreApplication>
#include <QDebug>
#include "agecalc.h"

void print(AgeCalc &calc)
{
    qInfo() << calc.name() << "Human Years" << calc.humanYears();
    qInfo() << calc.name() << "Human Years" << calc.catYears();
    qInfo() << calc.name() << "Human Years" << calc.dogYears();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AgeCalc bryan;
    AgeCalc tammy;

    bryan.setName("Bryan");
    bryan.setAge(46);
    tammy.setName("Tammy");
    tammy.setAge(27);

    print(bryan);
    print(tammy);
    return a.exec();
}
