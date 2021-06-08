#ifndef SETSERIAL_H
#define SETSERIAL_H

#include <QWidget>
#include <QtSerialPort>

namespace Ui {
class setSerial;
}

class setSerial : public QWidget
{
    Q_OBJECT

public:
    explicit setSerial(QWidget *parent = nullptr);

    ~setSerial();

private slots:

    void Sleep(int msec);

    void serialPortReadyRead_Slot();

    void on_openBt_clicked();

    void on_close_Bt_clicked();

    void on_end_Bt_clicked();

    void on_begin_Bt_clicked();

    void on_sendSym_Bt_clicked();

private:
    Ui::setSerial *ui;
};

#endif // SETSERIAL_H
