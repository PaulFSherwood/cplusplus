#ifndef SENDER_H
#define SENDER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Sender; }
QT_END_NAMESPACE

class Sender : public QMainWindow
{
    Q_OBJECT

public:
    Sender(QWidget *parent = nullptr);
    ~Sender();

private:
    Ui::Sender *ui;
};
#endif // SENDER_H
