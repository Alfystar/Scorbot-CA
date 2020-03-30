/********************************************************************************
** Form generated from reading UI file 'freeMoveWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREEMOVEWINDOW_H
#define UI_FREEMOVEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FreeMoveWindow
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *minus;
    QPushButton *mn1;
    QPushButton *mn2;
    QPushButton *mn3;
    QPushButton *mn4;
    QPushButton *mn5;
    QPushButton *mn6;
    QVBoxLayout *verticalLayout_2;
    QLabel *Step1_direct;
    QLabel *Step2_direct;
    QLabel *Step3_direct;
    QLabel *Step4_direct;
    QLabel *Step5_direct;
    QLabel *Step6_direct;
    QVBoxLayout *plus;
    QPushButton *mp1;
    QPushButton *mp2;
    QPushButton *mp3;
    QPushButton *mp4;
    QPushButton *mp5;
    QPushButton *mp6;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;
    QSlider *pwmSpeed;
    QLCDNumber *lcdNumber;
    QButtonGroup *freeMovePushGroup;

    void setupUi(QDialog *FreeMoveWindow)
    {
        if (FreeMoveWindow->objectName().isEmpty())
            FreeMoveWindow->setObjectName(QString::fromUtf8("FreeMoveWindow"));
        FreeMoveWindow->resize(267, 268);
        layoutWidget = new QWidget(FreeMoveWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 141, 250));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        minus = new QVBoxLayout();
        minus->setObjectName(QString::fromUtf8("minus"));
        minus->setSizeConstraint(QLayout::SetMinimumSize);
        mn1 = new QPushButton(layoutWidget);
        freeMovePushGroup = new QButtonGroup(FreeMoveWindow);
        freeMovePushGroup->setObjectName(QString::fromUtf8("freeMovePushGroup"));
        freeMovePushGroup->addButton(mn1);
        mn1->setObjectName(QString::fromUtf8("mn1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mn1->sizePolicy().hasHeightForWidth());
        mn1->setSizePolicy(sizePolicy);
        mn1->setCheckable(false);
        mn1->setAutoExclusive(true);

        minus->addWidget(mn1);

        mn2 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mn2);
        mn2->setObjectName(QString::fromUtf8("mn2"));
        sizePolicy.setHeightForWidth(mn2->sizePolicy().hasHeightForWidth());
        mn2->setSizePolicy(sizePolicy);
        mn2->setCheckable(false);
        mn2->setAutoExclusive(true);

        minus->addWidget(mn2);

        mn3 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mn3);
        mn3->setObjectName(QString::fromUtf8("mn3"));
        sizePolicy.setHeightForWidth(mn3->sizePolicy().hasHeightForWidth());
        mn3->setSizePolicy(sizePolicy);
        mn3->setCheckable(false);
        mn3->setAutoExclusive(true);

        minus->addWidget(mn3);

        mn4 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mn4);
        mn4->setObjectName(QString::fromUtf8("mn4"));
        sizePolicy.setHeightForWidth(mn4->sizePolicy().hasHeightForWidth());
        mn4->setSizePolicy(sizePolicy);
        mn4->setCheckable(false);
        mn4->setAutoExclusive(true);

        minus->addWidget(mn4);

        mn5 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mn5);
        mn5->setObjectName(QString::fromUtf8("mn5"));
        sizePolicy.setHeightForWidth(mn5->sizePolicy().hasHeightForWidth());
        mn5->setSizePolicy(sizePolicy);
        mn5->setCheckable(false);
        mn5->setAutoExclusive(true);

        minus->addWidget(mn5);

        mn6 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mn6);
        mn6->setObjectName(QString::fromUtf8("mn6"));
        sizePolicy.setHeightForWidth(mn6->sizePolicy().hasHeightForWidth());
        mn6->setSizePolicy(sizePolicy);
        mn6->setCheckable(false);
        mn6->setAutoExclusive(true);

        minus->addWidget(mn6);


        horizontalLayout->addLayout(minus);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        Step1_direct = new QLabel(layoutWidget);
        Step1_direct->setObjectName(QString::fromUtf8("Step1_direct"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Step1_direct->sizePolicy().hasHeightForWidth());
        Step1_direct->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(10);
        Step1_direct->setFont(font);
        Step1_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step1_direct);

        Step2_direct = new QLabel(layoutWidget);
        Step2_direct->setObjectName(QString::fromUtf8("Step2_direct"));
        sizePolicy1.setHeightForWidth(Step2_direct->sizePolicy().hasHeightForWidth());
        Step2_direct->setSizePolicy(sizePolicy1);
        Step2_direct->setFont(font);
        Step2_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step2_direct);

        Step3_direct = new QLabel(layoutWidget);
        Step3_direct->setObjectName(QString::fromUtf8("Step3_direct"));
        sizePolicy1.setHeightForWidth(Step3_direct->sizePolicy().hasHeightForWidth());
        Step3_direct->setSizePolicy(sizePolicy1);
        Step3_direct->setFont(font);
        Step3_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step3_direct);

        Step4_direct = new QLabel(layoutWidget);
        Step4_direct->setObjectName(QString::fromUtf8("Step4_direct"));
        sizePolicy1.setHeightForWidth(Step4_direct->sizePolicy().hasHeightForWidth());
        Step4_direct->setSizePolicy(sizePolicy1);
        Step4_direct->setFont(font);
        Step4_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step4_direct);

        Step5_direct = new QLabel(layoutWidget);
        Step5_direct->setObjectName(QString::fromUtf8("Step5_direct"));
        sizePolicy1.setHeightForWidth(Step5_direct->sizePolicy().hasHeightForWidth());
        Step5_direct->setSizePolicy(sizePolicy1);
        Step5_direct->setFont(font);
        Step5_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step5_direct);

        Step6_direct = new QLabel(layoutWidget);
        Step6_direct->setObjectName(QString::fromUtf8("Step6_direct"));
        sizePolicy1.setHeightForWidth(Step6_direct->sizePolicy().hasHeightForWidth());
        Step6_direct->setSizePolicy(sizePolicy1);
        Step6_direct->setFont(font);
        Step6_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step6_direct);


        horizontalLayout->addLayout(verticalLayout_2);

        plus = new QVBoxLayout();
        plus->setObjectName(QString::fromUtf8("plus"));
        plus->setSizeConstraint(QLayout::SetMinimumSize);
        mp1 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mp1);
        mp1->setObjectName(QString::fromUtf8("mp1"));
        sizePolicy.setHeightForWidth(mp1->sizePolicy().hasHeightForWidth());
        mp1->setSizePolicy(sizePolicy);
        mp1->setCheckable(false);
        mp1->setAutoExclusive(true);

        plus->addWidget(mp1);

        mp2 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mp2);
        mp2->setObjectName(QString::fromUtf8("mp2"));
        sizePolicy.setHeightForWidth(mp2->sizePolicy().hasHeightForWidth());
        mp2->setSizePolicy(sizePolicy);
        mp2->setCheckable(false);
        mp2->setAutoExclusive(true);

        plus->addWidget(mp2);

        mp3 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mp3);
        mp3->setObjectName(QString::fromUtf8("mp3"));
        sizePolicy.setHeightForWidth(mp3->sizePolicy().hasHeightForWidth());
        mp3->setSizePolicy(sizePolicy);
        mp3->setCheckable(false);
        mp3->setAutoRepeat(false);
        mp3->setAutoExclusive(true);

        plus->addWidget(mp3);

        mp4 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mp4);
        mp4->setObjectName(QString::fromUtf8("mp4"));
        sizePolicy.setHeightForWidth(mp4->sizePolicy().hasHeightForWidth());
        mp4->setSizePolicy(sizePolicy);
        mp4->setCheckable(false);
        mp4->setAutoRepeat(false);
        mp4->setAutoExclusive(true);

        plus->addWidget(mp4);

        mp5 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mp5);
        mp5->setObjectName(QString::fromUtf8("mp5"));
        sizePolicy.setHeightForWidth(mp5->sizePolicy().hasHeightForWidth());
        mp5->setSizePolicy(sizePolicy);
        mp5->setCheckable(false);
        mp5->setAutoRepeat(false);
        mp5->setAutoExclusive(true);

        plus->addWidget(mp5);

        mp6 = new QPushButton(layoutWidget);
        freeMovePushGroup->addButton(mp6);
        mp6->setObjectName(QString::fromUtf8("mp6"));
        sizePolicy.setHeightForWidth(mp6->sizePolicy().hasHeightForWidth());
        mp6->setSizePolicy(sizePolicy);
        mp6->setCheckable(false);
        mp6->setAutoRepeat(false);

        plus->addWidget(mp6);


        horizontalLayout->addLayout(plus);

        widget = new QWidget(FreeMoveWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(171, 10, 91, 251));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy2);
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        pwmSpeed = new QSlider(widget);
        pwmSpeed->setObjectName(QString::fromUtf8("pwmSpeed"));
        pwmSpeed->setMaximumSize(QSize(500, 171));
        pwmSpeed->setMouseTracking(true);
        pwmSpeed->setAutoFillBackground(true);
        pwmSpeed->setMaximum(255);
        pwmSpeed->setSingleStep(5);
        pwmSpeed->setPageStep(50);
        pwmSpeed->setValue(120);
        pwmSpeed->setOrientation(Qt::Vertical);
        pwmSpeed->setTickPosition(QSlider::NoTicks);
        pwmSpeed->setTickInterval(0);

        verticalLayout->addWidget(pwmSpeed);

        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        lcdNumber->setFrameShape(QFrame::Box);
        lcdNumber->setFrameShadow(QFrame::Raised);
        lcdNumber->setLineWidth(2);
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setDigitCount(3);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber->setProperty("intValue", QVariant(120));

        verticalLayout->addWidget(lcdNumber);


        retranslateUi(FreeMoveWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), FreeMoveWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FreeMoveWindow, SLOT(reject()));
        QObject::connect(pwmSpeed, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));

        QMetaObject::connectSlotsByName(FreeMoveWindow);
    } // setupUi

    void retranslateUi(QDialog *FreeMoveWindow)
    {
        FreeMoveWindow->setWindowTitle(QCoreApplication::translate("FreeMoveWindow", "Free Moving", nullptr));
        mn1->setText(QCoreApplication::translate("FreeMoveWindow", "-", nullptr));
        mn2->setText(QCoreApplication::translate("FreeMoveWindow", "-", nullptr));
        mn3->setText(QCoreApplication::translate("FreeMoveWindow", "-", nullptr));
        mn4->setText(QCoreApplication::translate("FreeMoveWindow", "-", nullptr));
        mn5->setText(QCoreApplication::translate("FreeMoveWindow", "-", nullptr));
        mn6->setText(QCoreApplication::translate("FreeMoveWindow", "-", nullptr));
        Step1_direct->setText(QCoreApplication::translate("FreeMoveWindow", "Mot1", nullptr));
        Step2_direct->setText(QCoreApplication::translate("FreeMoveWindow", "Mot2", nullptr));
        Step3_direct->setText(QCoreApplication::translate("FreeMoveWindow", "Mot3", nullptr));
        Step4_direct->setText(QCoreApplication::translate("FreeMoveWindow", "Mot4", nullptr));
        Step5_direct->setText(QCoreApplication::translate("FreeMoveWindow", "Mot5", nullptr));
        Step6_direct->setText(QCoreApplication::translate("FreeMoveWindow", "Mot6", nullptr));
        mp1->setText(QCoreApplication::translate("FreeMoveWindow", "+", nullptr));
        mp2->setText(QCoreApplication::translate("FreeMoveWindow", "+", nullptr));
        mp3->setText(QCoreApplication::translate("FreeMoveWindow", "+", nullptr));
        mp4->setText(QCoreApplication::translate("FreeMoveWindow", "+", nullptr));
        mp5->setText(QCoreApplication::translate("FreeMoveWindow", "+", nullptr));
        mp6->setText(QCoreApplication::translate("FreeMoveWindow", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FreeMoveWindow: public Ui_FreeMoveWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREEMOVEWINDOW_H
