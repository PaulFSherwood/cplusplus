/*
 * What
 * Pointer memory management
 *
 * Why
 * Pointers are fast but we have to manage them
 *
 * How
 * See be
 */


#include <QCoreApplication>

void display(QString *value)
{
    qInfo() << "The pointer" << value;
    qInfo() << "The address" << &value;
    qInfo() << "The data" << *value;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString name = "Bryan";  // Stack - C++ manages this

    QString *description = new QString("Hello pointer"); //Heap - we have to manage this  "NEW" is HEAP
    //    qInfo() << description;

    display(description);



    delete description; //delete the pointer
    //    display(description);
    return a.exec();
}
