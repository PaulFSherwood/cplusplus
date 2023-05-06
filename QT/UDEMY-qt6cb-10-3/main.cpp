#include <QCoreApplication>
#include <QDebug>

// test string function
// Stack - COPY
void test(QString value)
{
    qInfo() << &value << "Size" << value.length();
} // Destroyed

// test string function using pointers
// Stack - Pointing
void testPtr(QString *value)
{
    qInfo() << "P" <<  value << "Size:" << value->length();
    qInfo() << "A" << &value << "Size:" << value->length();
} // Destroyed

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "\n\n";

    // Make a QString name called bryan
    QString name = "Bryan";  // Stack
    qInfo() << &name << "Size" << name.length();

    test(name);
    testPtr(&name);

    return a.exec();
}
