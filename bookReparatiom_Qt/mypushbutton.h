#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalImag, QString pressImage = "");

signals:

public slots:

private:
    QString normalImagPath;
    QString stressImagePath;
};

#endif // MYPUSHBUTTON_H
