#include <QCoreApplication>
#include "source.h"
#include "destination.h"
#include "radio.h"
#include "station.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Source oSource;
    Destination oDestination;

    QObject::connect(&oSource, &Source::mySignal, &oDestination, &Destination::mySlot);

    // oSource.test();
    oDestination.mySlot("HaM");

    Radio boombox;
    Station* channels[3];

    // create some stations
    channels[0] = new Station(&boombox, 94, "Rock n Roll");
    channels[1] = new Station(&boombox, 87, "HipHop");
    channels[2] = new Station(&boombox, 104, "News");

    boombox.connect(&boombox, &Radio::quit, &a, &QCoreApplication::quit, Qt::QueuedConnection);

//    for (int i = 0; i < 3; i++)
//    {
//        Station* channel = channels[i];
//        boombox.connect(channel, &Station::send, &boombox, &Radio::listen);
//    }
    do
    {
        qInfo() << "Enter on, off, test, or quit";
        QTextStream qtin(stdin);
        QString line = qtin.readLine().trimmed().toUpper();

        //////////-- ON --//////////
        if (line == "ON")
        {
            qInfo() << "Turnig the radio on";
            for (int i = 0; i < 3; i++)
            {
                Station* channel = channels[i];
                boombox.connect(channel, &Station::send, &boombox, &Radio::listen);
            }
            qInfo() << "Radio is on";
        }
        //////////-- OFF --//////////
        if (line == "OFF")
        {
            qInfo() << "Turnig the radio off";
            for (int i = 0; i < 3; i++)
            {
                Station* channel = channels[i];
                boombox.disconnect(channel, &Station::send, &boombox, &Radio::listen);
            }
            qInfo() << "Radio is off";
        }
        //////////-- TEST --//////////
        if (line == "TEST")
        {
            qInfo() << "Testing";
            for (int i = 0; i < 3; i++)
            {
                Station* channel = channels[i];
                channel->broadcast("Broadcasting live");
            }
            qInfo() << "Testing Complete";
        }

        //////////-- QUIT --//////////
        if (line == "QUIT")
        {

            qInfo() << "Quiting";
            emit boombox.quit();
            break;

        }

    } while (true);

    return a.exec();
}
