#include "setserial.h"
#include "ui_setserial.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>
#include <QString>

QSerialPort *serialPort;

setSerial::setSerial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setSerial)
{
    ui->setupUi(this);

    QStringList serialNamePort;

    serialPort = new QSerialPort(this);

    connect(serialPort,SIGNAL(readyRead()),this,SLOT(serialPortReadyRead_Slot()));

    foreach(const QSerialPortInfo &info ,QSerialPortInfo::availablePorts()){
        serialNamePort << info.portName();
    }

    ui->serialCb->addItems(serialNamePort);
}

setSerial::~setSerial()
{
    delete ui;
}

void setSerial::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void setSerial::on_openBt_clicked()
{
    QSerialPort::BaudRate baudRate = QSerialPort::Baud115200;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QSerialPort::Parity checkBits = QSerialPort::NoParity;

    if (ui->baundCb->currentText()=="4800"){
        baudRate = QSerialPort::Baud4800;
    }
    else if (ui->baundCb->currentText()=="9600") {
        baudRate = QSerialPort::Baud9600;
    }
    else if (ui->baundCb->currentText()=="115200") {
        baudRate = QSerialPort::Baud115200;
    }

    if (ui->dataCb->currentText()=="6"){
        dataBits = QSerialPort::Data6;
    }
    else if (ui->dataCb->currentText()=="7") {
        dataBits = QSerialPort::Data7;
    }
    else if (ui->dataCb->currentText()=="8") {
        dataBits = QSerialPort::Data8;
    }

    if (ui->stopCb->currentText()=="1"){
        stopBits = QSerialPort::OneStop;
    }

    if (ui->checkCb->currentText()=="0"){
        checkBits = QSerialPort::NoParity;
    }

    serialPort->setPortName(ui->serialCb->currentText());
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);
    serialPort->setParity(checkBits);

    if (serialPort->open(QIODevice::ReadWrite) == true){
        QMessageBox::information(this,"提示","成功");
    }
    else{
        QMessageBox::critical(this,"提示","失败");
    }
}

void setSerial::on_close_Bt_clicked()
{
    serialPort->close();
    QMessageBox::critical(this,"提示","关闭成功");
}

void setSerial::serialPortReadyRead_Slot()
{
    QString buf;
    buf = QString(serialPort->readAll());
    ui->recvEdit->append(buf);
}

void setSerial::on_end_Bt_clicked()
{
    qDebug("close set;");

    this->close();
}

void setSerial::on_begin_Bt_clicked()
{
    std::fstream ifs;
    std::string buf;
    ifs.open("./data661.txt", std::ios::in);
    if(!ifs.is_open())
        std::cout << "open error"<< std::endl;
    while(std::getline(ifs, buf)){
        QString recData = QString::fromStdString(buf);
        recData += "\r\n";
        ui->recvEdit->append(recData);
        serialPort->write(recData.toLocal8Bit().data());
        Sleep(30);
    }
}

void setSerial::on_sendSym_Bt_clicked()
{
    QString send_data;

    send_data = ui->sendEdit->text();

    send_data += "\r\n";

    serialPort->write(send_data.toLocal8Bit().data());
}
