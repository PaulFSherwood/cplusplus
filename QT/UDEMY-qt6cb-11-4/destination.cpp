#include "destination.h"

Destination::Destination(QObject *parent)
    : QObject{parent}
{

}

void Destination::mySlot(QString message)
{
    qDebug() << "Destination received message:" << message;

}
