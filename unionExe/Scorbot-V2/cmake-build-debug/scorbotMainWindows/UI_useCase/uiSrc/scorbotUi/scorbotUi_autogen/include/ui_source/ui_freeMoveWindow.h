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
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FreeMoveWindow
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *minus;
    QToolButton *mn1;
    QToolButton *mn2;
    QToolButton *mn3;
    QToolButton *mn4;
    QToolButton *mn5;
    QToolButton *mn6;
    QVBoxLayout *verticalLayout_2;
    QLabel *Step1_direct;
    QLabel *Step2_direct;
    QLabel *Step3_direct;
    QLabel *Step4_direct;
    QLabel *Step5_direct;
    QLabel *Step6_direct;
    QVBoxLayout *plus;
    QToolButton *mp1;
    QToolButton *mp2;
    QToolButton *mp3;
    QToolButton *mp4;
    QToolButton *mp5;
    QToolButton *mp6;

    void setupUi(QDialog *FreeMoveWindow)
    {
        if (FreeMoveWindow->objectName().isEmpty())
            FreeMoveWindow->setObjectName(QString::fromUtf8("FreeMoveWindow"));
        FreeMoveWindow->resize(272, 268);
        buttonBox = new QDialogButtonBox(FreeMoveWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(180, 10, 75, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(FreeMoveWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 151, 250));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        minus = new QVBoxLayout();
        minus->setObjectName(QString::fromUtf8("minus"));
        minus->setSizeConstraint(QLayout::SetMinimumSize);
        mn1 = new QToolButton(layoutWidget);
        mn1->setObjectName(QString::fromUtf8("mn1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mn1->sizePolicy().hasHeightForWidth());
        mn1->setSizePolicy(sizePolicy);

        minus->addWidget(mn1);

        mn2 = new QToolButton(layoutWidget);
        mn2->setObjectName(QString::fromUtf8("mn2"));
        sizePolicy.setHeightForWidth(mn2->sizePolicy().hasHeightForWidth());
        mn2->setSizePolicy(sizePolicy);

        minus->addWidget(mn2);

        mn3 = new QToolButton(layoutWidget);
        mn3->setObjectName(QString::fromUtf8("mn3"));
        sizePolicy.setHeightForWidth(mn3->sizePolicy().hasHeightForWidth());
        mn3->setSizePolicy(sizePolicy);

        minus->addWidget(mn3);

        mn4 = new QToolButton(layoutWidget);
        mn4->setObjectName(QString::fromUtf8("mn4"));
        sizePolicy.setHeightForWidth(mn4->sizePolicy().hasHeightForWidth());
        mn4->setSizePolicy(sizePolicy);

        minus->addWidget(mn4);

        mn5 = new QToolButton(layoutWidget);
        mn5->setObjectName(QString::fromUtf8("mn5"));
        sizePolicy.setHeightForWidth(mn5->sizePolicy().hasHeightForWidth());
        mn5->setSizePolicy(sizePolicy);

        minus->addWidget(mn5);

        mn6 = new QToolButton(layoutWidget);
        mn6->setObjectName(QString::fromUtf8("mn6"));
        sizePolicy.setHeightForWidth(mn6->sizePolicy().hasHeightForWidth());
        mn6->setSizePolicy(sizePolicy);

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
        mp1 = new QToolButton(layoutWidget);
        mp1->setObjectName(QString::fromUtf8("mp1"));
        sizePolicy.setHeightForWidth(mp1->sizePolicy().hasHeightForWidth());
        mp1->setSizePolicy(sizePolicy);

        plus->addWidget(mp1);

        mp2 = new QToolButton(layoutWidget);
        mp2->setObjectName(QString::fromUtf8("mp2"));
        sizePolicy.setHeightForWidth(mp2->sizePolicy().hasHeightForWidth());
        mp2->setSizePolicy(sizePolicy);

        plus->addWidget(mp2);

        mp3 = new QToolButton(layoutWidget);
        mp3->setObjectName(QString::fromUtf8("mp3"));
        sizePolicy.setHeightForWidth(mp3->sizePolicy().hasHeightForWidth());
        mp3->setSizePolicy(sizePolicy);

        plus->addWidget(mp3);

        mp4 = new QToolButton(layoutWidget);
        mp4->setObjectName(QString::fromUtf8("mp4"));
        sizePolicy.setHeightForWidth(mp4->sizePolicy().hasHeightForWidth());
        mp4->setSizePolicy(sizePolicy);

        plus->addWidget(mp4);

        mp5 = new QToolButton(layoutWidget);
        mp5->setObjectName(QString::fromUtf8("mp5"));
        sizePolicy.setHeightForWidth(mp5->sizePolicy().hasHeightForWidth());
        mp5->setSizePolicy(sizePolicy);

        plus->addWidget(mp5);

        mp6 = new QToolButton(layoutWidget);
        mp6->setObjectName(QString::fromUtf8("mp6"));
        sizePolicy.setHeightForWidth(mp6->sizePolicy().hasHeightForWidth());
        mp6->setSizePolicy(sizePolicy);

        plus->addWidget(mp6);


        horizontalLayout->addLayout(plus);


        retranslateUi(FreeMoveWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), FreeMoveWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FreeMoveWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(FreeMoveWindow);
    } // setupUi

    void retranslateUi(QDialog *FreeMoveWindow)
    {
        FreeMoveWindow->setWindowTitle(QCoreApplication::translate("FreeMoveWindow", "Dialog", nullptr));
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
