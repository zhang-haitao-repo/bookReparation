#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>

MyPushButton::MyPushButton(QString normalImag, QString pressImage)
{
    this->normalImagPath = normalImag;
    this->stressImagePath = pressImage;

    QPixmap pix;
    bool ret = pix.load(this->normalImagPath);
    if(!ret){
        qDebug() << "picture load failue";
        return;
    }

    // 设定图片大小
    this->setFixedSize(pix.width(), pix.height());

    // 设置不规则图片样式
    this->setStyleSheet("QPushButton{boarder:0px;}");

    // 设置图片
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));

}

