/********************************************************************************
** Form generated from reading UI file 'setserial.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSERIAL_H
#define UI_SETSERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setSerial
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_9;
    QTextEdit *recvEdit;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QComboBox *checkCb;
    QComboBox *serialCb;
    QLabel *label_2;
    QComboBox *baundCb;
    QLabel *label_4;
    QComboBox *stopCb;
    QLabel *label_3;
    QComboBox *dataCb;
    QLabel *label_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *close_Bt;
    QPushButton *openBt;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *sendSym_Bt;
    QLineEdit *sendEdit;
    QSpacerItem *verticalSpacer_5;
    QPushButton *end_Bt;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QPushButton *begin_Bt;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *stop_Bt;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *setSerial)
    {
        if (setSerial->objectName().isEmpty())
            setSerial->setObjectName(QString::fromUtf8("setSerial"));
        setSerial->resize(800, 480);
        gridLayout_2 = new QGridLayout(setSerial);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(setSerial);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(773, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_9, 1, 0, 1, 1);

        recvEdit = new QTextEdit(setSerial);
        recvEdit->setObjectName(QString::fromUtf8("recvEdit"));
        recvEdit->setReadOnly(true);

        gridLayout_2->addWidget(recvEdit, 2, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(773, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkCb = new QComboBox(setSerial);
        checkCb->addItem(QString());
        checkCb->addItem(QString());
        checkCb->setObjectName(QString::fromUtf8("checkCb"));

        gridLayout->addWidget(checkCb, 4, 1, 1, 1);

        serialCb = new QComboBox(setSerial);
        serialCb->setObjectName(QString::fromUtf8("serialCb"));

        gridLayout->addWidget(serialCb, 0, 1, 1, 1);

        label_2 = new QLabel(setSerial);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        baundCb = new QComboBox(setSerial);
        baundCb->addItem(QString());
        baundCb->addItem(QString());
        baundCb->addItem(QString());
        baundCb->setObjectName(QString::fromUtf8("baundCb"));

        gridLayout->addWidget(baundCb, 2, 1, 1, 1);

        label_4 = new QLabel(setSerial);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        stopCb = new QComboBox(setSerial);
        stopCb->addItem(QString());
        stopCb->addItem(QString());
        stopCb->setObjectName(QString::fromUtf8("stopCb"));

        gridLayout->addWidget(stopCb, 5, 1, 1, 1);

        label_3 = new QLabel(setSerial);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        dataCb = new QComboBox(setSerial);
        dataCb->addItem(QString());
        dataCb->addItem(QString());
        dataCb->addItem(QString());
        dataCb->setObjectName(QString::fromUtf8("dataCb"));

        gridLayout->addWidget(dataCb, 3, 1, 1, 1);

        label_5 = new QLabel(setSerial);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label = new QLabel(setSerial);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        close_Bt = new QPushButton(setSerial);
        close_Bt->setObjectName(QString::fromUtf8("close_Bt"));

        horizontalLayout_2->addWidget(close_Bt);

        openBt = new QPushButton(setSerial);
        openBt->setObjectName(QString::fromUtf8("openBt"));

        horizontalLayout_2->addWidget(openBt);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sendSym_Bt = new QPushButton(setSerial);
        sendSym_Bt->setObjectName(QString::fromUtf8("sendSym_Bt"));

        horizontalLayout->addWidget(sendSym_Bt);

        sendEdit = new QLineEdit(setSerial);
        sendEdit->setObjectName(QString::fromUtf8("sendEdit"));
        sendEdit->setMinimumSize(QSize(200, 20));

        horizontalLayout->addWidget(sendEdit);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        end_Bt = new QPushButton(setSerial);
        end_Bt->setObjectName(QString::fromUtf8("end_Bt"));

        verticalLayout_4->addWidget(end_Bt);


        horizontalLayout_3->addLayout(verticalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        begin_Bt = new QPushButton(setSerial);
        begin_Bt->setObjectName(QString::fromUtf8("begin_Bt"));

        verticalLayout->addWidget(begin_Bt);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        pushButton = new QPushButton(setSerial);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        stop_Bt = new QPushButton(setSerial);
        stop_Bt->setObjectName(QString::fromUtf8("stop_Bt"));

        verticalLayout->addWidget(stop_Bt);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout_3, 4, 0, 1, 1);


        retranslateUi(setSerial);

        baundCb->setCurrentIndex(2);
        stopCb->setCurrentIndex(1);
        dataCb->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(setSerial);
    } // setupUi

    void retranslateUi(QWidget *setSerial)
    {
        setSerial->setWindowTitle(QApplication::translate("setSerial", "Form", nullptr));
        label_6->setText(QApplication::translate("setSerial", "\345\217\244\347\261\215\344\277\256\345\244\215\347\263\273\347\273\237\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        checkCb->setItemText(0, QApplication::translate("setSerial", "0", nullptr));
        checkCb->setItemText(1, QApplication::translate("setSerial", "1", nullptr));

        label_2->setText(QApplication::translate("setSerial", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        baundCb->setItemText(0, QApplication::translate("setSerial", "4800", nullptr));
        baundCb->setItemText(1, QApplication::translate("setSerial", "9600", nullptr));
        baundCb->setItemText(2, QApplication::translate("setSerial", "115200", nullptr));

        label_4->setText(QApplication::translate("setSerial", "\345\201\234\346\255\242\344\275\215\357\274\232", nullptr));
        stopCb->setItemText(0, QApplication::translate("setSerial", "0", nullptr));
        stopCb->setItemText(1, QApplication::translate("setSerial", "1", nullptr));

        label_3->setText(QApplication::translate("setSerial", "\346\240\241\351\252\214\344\275\215\357\274\232", nullptr));
        dataCb->setItemText(0, QApplication::translate("setSerial", "6", nullptr));
        dataCb->setItemText(1, QApplication::translate("setSerial", "7", nullptr));
        dataCb->setItemText(2, QApplication::translate("setSerial", "8", nullptr));

        label_5->setText(QApplication::translate("setSerial", "\346\225\260\346\215\256\344\275\215\357\274\232", nullptr));
        label->setText(QApplication::translate("setSerial", "\344\270\262\345\217\243\357\274\232", nullptr));
        close_Bt->setText(QApplication::translate("setSerial", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        openBt->setText(QApplication::translate("setSerial", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        sendSym_Bt->setText(QApplication::translate("setSerial", "\345\217\221\351\200\201", nullptr));
        end_Bt->setText(QApplication::translate("setSerial", "\351\200\200\345\207\272", nullptr));
        begin_Bt->setText(QApplication::translate("setSerial", "\350\257\273\345\217\226\346\226\207\344\273\266", nullptr));
        pushButton->setText(QApplication::translate("setSerial", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        stop_Bt->setText(QApplication::translate("setSerial", "\346\232\202\345\201\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setSerial: public Ui_setSerial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSERIAL_H
