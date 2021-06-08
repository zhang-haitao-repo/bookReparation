#include "widget.h"
#include "ui_widget.h"
#include "setserial.h"
#include <QApplication>
#include <QLabel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(800, 480);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    setSerial* serialUi = new setSerial;

    serialUi->show();
}
