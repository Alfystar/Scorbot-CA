/********************************************************************************
** Form generated from reading UI file 'freeMoveWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREEMOVEWINDOW_H
#define UI_FREEMOVEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            FreeMoveWindow->setObjectName(QStringLiteral("FreeMoveWindow"));
        FreeMoveWindow->resize(272, 202);
        buttonBox = new QDialogButtonBox(FreeMoveWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(180, 10, 75, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(FreeMoveWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 121, 190));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        minus = new QVBoxLayout();
        minus->setObjectName(QStringLiteral("minus"));
        minus->setSizeConstraint(QLayout::SetMinimumSize);
        mn1 = new QToolButton(layoutWidget);
        mn1->setObjectName(QStringLiteral("mn1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mn1->sizePolicy().hasHeightForWidth());
        mn1->setSizePolicy(sizePolicy);

        minus->addWidget(mn1);

        mn2 = new QToolButton(layoutWidget);
        mn2->setObjectName(QStringLiteral("mn2"));
        sizePolicy.setHeightForWidth(mn2->sizePolicy().hasHeightForWidth());
        mn2->setSizePolicy(sizePolicy);

        minus->addWidget(mn2);

        mn3 = new QToolButton(layoutWidget);
        mn3->setObjectName(QStringLiteral("mn3"));
        sizePolicy.setHeightForWidth(mn3->sizePolicy().hasHeightForWidth());
        mn3->setSizePolicy(sizePolicy);

        minus->addWidget(mn3);

        mn4 = new QToolButton(layoutWidget);
        mn4->setObjectName(QStringLiteral("mn4"));
        sizePolicy.setHeightForWidth(mn4->sizePolicy().hasHeightForWidth());
        mn4->setSizePolicy(sizePolicy);

        minus->addWidget(mn4);

        mn5 = new QToolButton(layoutWidget);
        mn5->setObjectName(QStringLiteral("mn5"));
        sizePolicy.setHeightForWidth(mn5->sizePolicy().hasHeightForWidth());
        mn5->setSizePolicy(sizePolicy);

        minus->addWidget(mn5);

        mn6 = new QToolButton(layoutWidget);
        mn6->setObjectName(QStringLiteral("mn6"));
        sizePolicy.setHeightForWidth(mn6->sizePolicy().hasHeightForWidth());
        mn6->setSizePolicy(sizePolicy);

        minus->addWidget(mn6);


        horizontalLayout->addLayout(minus);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        Step1_direct = new QLabel(layoutWidget);
        Step1_direct->setObjectName(QStringLiteral("Step1_direct"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
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
        Step2_direct->setObjectName(QStringLiteral("Step2_direct"));
        sizePolicy1.setHeightForWidth(Step2_direct->sizePolicy().hasHeightForWidth());
        Step2_direct->setSizePolicy(sizePolicy1);
        Step2_direct->setFont(font);
        Step2_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step2_direct);

        Step3_direct = new QLabel(layoutWidget);
        Step3_direct->setObjectName(QStringLiteral("Step3_direct"));
        sizePolicy1.setHeightForWidth(Step3_direct->sizePolicy().hasHeightForWidth());
        Step3_direct->setSizePolicy(sizePolicy1);
        Step3_direct->setFont(font);
        Step3_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step3_direct);

        Step4_direct = new QLabel(layoutWidget);
        Step4_direct->setObjectName(QStringLiteral("Step4_direct"));
        sizePolicy1.setHeightForWidth(Step4_direct->sizePolicy().hasHeightForWidth());
        Step4_direct->setSizePolicy(sizePolicy1);
        Step4_direct->setFont(font);
        Step4_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step4_direct);

        Step5_direct = new QLabel(layoutWidget);
        Step5_direct->setObjectName(QStringLiteral("Step5_direct"));
        sizePolicy1.setHeightForWidth(Step5_direct->sizePolicy().hasHeightForWidth());
        Step5_direct->setSizePolicy(sizePolicy1);
        Step5_direct->setFont(font);
        Step5_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step5_direct);

        Step6_direct = new QLabel(layoutWidget);
        Step6_direct->setObjectName(QStringLiteral("Step6_direct"));
        sizePolicy1.setHeightForWidth(Step6_direct->sizePolicy().hasHeightForWidth());
        Step6_direct->setSizePolicy(sizePolicy1);
        Step6_direct->setFont(font);
        Step6_direct->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Step6_direct);


        horizontalLayout->addLayout(verticalLayout_2);

        plus = new QVBoxLayout();
        plus->setObjectName(QStringLiteral("plus"));
        plus->setSizeConstraint(QLayout::SetMinimumSize);
        mp1 = new QToolButton(layoutWidget);
        mp1->setObjectName(QStringLiteral("mp1"));
        sizePolicy.setHeightForWidth(mp1->sizePolicy().hasHeightForWidth());
        mp1->setSizePolicy(sizePolicy);

        plus->addWidget(mp1);

        mp2 = new QToolButton(layoutWidget);
        mp2->setObjectName(QStringLiteral("mp2"));
        sizePolicy.setHeightForWidth(mp2->sizePolicy().hasHeightForWidth());
        mp2->setSizePolicy(sizePolicy);

        plus->addWidget(mp2);

        mp3 = new QToolButton(layoutWidget);
        mp3->setObjectName(QStringLiteral("mp3"));
        sizePolicy.setHeightForWidth(mp3->sizePolicy().hasHeightForWidth());
        mp3->setSizePolicy(sizePolicy);

        plus->addWidget(mp3);

        mp4 = new QToolButton(layoutWidget);
        mp4->setObjectName(QStringLiteral("mp4"));
        sizePolicy.setHeightForWidth(mp4->sizePolicy().hasHeightForWidth());
        mp4->setSizePolicy(sizePolicy);

        plus->addWidget(mp4);

        mp5 = new QToolButton(layoutWidget);
        mp5->setObjectName(QStringLiteral("mp5"));
        sizePolicy.setHeightForWidth(mp5->sizePolicy().hasHeightForWidth());
        mp5->setSizePolicy(sizePolicy);

        plus->addWidget(mp5);

        mp6 = new QToolButton(layoutWidget);
        mp6->setObjectName(QStringLiteral("mp6"));
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
        FreeMoveWindow->setWindowTitle(QApplication::translate("FreeMoveWindow", "Dialog", Q_NULLPTR));
        mn1->setText(QApplication::translate("FreeMoveWindow", "-", Q_NULLPTR));
        mn2->setText(QApplication::translate("FreeMoveWindow", "-", Q_NULLPTR));
        mn3->setText(QApplication::translate("FreeMoveWindow", "-", Q_NULLPTR));
        mn4->setText(QApplication::translate("FreeMoveWindow", "-", Q_NULLPTR));
        mn5->setText(QApplication::translate("FreeMoveWindow", "-", Q_NULLPTR));
        mn6->setText(QApplication::translate("FreeMoveWindow", "-", Q_NULLPTR));
        Step1_direct->setText(QApplication::translate("FreeMoveWindow", "Mot1", Q_NULLPTR));
        Step2_direct->setText(QApplication::translate("FreeMoveWindow", "Mot2", Q_NULLPTR));
        Step3_direct->setText(QApplication::translate("FreeMoveWindow", "Mot3", Q_NULLPTR));
        Step4_direct->setText(QApplication::translate("FreeMoveWindow", "Mot4", Q_NULLPTR));
        Step5_direct->setText(QApplication::translate("FreeMoveWindow", "Mot5", Q_NULLPTR));
        Step6_direct->setText(QApplication::translate("FreeMoveWindow", "Mot6", Q_NULLPTR));
        mp1->setText(QApplication::translate("FreeMoveWindow", "+", Q_NULLPTR));
        mp2->setText(QApplication::translate("FreeMoveWindow", "+", Q_NULLPTR));
        mp3->setText(QApplication::translate("FreeMoveWindow", "+", Q_NULLPTR));
        mp4->setText(QApplication::translate("FreeMoveWindow", "+", Q_NULLPTR));
        mp5->setText(QApplication::translate("FreeMoveWindow", "+", Q_NULLPTR));
        mp6->setText(QApplication::translate("FreeMoveWindow", "+", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FreeMoveWindow: public Ui_FreeMoveWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREEMOVEWINDOW_H
