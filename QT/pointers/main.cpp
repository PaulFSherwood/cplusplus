#include <QCoreApplication>
#include <QDebug>

void test (QString value) // Stack - copy
{
    qInfo() << &value << "Size: " << value.length();
} // Destroy
void testPtr(QString *value) // Stack - Pointing
{
    qInfo() << value << "Size: " << value->length();
    qInfo() << &value << "Size: " << value->length();
}// destroy

void display (QString *value)
{
    qInfo() << "The pointer" << value;
    qInfo() << "The address" << &value;
    qInfo() << "The data" << *value;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString name = "AbadabaDOO"; // STACK
    QString *description = new QString("Hello Pointer");

    qInfo() << &name << "Size: " << name.length();

    test(name);
    testPtr(&name);

    delete description;

    return a.exec();
}
