#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool LightSwitch = false;

    for (int i = 0; i<10; i++)
    {
        qInfo() << "Light switch is: " << LightSwitch << "\n";
        LightSwitch = !LightSwitch;
    }
    qInfo() << "Hello World\n My\tDude ↓ ";

    return a.exec();
}
