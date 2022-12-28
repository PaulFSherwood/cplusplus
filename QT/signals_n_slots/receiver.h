#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>

namespace Ui {
class Receiver;
}

class Receiver : public QWidget
{
    Q_OBJECT

public:
    explicit Receiver(QWidget *parent = nullptr);
    ~Receiver();

public slots:
    void show_window();

private:
    Receiver *ui;
};

#endif // RECEIVER_H
