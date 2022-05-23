#include <QCoreApplication>
#include <QProcess>
#include <iostream>
#include <QDebug>
using namespace std;

int getArea(int w, int h)
{
    qInfo() << "area:" << w * h;
    return w * h;  // returns the area of a wall
}
double gallonArea(int area)
{
    return area / 360; // 360 is one gallon of paint  // this returns # of gallons
}
void widthQuestion()
{
    qInfo() << "Please enter your wall width";
}
void heightQuestion()
{
    qInfo() << "Please enter your wall height";
}
void exitConditionDisplay()
{
    qInfo() << "you can enter 0 to exit";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool isRunning = true;
    int width = 0;
    int height = 0;
    double total = 0;

    widthQuestion();

    while (isRunning)
    {
        qInfo() << "Please enter your selection: ";
        cin >> width;
        cout << "\n";
        //"Exiting program"
        switch (width) {
        case 0: // if age == 0
            isRunning = false;
            qInfo() << "Total gallon(s):" << total;
            qFatal("Exiting program");
            break;
        case 1 ... 100:
            qInfo() << "Width of: " << width << "accpeted please enter the height";
            cin >> height;
            if (height == 0) { qFatal("Exiting program"); } else {
                double temp = gallonArea(getArea(width, height));
                qInfo() << "Temp:"<< temp;
                total = total + temp;
                qInfo() << "total:" << total;
            }
            break;
        default:
            break;
        }
    }

    return a.exec();
}
