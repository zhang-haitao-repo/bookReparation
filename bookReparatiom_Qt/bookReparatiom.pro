#-------------------------------------------------
#
# Project created by QtCreator 2021-05-26T06:06:05
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bookReparatiom
TEMPLATE = app


SOURCES += main.cpp\
    setserial.cpp \
        widget.cpp \
    mypushbutton.cpp

HEADERS  += widget.h \
    mypushbutton.h \
    setserial.h

FORMS    += widget.ui \
    setserial.ui
