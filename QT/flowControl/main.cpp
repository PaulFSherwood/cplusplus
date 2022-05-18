#include <QCoreApplication>
#include <iostream>
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool isRunning = true;
    int age = 0;

    // age > 0 && age < 100 ? qInfo("You entered a valid age.") : qFatal("You didn't enter a valid age.");

    while (isRunning)
    {
        qInfo() << "Please enter your age: ";
        cin >> age;
        cout << "test\n";
        switch (age) {
        case 0 ... 15: // if age == 0
            qInfo() << "You did enter a valid age of " << age;
            break;
        case 16 ... 17:
            qInfo() << "You can drive at " << age;
            break;
        case 18:
            qInfo() << "You can vote at " << age;
            break;
        case 19 ... 54:
            qInfo() << "You should be working at " << age;
            break;
        case 55 ... 200:
            qInfo() << "You can retire at " << age;
            break;
        default:
            qFatal("I dunno what you did here.");
            isRunning = false;
            break;
        }
    }


    return a.exec();
}
