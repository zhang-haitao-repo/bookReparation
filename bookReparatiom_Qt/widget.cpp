#include "widget.h"
#include "ui_widget.h"
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
