#include "sender.h"
#include "./ui_sender.h"
#include "receiver.h"

Sender::Sender(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sender)
{
    ui->setupUi(this);
    Receiver *receiver = new Receiver;
    QObject::connect(ui->pushButton, &QPushButton::clicked, &Receiver::show_window);
}

Sender::~Sender()
{
    delete ui;
}

