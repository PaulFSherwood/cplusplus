#include "receiver.h"
#include "ui_Receiver.h"

Receiver::Receiver(QWidget *parent) :
    QWidget(parent),
    ui(new Receiver)
{
    ui->setupUi(this);
}

Receiver::~Receiver()
{
    delete ui;
}

void Receiver::show_window()
{
    show();
}
