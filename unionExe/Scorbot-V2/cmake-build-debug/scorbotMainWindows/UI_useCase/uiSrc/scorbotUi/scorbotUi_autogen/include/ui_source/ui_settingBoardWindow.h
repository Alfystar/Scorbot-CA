/********************************************************************************
** Form generated from reading UI file 'settingBoardWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGBOARDWINDOW_H
#define UI_SETTINGBOARDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingBoardWindow
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *EnSelect;
    QWidget *layoutWidget1;
    QVBoxLayout *EnMin;
    QLabel *valMinScr_2;
    QFormLayout *formLayout_2;
    QLabel *en1Label_2;
    QSpinBox *en1Min;
    QLabel *en2Label_2;
    QSpinBox *en2Min;
    QLabel *en3Label_2;
    QSpinBox *en3Min;
    QLabel *en4Label_2;
    QSpinBox *en4Min;
    QLabel *en5Label_2;
    QSpinBox *en5Min;
    QLabel *en6Label_2;
    QSpinBox *en6Min;
    QWidget *layoutWidget2;
    QVBoxLayout *EnMax;
    QLabel *valMinScr;
    QFormLayout *formLayout;
    QLabel *en1Label;
    QLabel *en2Label;
    QSpinBox *en2Max;
    QLabel *en3Label;
    QSpinBox *en3Max;
    QLabel *en4Label;
    QSpinBox *en4Max;
    QLabel *en5Label;
    QSpinBox *en5Max;
    QLabel *en6Label;
    QSpinBox *en6Max;
    QSpinBox *en1Max;
    QWidget *layoutWidget3;
    QVBoxLayout *CurMax;
    QLabel *valMinScr_3;
    QFormLayout *formLayout_3;
    QLabel *en1Label_3;
    QLabel *en2Label_3;
    QLabel *en3Label_3;
    QLabel *en4Label_3;
    QLabel *en5Label_3;
    QLabel *en6Label_3;
    QDoubleSpinBox *curM1;
    QDoubleSpinBox *curM6;
    QDoubleSpinBox *curM5;
    QDoubleSpinBox *curM4;
    QDoubleSpinBox *curM3;
    QDoubleSpinBox *curM2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *adcVref;
    QLabel *label;
    QRadioButton *in1V1;
    QRadioButton *in2V56;
    QRadioButton *ext;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *adcOffset;
    QLabel *label_2;
    QComboBox *offsetChose;
    QVBoxLayout *MotorPwm;
    QLabel *label_3;
    QComboBox *motFreqChose;
    QVBoxLayout *verticalLayout_4;
    QPushButton *saveSetting;
    QPushButton *loadSetting;
    QPushButton *restoreSetting;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingBoardWindow)
    {
        if (SettingBoardWindow->objectName().isEmpty())
            SettingBoardWindow->setObjectName(QStringLiteral("SettingBoardWindow"));
        SettingBoardWindow->resize(505, 405);
        SettingBoardWindow->setSizeGripEnabled(false);
        SettingBoardWindow->setModal(false);
        layoutWidget = new QWidget(SettingBoardWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 481, 381));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        EnSelect = new QSplitter(layoutWidget);
        EnSelect->setObjectName(QStringLiteral("EnSelect"));
        EnSelect->setOrientation(Qt::Horizontal);
        EnSelect->setHandleWidth(12);
        layoutWidget1 = new QWidget(EnSelect);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        EnMin = new QVBoxLayout(layoutWidget1);
        EnMin->setSpacing(6);
        EnMin->setContentsMargins(9, 9, 9, 9);
        EnMin->setObjectName(QStringLiteral("EnMin"));
        EnMin->setContentsMargins(0, 0, 0, 0);
        valMinScr_2 = new QLabel(layoutWidget1);
        valMinScr_2->setObjectName(QStringLiteral("valMinScr_2"));
        QFont font;
        font.setPointSize(12);
        font.setStrikeOut(false);
        font.setKerning(true);
        valMinScr_2->setFont(font);
        valMinScr_2->setAlignment(Qt::AlignCenter);

        EnMin->addWidget(valMinScr_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setLabelAlignment(Qt::AlignCenter);
        formLayout_2->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        en1Label_2 = new QLabel(layoutWidget1);
        en1Label_2->setObjectName(QStringLiteral("en1Label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, en1Label_2);

        en1Min = new QSpinBox(layoutWidget1);
        en1Min->setObjectName(QStringLiteral("en1Min"));
        en1Min->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en1Min->setMinimum(-99999);
        en1Min->setMaximum(99999);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, en1Min);

        en2Label_2 = new QLabel(layoutWidget1);
        en2Label_2->setObjectName(QStringLiteral("en2Label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, en2Label_2);

        en2Min = new QSpinBox(layoutWidget1);
        en2Min->setObjectName(QStringLiteral("en2Min"));
        en2Min->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en2Min->setMinimum(-99999);
        en2Min->setMaximum(99999);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, en2Min);

        en3Label_2 = new QLabel(layoutWidget1);
        en3Label_2->setObjectName(QStringLiteral("en3Label_2"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, en3Label_2);

        en3Min = new QSpinBox(layoutWidget1);
        en3Min->setObjectName(QStringLiteral("en3Min"));
        en3Min->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en3Min->setMinimum(-99999);
        en3Min->setMaximum(99999);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, en3Min);

        en4Label_2 = new QLabel(layoutWidget1);
        en4Label_2->setObjectName(QStringLiteral("en4Label_2"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, en4Label_2);

        en4Min = new QSpinBox(layoutWidget1);
        en4Min->setObjectName(QStringLiteral("en4Min"));
        en4Min->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en4Min->setMinimum(-99999);
        en4Min->setMaximum(99999);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, en4Min);

        en5Label_2 = new QLabel(layoutWidget1);
        en5Label_2->setObjectName(QStringLiteral("en5Label_2"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, en5Label_2);

        en5Min = new QSpinBox(layoutWidget1);
        en5Min->setObjectName(QStringLiteral("en5Min"));
        en5Min->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en5Min->setMinimum(-99999);
        en5Min->setMaximum(99999);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, en5Min);

        en6Label_2 = new QLabel(layoutWidget1);
        en6Label_2->setObjectName(QStringLiteral("en6Label_2"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, en6Label_2);

        en6Min = new QSpinBox(layoutWidget1);
        en6Min->setObjectName(QStringLiteral("en6Min"));
        en6Min->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en6Min->setMinimum(-99999);
        en6Min->setMaximum(99999);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, en6Min);


        EnMin->addLayout(formLayout_2);

        EnSelect->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(EnSelect);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        EnMax = new QVBoxLayout(layoutWidget2);
        EnMax->setSpacing(6);
        EnMax->setContentsMargins(9, 9, 9, 9);
        EnMax->setObjectName(QStringLiteral("EnMax"));
        EnMax->setContentsMargins(0, 0, 0, 0);
        valMinScr = new QLabel(layoutWidget2);
        valMinScr->setObjectName(QStringLiteral("valMinScr"));
        valMinScr->setFont(font);
        valMinScr->setTextFormat(Qt::AutoText);
        valMinScr->setAlignment(Qt::AlignCenter);

        EnMax->addWidget(valMinScr);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignCenter);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        en1Label = new QLabel(layoutWidget2);
        en1Label->setObjectName(QStringLiteral("en1Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, en1Label);

        en2Label = new QLabel(layoutWidget2);
        en2Label->setObjectName(QStringLiteral("en2Label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, en2Label);

        en2Max = new QSpinBox(layoutWidget2);
        en2Max->setObjectName(QStringLiteral("en2Max"));
        en2Max->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en2Max->setMinimum(-99999);
        en2Max->setMaximum(99999);

        formLayout->setWidget(1, QFormLayout::FieldRole, en2Max);

        en3Label = new QLabel(layoutWidget2);
        en3Label->setObjectName(QStringLiteral("en3Label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, en3Label);

        en3Max = new QSpinBox(layoutWidget2);
        en3Max->setObjectName(QStringLiteral("en3Max"));
        en3Max->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en3Max->setMinimum(-99999);
        en3Max->setMaximum(99999);

        formLayout->setWidget(2, QFormLayout::FieldRole, en3Max);

        en4Label = new QLabel(layoutWidget2);
        en4Label->setObjectName(QStringLiteral("en4Label"));

        formLayout->setWidget(3, QFormLayout::LabelRole, en4Label);

        en4Max = new QSpinBox(layoutWidget2);
        en4Max->setObjectName(QStringLiteral("en4Max"));
        en4Max->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en4Max->setMinimum(-99999);
        en4Max->setMaximum(99999);

        formLayout->setWidget(3, QFormLayout::FieldRole, en4Max);

        en5Label = new QLabel(layoutWidget2);
        en5Label->setObjectName(QStringLiteral("en5Label"));

        formLayout->setWidget(4, QFormLayout::LabelRole, en5Label);

        en5Max = new QSpinBox(layoutWidget2);
        en5Max->setObjectName(QStringLiteral("en5Max"));
        en5Max->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en5Max->setMinimum(-99999);
        en5Max->setMaximum(99999);

        formLayout->setWidget(4, QFormLayout::FieldRole, en5Max);

        en6Label = new QLabel(layoutWidget2);
        en6Label->setObjectName(QStringLiteral("en6Label"));

        formLayout->setWidget(5, QFormLayout::LabelRole, en6Label);

        en6Max = new QSpinBox(layoutWidget2);
        en6Max->setObjectName(QStringLiteral("en6Max"));
        en6Max->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en6Max->setMinimum(-99999);
        en6Max->setMaximum(99999);

        formLayout->setWidget(5, QFormLayout::FieldRole, en6Max);

        en1Max = new QSpinBox(layoutWidget2);
        en1Max->setObjectName(QStringLiteral("en1Max"));
        en1Max->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en1Max->setMinimum(-99999);
        en1Max->setMaximum(99999);

        formLayout->setWidget(0, QFormLayout::FieldRole, en1Max);


        EnMax->addLayout(formLayout);

        EnSelect->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(EnSelect);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        CurMax = new QVBoxLayout(layoutWidget3);
        CurMax->setSpacing(6);
        CurMax->setContentsMargins(9, 9, 9, 9);
        CurMax->setObjectName(QStringLiteral("CurMax"));
        CurMax->setContentsMargins(0, 0, 0, 0);
        valMinScr_3 = new QLabel(layoutWidget3);
        valMinScr_3->setObjectName(QStringLiteral("valMinScr_3"));
        valMinScr_3->setFont(font);
        valMinScr_3->setTextFormat(Qt::AutoText);
        valMinScr_3->setAlignment(Qt::AlignCenter);

        CurMax->addWidget(valMinScr_3);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setLabelAlignment(Qt::AlignCenter);
        formLayout_3->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        en1Label_3 = new QLabel(layoutWidget3);
        en1Label_3->setObjectName(QStringLiteral("en1Label_3"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, en1Label_3);

        en2Label_3 = new QLabel(layoutWidget3);
        en2Label_3->setObjectName(QStringLiteral("en2Label_3"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, en2Label_3);

        en3Label_3 = new QLabel(layoutWidget3);
        en3Label_3->setObjectName(QStringLiteral("en3Label_3"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, en3Label_3);

        en4Label_3 = new QLabel(layoutWidget3);
        en4Label_3->setObjectName(QStringLiteral("en4Label_3"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, en4Label_3);

        en5Label_3 = new QLabel(layoutWidget3);
        en5Label_3->setObjectName(QStringLiteral("en5Label_3"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, en5Label_3);

        en6Label_3 = new QLabel(layoutWidget3);
        en6Label_3->setObjectName(QStringLiteral("en6Label_3"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, en6Label_3);

        curM1 = new QDoubleSpinBox(layoutWidget3);
        curM1->setObjectName(QStringLiteral("curM1"));
        curM1->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        curM1->setMinimum(200);
        curM1->setMaximum(4000);
        curM1->setValue(2000);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, curM1);

        curM6 = new QDoubleSpinBox(layoutWidget3);
        curM6->setObjectName(QStringLiteral("curM6"));
        curM6->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        curM6->setMinimum(200);
        curM6->setMaximum(4000);
        curM6->setValue(2000);

        formLayout_3->setWidget(5, QFormLayout::FieldRole, curM6);

        curM5 = new QDoubleSpinBox(layoutWidget3);
        curM5->setObjectName(QStringLiteral("curM5"));
        curM5->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        curM5->setMinimum(200);
        curM5->setMaximum(4000);
        curM5->setValue(2000);

        formLayout_3->setWidget(4, QFormLayout::FieldRole, curM5);

        curM4 = new QDoubleSpinBox(layoutWidget3);
        curM4->setObjectName(QStringLiteral("curM4"));
        curM4->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        curM4->setMinimum(200);
        curM4->setMaximum(4000);
        curM4->setValue(2000);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, curM4);

        curM3 = new QDoubleSpinBox(layoutWidget3);
        curM3->setObjectName(QStringLiteral("curM3"));
        curM3->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        curM3->setMinimum(200);
        curM3->setMaximum(4000);
        curM3->setValue(2000);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, curM3);

        curM2 = new QDoubleSpinBox(layoutWidget3);
        curM2->setObjectName(QStringLiteral("curM2"));
        curM2->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        curM2->setMinimum(200);
        curM2->setMaximum(4000);
        curM2->setValue(2000);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, curM2);


        CurMax->addLayout(formLayout_3);

        EnSelect->addWidget(layoutWidget3);

        verticalLayout->addWidget(EnSelect);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(100);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(16);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        adcVref = new QVBoxLayout();
        adcVref->setSpacing(6);
        adcVref->setObjectName(QStringLiteral("adcVref"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(12);
        font1.setItalic(false);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        label->setFont(font1);
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        label->setLineWidth(1);
        label->setMidLineWidth(0);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        adcVref->addWidget(label);

        in1V1 = new QRadioButton(layoutWidget);
        in1V1->setObjectName(QStringLiteral("in1V1"));

        adcVref->addWidget(in1V1);

        in2V56 = new QRadioButton(layoutWidget);
        in2V56->setObjectName(QStringLiteral("in2V56"));

        adcVref->addWidget(in2V56);

        ext = new QRadioButton(layoutWidget);
        ext->setObjectName(QStringLiteral("ext"));

        adcVref->addWidget(ext);


        horizontalLayout->addLayout(adcVref);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        adcOffset = new QVBoxLayout();
        adcOffset->setSpacing(6);
        adcOffset->setObjectName(QStringLiteral("adcOffset"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
#ifndef QT_NO_STATUSTIP
        label_2->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        label_2->setAlignment(Qt::AlignCenter);

        adcOffset->addWidget(label_2);

        offsetChose = new QComboBox(layoutWidget);
        offsetChose->setObjectName(QStringLiteral("offsetChose"));

        adcOffset->addWidget(offsetChose);


        verticalLayout_5->addLayout(adcOffset);

        MotorPwm = new QVBoxLayout();
        MotorPwm->setSpacing(6);
        MotorPwm->setObjectName(QStringLiteral("MotorPwm"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
#ifndef QT_NO_STATUSTIP
        label_3->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        label_3->setAlignment(Qt::AlignCenter);

        MotorPwm->addWidget(label_3);

        motFreqChose = new QComboBox(layoutWidget);
        motFreqChose->setObjectName(QStringLiteral("motFreqChose"));
        QFont font2;
        font2.setPointSize(10);
        motFreqChose->setFont(font2);
        motFreqChose->setEditable(false);

        MotorPwm->addWidget(motFreqChose);


        verticalLayout_5->addLayout(MotorPwm);


        horizontalLayout->addLayout(verticalLayout_5);


        horizontalLayout_2->addLayout(horizontalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(12);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        saveSetting = new QPushButton(layoutWidget);
        saveSetting->setObjectName(QStringLiteral("saveSetting"));

        verticalLayout_4->addWidget(saveSetting);

        loadSetting = new QPushButton(layoutWidget);
        loadSetting->setObjectName(QStringLiteral("loadSetting"));

        verticalLayout_4->addWidget(loadSetting);

        restoreSetting = new QPushButton(layoutWidget);
        restoreSetting->setObjectName(QStringLiteral("restoreSetting"));

        verticalLayout_4->addWidget(restoreSetting);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        en1Label_2->setBuddy(en1Min);
        en2Label_2->setBuddy(en2Min);
        en3Label_2->setBuddy(en3Min);
        en4Label_2->setBuddy(en4Min);
        en5Label_2->setBuddy(en5Min);
        en6Label_2->setBuddy(en6Min);
        en1Label->setBuddy(en1Max);
        en2Label->setBuddy(en2Max);
        en3Label->setBuddy(en3Max);
        en4Label->setBuddy(en4Max);
        en5Label->setBuddy(en5Max);
        en6Label->setBuddy(en6Max);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(en1Min, en1Max);
        QWidget::setTabOrder(en1Max, curM1);
        QWidget::setTabOrder(curM1, en2Min);
        QWidget::setTabOrder(en2Min, en2Max);
        QWidget::setTabOrder(en2Max, curM2);
        QWidget::setTabOrder(curM2, en3Min);
        QWidget::setTabOrder(en3Min, en3Max);
        QWidget::setTabOrder(en3Max, curM3);
        QWidget::setTabOrder(curM3, en4Min);
        QWidget::setTabOrder(en4Min, en4Max);
        QWidget::setTabOrder(en4Max, curM4);
        QWidget::setTabOrder(curM4, en5Min);
        QWidget::setTabOrder(en5Min, en5Max);
        QWidget::setTabOrder(en5Max, curM5);
        QWidget::setTabOrder(curM5, en6Min);
        QWidget::setTabOrder(en6Min, en6Max);
        QWidget::setTabOrder(en6Max, curM6);
        QWidget::setTabOrder(curM6, in1V1);
        QWidget::setTabOrder(in1V1, in2V56);
        QWidget::setTabOrder(in2V56, ext);
        QWidget::setTabOrder(ext, offsetChose);
        QWidget::setTabOrder(offsetChose, motFreqChose);
        QWidget::setTabOrder(motFreqChose, saveSetting);
        QWidget::setTabOrder(saveSetting, loadSetting);
        QWidget::setTabOrder(loadSetting, restoreSetting);

        retranslateUi(SettingBoardWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingBoardWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingBoardWindow, SLOT(reject()));

        motFreqChose->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SettingBoardWindow);
    } // setupUi

    void retranslateUi(QDialog *SettingBoardWindow)
    {
        SettingBoardWindow->setWindowTitle(QApplication::translate("SettingBoardWindow", "SettingBoard", Q_NULLPTR));
        valMinScr_2->setText(QApplication::translate("SettingBoardWindow", "En min [Step]", Q_NULLPTR));
        en1Label_2->setText(QApplication::translate("SettingBoardWindow", "En 1", Q_NULLPTR));
        en2Label_2->setText(QApplication::translate("SettingBoardWindow", "En 2", Q_NULLPTR));
        en3Label_2->setText(QApplication::translate("SettingBoardWindow", "En 3", Q_NULLPTR));
        en4Label_2->setText(QApplication::translate("SettingBoardWindow", "En 4", Q_NULLPTR));
        en5Label_2->setText(QApplication::translate("SettingBoardWindow", "En 5", Q_NULLPTR));
        en6Label_2->setText(QApplication::translate("SettingBoardWindow", "En 6", Q_NULLPTR));
        valMinScr->setText(QApplication::translate("SettingBoardWindow", "En MAX [Step]", Q_NULLPTR));
        en1Label->setText(QApplication::translate("SettingBoardWindow", "En 1", Q_NULLPTR));
        en2Label->setText(QApplication::translate("SettingBoardWindow", "En 2", Q_NULLPTR));
        en3Label->setText(QApplication::translate("SettingBoardWindow", "En 3", Q_NULLPTR));
        en4Label->setText(QApplication::translate("SettingBoardWindow", "En 4", Q_NULLPTR));
        en5Label->setText(QApplication::translate("SettingBoardWindow", "En 5", Q_NULLPTR));
        en6Label->setText(QApplication::translate("SettingBoardWindow", "En 6", Q_NULLPTR));
        valMinScr_3->setText(QApplication::translate("SettingBoardWindow", "Cur Max [mA]", Q_NULLPTR));
        en1Label_3->setText(QApplication::translate("SettingBoardWindow", "Mot1", Q_NULLPTR));
        en2Label_3->setText(QApplication::translate("SettingBoardWindow", "Mot2", Q_NULLPTR));
        en3Label_3->setText(QApplication::translate("SettingBoardWindow", "Mot3", Q_NULLPTR));
        en4Label_3->setText(QApplication::translate("SettingBoardWindow", "Mot4", Q_NULLPTR));
        en5Label_3->setText(QApplication::translate("SettingBoardWindow", "Mot5", Q_NULLPTR));
        en6Label_3->setText(QApplication::translate("SettingBoardWindow", "Mot6", Q_NULLPTR));
        label->setText(QApplication::translate("SettingBoardWindow", "Adc Vref", Q_NULLPTR));
        in1V1->setText(QApplication::translate("SettingBoardWindow", "1.1V Interna", Q_NULLPTR));
        in2V56->setText(QApplication::translate("SettingBoardWindow", "2.56V Interna", Q_NULLPTR));
        ext->setText(QApplication::translate("SettingBoardWindow", "Vref Esterna", Q_NULLPTR));
        label_2->setText(QApplication::translate("SettingBoardWindow", "Offset Remove", Q_NULLPTR));
        offsetChose->clear();
        offsetChose->insertItems(0, QStringList()
         << QApplication::translate("SettingBoardWindow", "Reading Directly", Q_NULLPTR)
         << QApplication::translate("SettingBoardWindow", "Remove Offset", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("SettingBoardWindow", "Motor PWM Freq", Q_NULLPTR));
        motFreqChose->clear();
        motFreqChose->insertItems(0, QStringList()
         << QApplication::translate("SettingBoardWindow", "30 hz", Q_NULLPTR)
         << QApplication::translate("SettingBoardWindow", "120 hz", Q_NULLPTR)
         << QApplication::translate("SettingBoardWindow", "490 hz", Q_NULLPTR)
         << QApplication::translate("SettingBoardWindow", "4 Khz", Q_NULLPTR)
         << QApplication::translate("SettingBoardWindow", "30 Khz", Q_NULLPTR)
        );
        saveSetting->setText(QApplication::translate("SettingBoardWindow", "Save", Q_NULLPTR));
        loadSetting->setText(QApplication::translate("SettingBoardWindow", "Load", Q_NULLPTR));
        restoreSetting->setText(QApplication::translate("SettingBoardWindow", "Restore", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SettingBoardWindow: public Ui_SettingBoardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGBOARDWINDOW_H
