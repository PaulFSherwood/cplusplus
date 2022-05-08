#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QTime>
#include <array>
using namespace std;

enum Colors {
    red,
    green,
    blue
};

void delay(int a)
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, a);
}

// Precursor to classes
struct product
{
    int weight;
    double value;
    Colors color;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool LightSwitch = false;
    int ages[4] = {23, 7, 34, 1000};
    array<int,5> cars;
    cars = {0, 88, 55, 18, 12};

    Colors mycolor = Colors::green;

    for (int i = 0; i<3; i++)
    {
        qInfo() << "Light switch is: " << LightSwitch;// << "\n";
        LightSwitch = !LightSwitch;
        qInfo() << sizeof(i);
        qInfo() << "Ages[" << i << "]: " << ages[i];
        qInfo() << "Cars[" << i << "]: " << cars[i];
    }
    qInfo() << "##############################\n##############################\nHello World\n My\tDude " << mycolor;
    qInfo() << *ages;

    product laptop;
    qInfo() << "SizeOf: " << sizeof(laptop);

    laptop.color = Colors::green;
    laptop.value = 540.97;
    laptop.weight = 3;

    qInfo() << "Color: \t" << laptop.color <<
               "\nValue: \t" << laptop.value <<
                "\nWeight: \t" << laptop.weight << "\n";
    // qInfo() << laptop[0];  // can't access a struct by index
    qInfo() << "Size:" << cars.size();
    qInfo() << "SizeOf:" << sizeof(cars);

    int x = 10;
    qInfo() << "x between 5 and 20" << (x > 5 && x < 20);
    qInfo() << "x greater than 20 or greater than 8" << (x > 20 || x > 8);
    qInfo() << "x not not = to 10" << !(x != 10);
    qInfo() << "complex" << (x > 11 && x < 20 || x == 10);

    int bacon = 1;
    delay(5000);

    for (int i = 0; i < 10; i++)
    {
        system("CLS");

        //delay(100);
        bacon *= 2;
        qInfo() << "Bacon*10=" << bacon;
        delay(1000);
    }


    cout << "//C++ way" << endl;
    qInfo() << "//Qt way";
    // old stuff
    // cout << age;
    // cout << endl;
    // cout << flush;

    int number = 0;
    cin >> number;
    qInfo() << "Num:" << number;

    return a.exec();
}
