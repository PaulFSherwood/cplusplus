#include <QCoreApplication>
#include <QProcess>
#include <iostream>
#include <QDebug>
using namespace std;

void mainDisplay()
{
    qInfo() << "File\tEdit\tView\tQuit";
}
void fileDisplay()
{
    qInfo() << "File\tEdit\tView\tQuit";
    qInfo() << "Open";
    qInfo() << "Save";
    qInfo() << "Close";
}
void editDisplay()
{
    qInfo() << "File\tEdit\tView\tQuit";
    qInfo() << "\tUndo";
    qInfo() << "\tRedo";
    qInfo() << "\tCut";
}
void viewDisplay()
{
    qInfo() << "File\tEdit\tView\tQuit";
    qInfo() << "\t\tShow";
    qInfo() << "\t\tHide";
    qInfo() << "\t\tPane";
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool isRunning = true;
    char selection ='l';

    mainDisplay();

    while (isRunning)
    {
        qInfo() << "Please enter your selection: ";
        cin.get(selection);
        cout << "\n";
        switch (selection) {
        case 'f': // if age == 0
            QProcess::execute("CLS");
            fileDisplay();
            break;
        case 'e':
            QProcess::execute("CLS");
            editDisplay();
            break;
        case 'v':
            QProcess::execute("CLS");
            viewDisplay();
            break;
        case 'q':
            isRunning = false;
            break;
        default:
            QProcess::execute("CLS");
            mainDisplay();
            break;
        }
    }

    return a.exec();
}
