#include <QCoreApplication>
#include <QDebug>
#include <stdio.h>

void test(int number)
{
    qInfo() << "1 - Number: " << &number << " = " << number;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int number = 75;

    qInfo() << "1 - Number: " << &number << " = " << number;
    test(76);

    for (int i = 0; i < 12; i++)
    {
        int *ptr = &number-(1*i);
        qInfo() << 3+i << "- Number: " << ptr << " = " << *ptr;
    }
    return a.exec();
}
