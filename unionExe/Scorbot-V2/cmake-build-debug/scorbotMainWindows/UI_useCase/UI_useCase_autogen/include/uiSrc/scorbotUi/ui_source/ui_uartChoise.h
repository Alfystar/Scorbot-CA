/********************************************************************************
** Form generated from reading UI file 'uartChoise.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UARTCHOISE_H
#define UI_UARTCHOISE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
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

    void setupUi(QWidget *UartChoise)
    {
        if (UartChoise->objectName().isEmpty())
            UartChoise->setObjectName(QStringLiteral("UartChoise"));
        UartChoise->resize(320, 240);
        buttonBox = new QDialogButtonBox(UartChoise);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(140, 200, 160, 26));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(UartChoise);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 301, 86));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        speedChose = new QComboBox(layoutWidget);
        speedChose->setObjectName(QStringLiteral("speedChose"));
        speedChose->setEditable(false);

        gridLayout->addWidget(speedChose, 2, 1, 1, 1);

        serial_find = new QPushButton(layoutWidget);
        serial_find->setObjectName(QStringLiteral("serial_find"));

        gridLayout->addWidget(serial_find, 0, 0, 1, 1);

        uartFind = new QComboBox(layoutWidget);
        uartFind->setObjectName(QStringLiteral("uartFind"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uartFind->sizePolicy().hasHeightForWidth());
        uartFind->setSizePolicy(sizePolicy);

        gridLayout->addWidget(uartFind, 0, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);


        retranslateUi(UartChoise);
        QObject::connect(buttonBox, SIGNAL(rejected()), UartChoise, SLOT(hide()));

        speedChose->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(UartChoise);
    } // setupUi

    void retranslateUi(QWidget *UartChoise)
    {
        UartChoise->setWindowTitle(QApplication::translate("UartChoise", "Form", Q_NULLPTR));
        speedChose->clear();
        speedChose->insertItems(0, QStringList()
         << QApplication::translate("UartChoise", "B9600", Q_NULLPTR)
         << QApplication::translate("UartChoise", "B57600", Q_NULLPTR)
         << QApplication::translate("UartChoise", "B115200", Q_NULLPTR)
         << QApplication::translate("UartChoise", "B921600", Q_NULLPTR)
        );
        serial_find->setText(QApplication::translate("UartChoise", "Serial find", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        uartFind->setWhatsThis(QApplication::translate("UartChoise", "<html><head/><body><p>Seleziona la Porta Seriale</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("UartChoise", "Uart Speed", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UartChoise: public Ui_UartChoise {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UARTCHOISE_H
