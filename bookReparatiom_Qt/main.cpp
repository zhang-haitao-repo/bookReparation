#include "widget.h"
#include "setserial.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 创建Qt应用程序对象
    QApplication a(argc, argv);
//    Widget w;
//    w.show();
    setSerial s;
    s.show();

    return a.exec();
}
