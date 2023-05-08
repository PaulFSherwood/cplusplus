/*
 * What
 * Qt date time classes
 *
 * Why
 * Makes dates and times easy
 *
 * How
 * See below
 *
 */

#include <QCoreApplication>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDate today = QDate::currentDate();
    qInfo() << today;
    qInfo() << today.addDays(1);
    qInfo() << today.addYears(20);

    // Different than Qt 5
    qInfo() << "ISODate: " << today.toString(Qt::DateFormat::ISODate);
    qInfo() << "RFC2822Date: " << today.toString(Qt::DateFormat::RFC2822Date);
    qInfo() << "TextDate: " << today.toString(Qt::DateFormat::TextDate);

    QTime now = QTime::currentTime();
    qInfo() << "ISOTime: " << now.toString(Qt::DateFormat::ISODate);
    qInfo() << "RFC2822Time: " << now.toString(Qt::DateFormat::RFC2822Date);
    qInfo() << "TextTime: " << now.toString(Qt::DateFormat::TextDate);

    QDateTime current = QDateTime::currentDateTime();
    qInfo() << "ISODateTime: " << current.toString(Qt::DateFormat::ISODate);
    qInfo() << "RFC2822DateTime: " << current.toString(Qt::DateFormat::RFC2822Date);
    qInfo() << "TextDateTime: " << current.toString(Qt::DateFormat::TextDate);

    qInfo() << current;
    QDateTime expire = current.addDays(45);
    qInfo() << expire;
    qInfo() << "Days to expire: " << current.daysTo(expire);

    if (current > expire)
    {
        qInfo() << "Expired!";
    } else
    {
        qInfo() << "Not expired!";
    }


    return a.exec();
}
