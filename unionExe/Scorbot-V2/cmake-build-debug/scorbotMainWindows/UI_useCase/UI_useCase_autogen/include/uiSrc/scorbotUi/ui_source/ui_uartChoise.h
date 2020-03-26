/********************************************************************************
** Form generated from reading UI file 'uartChoise.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UARTCHOISE_H
#define UI_UARTCHOISE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UartChoise
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QComboBox *speedChose;
    QPushButton *serial_find;
    QComboBox *uartFind;
    QLabel *label;

    void setupUi(QWidget *UartChoise) {
        if (UartChoise->objectName().isEmpty())
            UartChoise->setObjectName(QString::fromUtf8("UartChoise"));
        UartChoise->resize(320, 139);
        buttonBox = new QDialogButtonBox(UartChoise);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(140, 110, 160, 26));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
        layoutWidget = new QWidget(UartChoise);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 301, 86));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        speedChose = new QComboBox(layoutWidget);
        speedChose->addItem(QString());
        speedChose->addItem(QString());
        speedChose->addItem(QString());
        speedChose->addItem(QString());
        speedChose->setObjectName(QString::fromUtf8("speedChose"));
        speedChose->setEditable(false);

        gridLayout->addWidget(speedChose, 2, 1, 1, 1);

        serial_find = new QPushButton(layoutWidget);
        serial_find->setObjectName(QString::fromUtf8("serial_find"));

        gridLayout->addWidget(serial_find, 0, 0, 1, 1);

        uartFind = new QComboBox(layoutWidget);
        uartFind->setObjectName(QString::fromUtf8("uartFind"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uartFind->sizePolicy().hasHeightForWidth());
        uartFind->setSizePolicy(sizePolicy);

        gridLayout->addWidget(uartFind, 0, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);


        retranslateUi(UartChoise);
        QObject::connect(buttonBox, SIGNAL(rejected()), UartChoise, SLOT(hide()));

        speedChose->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(UartChoise);
    } // setupUi

    void retranslateUi(QWidget *UartChoise) {
        UartChoise->setWindowTitle(QCoreApplication::translate("UartChoise", "Form", nullptr));
        speedChose->setItemText(0, QCoreApplication::translate("UartChoise", "B9600", nullptr));
        speedChose->setItemText(1, QCoreApplication::translate("UartChoise", "B57600", nullptr));
        speedChose->setItemText(2, QCoreApplication::translate("UartChoise", "B115200", nullptr));
        speedChose->setItemText(3, QCoreApplication::translate("UartChoise", "B921600", nullptr));

        serial_find->setText(QCoreApplication::translate("UartChoise", "Serial find", nullptr));
#if QT_CONFIG(whatsthis)
        uartFind->setWhatsThis(QCoreApplication::translate("UartChoise", "<html><head/><body><p>Seleziona la Porta Seriale</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QCoreApplication::translate("UartChoise", "Uart Speed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UartChoise: public Ui_UartChoise {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UARTCHOISE_H
