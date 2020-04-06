/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionInfo;
    QAction *serialPort;
    QAction *actionConnection_Start;
    QAction *actionReset_Board;
    QAction *actionClose_connection;
    QAction *actionSerial_Find;
    QAction *actionB9600;
    QAction *actionB57600;
    QAction *actionB115200;
    QAction *actionB230400;
    QAction *actionB460800;
    QAction *actionB921600;
    QWidget *centralwidget;
    QTabWidget *tabReference;
    QWidget *Direct;
    QWidget *layoutWidget_6;
    QVBoxLayout *EnRef;
    QLabel *valMinScr_3;
    QFormLayout *formLayout_4;
    QLabel *en1Label_3;
    QSpinBox *en1Ref;
    QLabel *en2Label_3;
    QSpinBox *en2Ref;
    QLabel *en3Label_3;
    QSpinBox *en3Ref;
    QLabel *en4Label_3;
    QSpinBox *en4Ref;
    QLabel *en5Label_3;
    QSpinBox *en5Ref;
    QLabel *en6Label_3;
    QSpinBox *en6Ref;
    QWidget *Direct_Angular;
    QWidget *layoutWidget_13;
    QVBoxLayout *DegRef;
    QLabel *valMinScr_4;
    QFormLayout *formLayout_5;
    QLabel *en1Label_4;
    QLabel *en2Label_4;
    QLabel *en3Label_4;
    QLabel *en4Label_4;
    QLabel *en5Label_4;
    QLabel *en6Label_4;
    QSlider *pinzaRef;
    QDoubleSpinBox *thetaRef1;
    QDoubleSpinBox *thetaRef2;
    QDoubleSpinBox *thetaRef3;
    QDoubleSpinBox *thetaRef4;
    QDoubleSpinBox *thetaRef5;
    QWidget *Inverse;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *Pdes;
    QLabel *valMinScr_5;
    QFormLayout *formLayout_6;
    QLabel *en1Label_5;
    QDoubleSpinBox *xDes;
    QLabel *en2Label_5;
    QDoubleSpinBox *yDes;
    QLabel *en3Label_5;
    QDoubleSpinBox *zDes;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *Rdes;
    QLabel *valMinScr_6;
    QFormLayout *formLayout_7;
    QLabel *en1Label_6;
    QDoubleSpinBox *betaDes;
    QLabel *en2Label_6;
    QDoubleSpinBox *omegaDes;
    QSpacerItem *verticalSpacer_5;
    QSlider *pinzaInv;
    QLabel *en6Label_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QRadioButton *gH;
    QRadioButton *gL;
    QSpacerItem *verticalSpacer_6;
    QWidget *RoboSetup;
    QSplitter *splitter;
    QWidget *layoutWidget1;
    QVBoxLayout *homeOffset;
    QLabel *valMinScr_2;
    QFormLayout *formLayout_2;
    QLabel *en1Label_2;
    QSpinBox *en1Home;
    QLabel *en2Label_2;
    QSpinBox *en2Home;
    QLabel *en3Label_2;
    QSpinBox *en3Home;
    QLabel *en4Label_2;
    QSpinBox *en4Home;
    QLabel *en5Label_2;
    QSpinBox *en5Home;
    QLabel *en6Label_2;
    QSpinBox *en6Home;
    QWidget *layoutWidget2;
    QVBoxLayout *RoboSize;
    QLabel *label;
    QFormLayout *formLayout;
    QLabel *l1Label;
    QDoubleSpinBox *l1Robot;
    QLabel *l2Label;
    QDoubleSpinBox *l2Robot;
    QLabel *l3Label;
    QDoubleSpinBox *l3Robot;
    QLabel *l4Label;
    QDoubleSpinBox *d1Robot;
    QLabel *l5Label;
    QDoubleSpinBox *d5Robot;
    QPushButton *scorSwHome;
    QWidget *layoutWidget3;
    QVBoxLayout *en2deg;
    QLabel *label_2;
    QFormLayout *formLayout_3;
    QLabel *aLabel;
    QDoubleSpinBox *alphaRobot;
    QLabel *bLabel;
    QDoubleSpinBox *betaRobot;
    QLabel *cLabel;
    QDoubleSpinBox *gammaRobot;
    QLabel *dLabel;
    QDoubleSpinBox *deltaRobot;
    QPushButton *scorParamLoad;
    QPushButton *scorParamReset;
    QCustomPlot *plot;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_21;
    QPushButton *scorBoardSetup;
    QPushButton *controlSet;
    QPushButton *freeMove;
    QFrame *frame;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_7;
    QSplitter *splitter_5;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_7;
    QLabel *Xattuale;
    QLabel *Yattuale;
    QLabel *Zattuale;
    QLabel *en1Label_7;
    QLabel *en2Label_7;
    QVBoxLayout *verticalLayout_17;
    QLabel *xRead;
    QLabel *yRead;
    QLabel *zRead;
    QLabel *betaRead;
    QLabel *omegaRead;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_18;
    QLabel *encrease1_3;
    QLabel *encrease2_3;
    QLabel *encrease3_3;
    QLabel *encrease3_5;
    QLabel *encrease3_4;
    QVBoxLayout *verticalLayout_19;
    QLabel *xEr;
    QLabel *yEr;
    QLabel *zEr;
    QLabel *betaEr;
    QLabel *omegaEr;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QProgressBar *pinzaRead;
    QSplitter *splitter_4;
    QFrame *enRead;
    QVBoxLayout *verticalLayout_16;
    QLabel *label_4;
    QSplitter *splitter_3;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *Step1_direct;
    QLabel *Step2_direct;
    QLabel *Step3_direct;
    QLabel *Step4_direct;
    QLabel *Step5_direct;
    QLabel *Step6_direct;
    QVBoxLayout *verticalLayout_4;
    QLabel *enR1;
    QLabel *enR2;
    QLabel *enR3;
    QLabel *enR4;
    QLabel *enR5;
    QLabel *enR6;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *encrease1;
    QLabel *encrease2;
    QLabel *encrease3;
    QLabel *encrease4;
    QLabel *encrease5;
    QLabel *encrease6;
    QVBoxLayout *verticalLayout_6;
    QLabel *enEr1;
    QLabel *enEr2;
    QLabel *enEr3;
    QLabel *enEr4;
    QLabel *enEr5;
    QLabel *enEr6;
    QFrame *degRead;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_5;
    QSplitter *splitter_2;
    QWidget *layoutWidget9;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_8;
    QLabel *teta1_dir;
    QLabel *teta2_dir;
    QLabel *teta3_dit;
    QLabel *teta4_dit;
    QLabel *teta5_dir;
    QLabel *teta6_dir;
    QVBoxLayout *verticalLayout_11;
    QLabel *thR1;
    QLabel *thR2;
    QLabel *thR3;
    QLabel *thR4;
    QLabel *thR5;
    QLabel *pinzaOpen;
    QWidget *layoutWidget10;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_9;
    QLabel *encrease1_2;
    QLabel *encrease2_2;
    QLabel *encrease3_2;
    QLabel *encrease4_2;
    QLabel *encrease5_2;
    QLabel *encrease6_2;
    QVBoxLayout *verticalLayout_12;
    QLabel *thEr1;
    QLabel *thEr2;
    QLabel *thEr3;
    QLabel *thEr4;
    QLabel *thEr5;
    QLabel *pinzaOpenErr;
    QFrame *curRead;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_10;
    QLabel *ma1;
    QLabel *ma2;
    QLabel *ma3;
    QLabel *ma4;
    QLabel *ma5;
    QLabel *ma6;
    QVBoxLayout *verticalLayout_13;
    QLabel *mA1;
    QLabel *mA2;
    QLabel *mA3;
    QLabel *mA4;
    QLabel *mA5;
    QLabel *mA6;
    QWidget *layoutWidget11;
    QVBoxLayout *verticalLayout_22;
    QCheckBox *motPlot1;
    QCheckBox *motPlot2;
    QCheckBox *motPlot3;
    QCheckBox *motPlot4;
    QCheckBox *motPlot5;
    QCheckBox *motPlot6;
    QLabel *image;
    QWidget *layoutWidget12;
    QVBoxLayout *verticalLayout;
    QPushButton *sendRef;
    QPushButton *goHome;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QMenu *menuUartSetting;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(1100, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1100, 500));
        MainWindow->setMaximumSize(QSize(1100, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/Logo-Uni-Tor-Vergata.png_256x256.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setDocumentMode(true);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockNestingEnabled(false);
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        serialPort = new QAction(MainWindow);
        serialPort->setObjectName(QString::fromUtf8("serialPort"));
        actionConnection_Start = new QAction(MainWindow);
        actionConnection_Start->setObjectName(QString::fromUtf8("actionConnection_Start"));
        actionReset_Board = new QAction(MainWindow);
        actionReset_Board->setObjectName(QString::fromUtf8("actionReset_Board"));
        actionClose_connection = new QAction(MainWindow);
        actionClose_connection->setObjectName(QString::fromUtf8("actionClose_connection"));
        actionSerial_Find = new QAction(MainWindow);
        actionSerial_Find->setObjectName(QString::fromUtf8("actionSerial_Find"));
        actionSerial_Find->setEnabled(true);
        actionSerial_Find->setAutoRepeat(true);
        actionSerial_Find->setMenuRole(QAction::ApplicationSpecificRole);
        actionB9600 = new QAction(MainWindow);
        actionB9600->setObjectName(QString::fromUtf8("actionB9600"));
        actionB57600 = new QAction(MainWindow);
        actionB57600->setObjectName(QString::fromUtf8("actionB57600"));
        actionB115200 = new QAction(MainWindow);
        actionB115200->setObjectName(QString::fromUtf8("actionB115200"));
        actionB230400 = new QAction(MainWindow);
        actionB230400->setObjectName(QString::fromUtf8("actionB230400"));
        actionB460800 = new QAction(MainWindow);
        actionB460800->setObjectName(QString::fromUtf8("actionB460800"));
        actionB921600 = new QAction(MainWindow);
        actionB921600->setObjectName(QString::fromUtf8("actionB921600"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabReference = new QTabWidget(centralwidget);
        tabReference->setObjectName(QString::fromUtf8("tabReference"));
        tabReference->setGeometry(QRect(10, 10, 401, 301));
        QFont font;
        font.setPointSize(14);
        tabReference->setFont(font);
        tabReference->setTabPosition(QTabWidget::North);
        tabReference->setTabShape(QTabWidget::Rounded);
        tabReference->setUsesScrollButtons(false);
        tabReference->setDocumentMode(false);
        tabReference->setTabsClosable(false);
        tabReference->setMovable(false);
        tabReference->setTabBarAutoHide(false);
        Direct = new QWidget();
        Direct->setObjectName(QString::fromUtf8("Direct"));
        layoutWidget_6 = new QWidget(Direct);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 10, 143, 241));
        EnRef = new QVBoxLayout(layoutWidget_6);
        EnRef->setSpacing(6);
        EnRef->setObjectName(QString::fromUtf8("EnRef"));
        EnRef->setContentsMargins(0, 0, 0, 0);
        valMinScr_3 = new QLabel(layoutWidget_6);
        valMinScr_3->setObjectName(QString::fromUtf8("valMinScr_3"));
        sizePolicy.setHeightForWidth(valMinScr_3->sizePolicy().hasHeightForWidth());
        valMinScr_3->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        valMinScr_3->setFont(font1);
        valMinScr_3->setAlignment(Qt::AlignCenter);

        EnRef->addWidget(valMinScr_3);

        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_4->setLabelAlignment(Qt::AlignCenter);
        formLayout_4->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        en1Label_3 = new QLabel(layoutWidget_6);
        en1Label_3->setObjectName(QString::fromUtf8("en1Label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(en1Label_3->sizePolicy().hasHeightForWidth());
        en1Label_3->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(10);
        en1Label_3->setFont(font2);

        formLayout_4->setWidget(0, QFormLayout::LabelRole, en1Label_3);

        en1Ref = new QSpinBox(layoutWidget_6);
        en1Ref->setObjectName(QString::fromUtf8("en1Ref"));
        sizePolicy1.setHeightForWidth(en1Ref->sizePolicy().hasHeightForWidth());
        en1Ref->setSizePolicy(sizePolicy1);
        en1Ref->setFont(font2);
        en1Ref->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en1Ref->setMinimum(-99999);
        en1Ref->setMaximum(99999);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, en1Ref);

        en2Label_3 = new QLabel(layoutWidget_6);
        en2Label_3->setObjectName(QString::fromUtf8("en2Label_3"));
        sizePolicy1.setHeightForWidth(en2Label_3->sizePolicy().hasHeightForWidth());
        en2Label_3->setSizePolicy(sizePolicy1);
        en2Label_3->setFont(font2);

        formLayout_4->setWidget(1, QFormLayout::LabelRole, en2Label_3);

        en2Ref = new QSpinBox(layoutWidget_6);
        en2Ref->setObjectName(QString::fromUtf8("en2Ref"));
        sizePolicy1.setHeightForWidth(en2Ref->sizePolicy().hasHeightForWidth());
        en2Ref->setSizePolicy(sizePolicy1);
        en2Ref->setFont(font2);
        en2Ref->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en2Ref->setMinimum(-99999);
        en2Ref->setMaximum(99999);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, en2Ref);

        en3Label_3 = new QLabel(layoutWidget_6);
        en3Label_3->setObjectName(QString::fromUtf8("en3Label_3"));
        en3Label_3->setEnabled(true);
        sizePolicy1.setHeightForWidth(en3Label_3->sizePolicy().hasHeightForWidth());
        en3Label_3->setSizePolicy(sizePolicy1);
        en3Label_3->setFont(font2);

        formLayout_4->setWidget(2, QFormLayout::LabelRole, en3Label_3);

        en3Ref = new QSpinBox(layoutWidget_6);
        en3Ref->setObjectName(QString::fromUtf8("en3Ref"));
        sizePolicy1.setHeightForWidth(en3Ref->sizePolicy().hasHeightForWidth());
        en3Ref->setSizePolicy(sizePolicy1);
        en3Ref->setFont(font2);
        en3Ref->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en3Ref->setMinimum(-99999);
        en3Ref->setMaximum(99999);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, en3Ref);

        en4Label_3 = new QLabel(layoutWidget_6);
        en4Label_3->setObjectName(QString::fromUtf8("en4Label_3"));
        sizePolicy1.setHeightForWidth(en4Label_3->sizePolicy().hasHeightForWidth());
        en4Label_3->setSizePolicy(sizePolicy1);
        en4Label_3->setFont(font2);

        formLayout_4->setWidget(3, QFormLayout::LabelRole, en4Label_3);

        en4Ref = new QSpinBox(layoutWidget_6);
        en4Ref->setObjectName(QString::fromUtf8("en4Ref"));
        sizePolicy1.setHeightForWidth(en4Ref->sizePolicy().hasHeightForWidth());
        en4Ref->setSizePolicy(sizePolicy1);
        en4Ref->setFont(font2);
        en4Ref->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en4Ref->setMinimum(-99999);
        en4Ref->setMaximum(99999);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, en4Ref);

        en5Label_3 = new QLabel(layoutWidget_6);
        en5Label_3->setObjectName(QString::fromUtf8("en5Label_3"));
        sizePolicy1.setHeightForWidth(en5Label_3->sizePolicy().hasHeightForWidth());
        en5Label_3->setSizePolicy(sizePolicy1);
        en5Label_3->setFont(font2);

        formLayout_4->setWidget(4, QFormLayout::LabelRole, en5Label_3);

        en5Ref = new QSpinBox(layoutWidget_6);
        en5Ref->setObjectName(QString::fromUtf8("en5Ref"));
        sizePolicy1.setHeightForWidth(en5Ref->sizePolicy().hasHeightForWidth());
        en5Ref->setSizePolicy(sizePolicy1);
        en5Ref->setFont(font2);
        en5Ref->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en5Ref->setMinimum(-99999);
        en5Ref->setMaximum(99999);

        formLayout_4->setWidget(4, QFormLayout::FieldRole, en5Ref);

        en6Label_3 = new QLabel(layoutWidget_6);
        en6Label_3->setObjectName(QString::fromUtf8("en6Label_3"));
        sizePolicy1.setHeightForWidth(en6Label_3->sizePolicy().hasHeightForWidth());
        en6Label_3->setSizePolicy(sizePolicy1);
        en6Label_3->setFont(font2);

        formLayout_4->setWidget(5, QFormLayout::LabelRole, en6Label_3);

        en6Ref = new QSpinBox(layoutWidget_6);
        en6Ref->setObjectName(QString::fromUtf8("en6Ref"));
        sizePolicy1.setHeightForWidth(en6Ref->sizePolicy().hasHeightForWidth());
        en6Ref->setSizePolicy(sizePolicy1);
        en6Ref->setFont(font2);
        en6Ref->setWrapping(false);
        en6Ref->setFrame(true);
        en6Ref->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en6Ref->setMinimum(-99999);
        en6Ref->setMaximum(99999);

        formLayout_4->setWidget(5, QFormLayout::FieldRole, en6Ref);


        EnRef->addLayout(formLayout_4);

        tabReference->addTab(Direct, QString());
        Direct_Angular = new QWidget();
        Direct_Angular->setObjectName(QString::fromUtf8("Direct_Angular"));
        layoutWidget_13 = new QWidget(Direct_Angular);
        layoutWidget_13->setObjectName(QString::fromUtf8("layoutWidget_13"));
        layoutWidget_13->setGeometry(QRect(10, 10, 179, 231));
        DegRef = new QVBoxLayout(layoutWidget_13);
        DegRef->setSpacing(0);
        DegRef->setObjectName(QString::fromUtf8("DegRef"));
        DegRef->setContentsMargins(0, 0, 0, 0);
        valMinScr_4 = new QLabel(layoutWidget_13);
        valMinScr_4->setObjectName(QString::fromUtf8("valMinScr_4"));
        sizePolicy.setHeightForWidth(valMinScr_4->sizePolicy().hasHeightForWidth());
        valMinScr_4->setSizePolicy(sizePolicy);
        valMinScr_4->setFont(font1);
        valMinScr_4->setAlignment(Qt::AlignCenter);

        DegRef->addWidget(valMinScr_4);

        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        formLayout_5->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_5->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_5->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        en1Label_4 = new QLabel(layoutWidget_13);
        en1Label_4->setObjectName(QString::fromUtf8("en1Label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(en1Label_4->sizePolicy().hasHeightForWidth());
        en1Label_4->setSizePolicy(sizePolicy2);
        en1Label_4->setFont(font2);
        en1Label_4->setLayoutDirection(Qt::LeftToRight);
        en1Label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(0, QFormLayout::LabelRole, en1Label_4);

        en2Label_4 = new QLabel(layoutWidget_13);
        en2Label_4->setObjectName(QString::fromUtf8("en2Label_4"));
        sizePolicy2.setHeightForWidth(en2Label_4->sizePolicy().hasHeightForWidth());
        en2Label_4->setSizePolicy(sizePolicy2);
        en2Label_4->setFont(font2);
        en2Label_4->setLayoutDirection(Qt::LeftToRight);
        en2Label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(1, QFormLayout::LabelRole, en2Label_4);

        en3Label_4 = new QLabel(layoutWidget_13);
        en3Label_4->setObjectName(QString::fromUtf8("en3Label_4"));
        en3Label_4->setEnabled(true);
        sizePolicy2.setHeightForWidth(en3Label_4->sizePolicy().hasHeightForWidth());
        en3Label_4->setSizePolicy(sizePolicy2);
        en3Label_4->setFont(font2);
        en3Label_4->setLayoutDirection(Qt::LeftToRight);
        en3Label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(2, QFormLayout::LabelRole, en3Label_4);

        en4Label_4 = new QLabel(layoutWidget_13);
        en4Label_4->setObjectName(QString::fromUtf8("en4Label_4"));
        sizePolicy2.setHeightForWidth(en4Label_4->sizePolicy().hasHeightForWidth());
        en4Label_4->setSizePolicy(sizePolicy2);
        en4Label_4->setFont(font2);
        en4Label_4->setLayoutDirection(Qt::LeftToRight);
        en4Label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(3, QFormLayout::LabelRole, en4Label_4);

        en5Label_4 = new QLabel(layoutWidget_13);
        en5Label_4->setObjectName(QString::fromUtf8("en5Label_4"));
        sizePolicy2.setHeightForWidth(en5Label_4->sizePolicy().hasHeightForWidth());
        en5Label_4->setSizePolicy(sizePolicy2);
        en5Label_4->setFont(font2);
        en5Label_4->setLayoutDirection(Qt::LeftToRight);
        en5Label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(4, QFormLayout::LabelRole, en5Label_4);

        en6Label_4 = new QLabel(layoutWidget_13);
        en6Label_4->setObjectName(QString::fromUtf8("en6Label_4"));
        sizePolicy2.setHeightForWidth(en6Label_4->sizePolicy().hasHeightForWidth());
        en6Label_4->setSizePolicy(sizePolicy2);
        en6Label_4->setFont(font2);
        en6Label_4->setLayoutDirection(Qt::LeftToRight);
        en6Label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(5, QFormLayout::LabelRole, en6Label_4);

        pinzaRef = new QSlider(layoutWidget_13);
        pinzaRef->setObjectName(QString::fromUtf8("pinzaRef"));
        pinzaRef->setFont(font2);
        pinzaRef->setMaximum(100);
        pinzaRef->setOrientation(Qt::Horizontal);

        formLayout_5->setWidget(5, QFormLayout::FieldRole, pinzaRef);

        thetaRef1 = new QDoubleSpinBox(layoutWidget_13);
        thetaRef1->setObjectName(QString::fromUtf8("thetaRef1"));
        thetaRef1->setFont(font2);
        thetaRef1->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        thetaRef1->setMinimum(-999.000000000000000);
        thetaRef1->setMaximum(999.000000000000000);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, thetaRef1);

        thetaRef2 = new QDoubleSpinBox(layoutWidget_13);
        thetaRef2->setObjectName(QString::fromUtf8("thetaRef2"));
        thetaRef2->setFont(font2);
        thetaRef2->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        thetaRef2->setMinimum(-999.000000000000000);
        thetaRef2->setMaximum(999.000000000000000);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, thetaRef2);

        thetaRef3 = new QDoubleSpinBox(layoutWidget_13);
        thetaRef3->setObjectName(QString::fromUtf8("thetaRef3"));
        thetaRef3->setFont(font2);
        thetaRef3->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        thetaRef3->setMinimum(-999.000000000000000);
        thetaRef3->setMaximum(999.000000000000000);

        formLayout_5->setWidget(2, QFormLayout::FieldRole, thetaRef3);

        thetaRef4 = new QDoubleSpinBox(layoutWidget_13);
        thetaRef4->setObjectName(QString::fromUtf8("thetaRef4"));
        thetaRef4->setFont(font2);
        thetaRef4->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        thetaRef4->setMinimum(-999.000000000000000);
        thetaRef4->setMaximum(999.000000000000000);

        formLayout_5->setWidget(3, QFormLayout::FieldRole, thetaRef4);

        thetaRef5 = new QDoubleSpinBox(layoutWidget_13);
        thetaRef5->setObjectName(QString::fromUtf8("thetaRef5"));
        thetaRef5->setFont(font2);
        thetaRef5->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        thetaRef5->setMinimum(-999.000000000000000);
        thetaRef5->setMaximum(999.000000000000000);

        formLayout_5->setWidget(4, QFormLayout::FieldRole, thetaRef5);


        DegRef->addLayout(formLayout_5);

        tabReference->addTab(Direct_Angular, QString());
        Inverse = new QWidget();
        Inverse->setObjectName(QString::fromUtf8("Inverse"));
        Inverse->setFont(font2);
        layoutWidget = new QWidget(Inverse);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 381, 165));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Pdes = new QVBoxLayout();
        Pdes->setSpacing(6);
        Pdes->setObjectName(QString::fromUtf8("Pdes"));
        valMinScr_5 = new QLabel(layoutWidget);
        valMinScr_5->setObjectName(QString::fromUtf8("valMinScr_5"));
        valMinScr_5->setFont(font1);
        valMinScr_5->setAlignment(Qt::AlignCenter);

        Pdes->addWidget(valMinScr_5);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        formLayout_6->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_6->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_6->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        en1Label_5 = new QLabel(layoutWidget);
        en1Label_5->setObjectName(QString::fromUtf8("en1Label_5"));
        sizePolicy2.setHeightForWidth(en1Label_5->sizePolicy().hasHeightForWidth());
        en1Label_5->setSizePolicy(sizePolicy2);
        en1Label_5->setLayoutDirection(Qt::LeftToRight);
        en1Label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(0, QFormLayout::LabelRole, en1Label_5);

        xDes = new QDoubleSpinBox(layoutWidget);
        xDes->setObjectName(QString::fromUtf8("xDes"));
        xDes->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        xDes->setProperty("showGroupSeparator", QVariant(false));
        xDes->setMinimum(-999.000000000000000);
        xDes->setMaximum(999.000000000000000);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, xDes);

        en2Label_5 = new QLabel(layoutWidget);
        en2Label_5->setObjectName(QString::fromUtf8("en2Label_5"));
        sizePolicy2.setHeightForWidth(en2Label_5->sizePolicy().hasHeightForWidth());
        en2Label_5->setSizePolicy(sizePolicy2);
        en2Label_5->setLayoutDirection(Qt::LeftToRight);
        en2Label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(1, QFormLayout::LabelRole, en2Label_5);

        yDes = new QDoubleSpinBox(layoutWidget);
        yDes->setObjectName(QString::fromUtf8("yDes"));
        yDes->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        yDes->setProperty("showGroupSeparator", QVariant(false));
        yDes->setMinimum(-999.000000000000000);
        yDes->setMaximum(999.000000000000000);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, yDes);

        en3Label_5 = new QLabel(layoutWidget);
        en3Label_5->setObjectName(QString::fromUtf8("en3Label_5"));
        en3Label_5->setEnabled(true);
        sizePolicy2.setHeightForWidth(en3Label_5->sizePolicy().hasHeightForWidth());
        en3Label_5->setSizePolicy(sizePolicy2);
        en3Label_5->setLayoutDirection(Qt::LeftToRight);
        en3Label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(2, QFormLayout::LabelRole, en3Label_5);

        zDes = new QDoubleSpinBox(layoutWidget);
        zDes->setObjectName(QString::fromUtf8("zDes"));
        zDes->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        zDes->setProperty("showGroupSeparator", QVariant(false));
        zDes->setMinimum(-999.000000000000000);
        zDes->setMaximum(999.000000000000000);

        formLayout_6->setWidget(2, QFormLayout::FieldRole, zDes);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_6->setItem(3, QFormLayout::FieldRole, verticalSpacer_4);


        Pdes->addLayout(formLayout_6);


        horizontalLayout->addLayout(Pdes);

        Rdes = new QVBoxLayout();
        Rdes->setSpacing(6);
        Rdes->setObjectName(QString::fromUtf8("Rdes"));
        valMinScr_6 = new QLabel(layoutWidget);
        valMinScr_6->setObjectName(QString::fromUtf8("valMinScr_6"));
        valMinScr_6->setFont(font1);
        valMinScr_6->setAlignment(Qt::AlignCenter);

        Rdes->addWidget(valMinScr_6);

        formLayout_7 = new QFormLayout();
        formLayout_7->setObjectName(QString::fromUtf8("formLayout_7"));
        formLayout_7->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_7->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_7->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        en1Label_6 = new QLabel(layoutWidget);
        en1Label_6->setObjectName(QString::fromUtf8("en1Label_6"));
        sizePolicy2.setHeightForWidth(en1Label_6->sizePolicy().hasHeightForWidth());
        en1Label_6->setSizePolicy(sizePolicy2);
        en1Label_6->setLayoutDirection(Qt::LeftToRight);
        en1Label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_7->setWidget(0, QFormLayout::LabelRole, en1Label_6);

        betaDes = new QDoubleSpinBox(layoutWidget);
        betaDes->setObjectName(QString::fromUtf8("betaDes"));
        betaDes->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        betaDes->setProperty("showGroupSeparator", QVariant(false));
        betaDes->setMinimum(-999.000000000000000);
        betaDes->setMaximum(999.000000000000000);

        formLayout_7->setWidget(0, QFormLayout::FieldRole, betaDes);

        en2Label_6 = new QLabel(layoutWidget);
        en2Label_6->setObjectName(QString::fromUtf8("en2Label_6"));
        sizePolicy2.setHeightForWidth(en2Label_6->sizePolicy().hasHeightForWidth());
        en2Label_6->setSizePolicy(sizePolicy2);
        en2Label_6->setLayoutDirection(Qt::LeftToRight);
        en2Label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_7->setWidget(1, QFormLayout::LabelRole, en2Label_6);

        omegaDes = new QDoubleSpinBox(layoutWidget);
        omegaDes->setObjectName(QString::fromUtf8("omegaDes"));
        omegaDes->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        omegaDes->setProperty("showGroupSeparator", QVariant(false));
        omegaDes->setMinimum(-999.000000000000000);
        omegaDes->setMaximum(999.000000000000000);

        formLayout_7->setWidget(1, QFormLayout::FieldRole, omegaDes);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_7->setItem(3, QFormLayout::FieldRole, verticalSpacer_5);

        pinzaInv = new QSlider(layoutWidget);
        pinzaInv->setObjectName(QString::fromUtf8("pinzaInv"));
        pinzaInv->setMaximum(100);
        pinzaInv->setOrientation(Qt::Horizontal);

        formLayout_7->setWidget(2, QFormLayout::FieldRole, pinzaInv);

        en6Label_5 = new QLabel(layoutWidget);
        en6Label_5->setObjectName(QString::fromUtf8("en6Label_5"));
        sizePolicy2.setHeightForWidth(en6Label_5->sizePolicy().hasHeightForWidth());
        en6Label_5->setSizePolicy(sizePolicy2);
        en6Label_5->setLayoutDirection(Qt::LeftToRight);
        en6Label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_7->setWidget(2, QFormLayout::LabelRole, en6Label_5);


        Rdes->addLayout(formLayout_7);


        horizontalLayout->addLayout(Rdes);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font3;
        font3.setPointSize(12);
        label_3->setFont(font3);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        gH = new QRadioButton(layoutWidget);
        gH->setObjectName(QString::fromUtf8("gH"));
        QFont font4;
        font4.setFamily(QString::fromUtf8(".SF NS Text"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        gH->setFont(font4);
        gH->setToolTipDuration(-1);
        gH->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(gH);

        gL = new QRadioButton(layoutWidget);
        gL->setObjectName(QString::fromUtf8("gL"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(gL->sizePolicy().hasHeightForWidth());
        gL->setSizePolicy(sizePolicy3);
        gL->setFont(font4);
        gL->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(gL);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);


        horizontalLayout->addLayout(verticalLayout_3);

        tabReference->addTab(Inverse, QString());
        RoboSetup = new QWidget();
        RoboSetup->setObjectName(QString::fromUtf8("RoboSetup"));
        RoboSetup->setFont(font2);
        splitter = new QSplitter(RoboSetup);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(10, 10, 381, 241));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(12);
        splitter->setChildrenCollapsible(false);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        homeOffset = new QVBoxLayout(layoutWidget1);
        homeOffset->setObjectName(QString::fromUtf8("homeOffset"));
        homeOffset->setContentsMargins(0, 0, 0, 0);
        valMinScr_2 = new QLabel(layoutWidget1);
        valMinScr_2->setObjectName(QString::fromUtf8("valMinScr_2"));
        sizePolicy.setHeightForWidth(valMinScr_2->sizePolicy().hasHeightForWidth());
        valMinScr_2->setSizePolicy(sizePolicy);
        valMinScr_2->setFont(font1);
        valMinScr_2->setAlignment(Qt::AlignCenter);

        homeOffset->addWidget(valMinScr_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setLabelAlignment(Qt::AlignCenter);
        formLayout_2->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        formLayout_2->setVerticalSpacing(6);
        en1Label_2 = new QLabel(layoutWidget1);
        en1Label_2->setObjectName(QString::fromUtf8("en1Label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, en1Label_2);

        en1Home = new QSpinBox(layoutWidget1);
        en1Home->setObjectName(QString::fromUtf8("en1Home"));
        en1Home->setWrapping(false);
        en1Home->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en1Home->setMinimum(-99999);
        en1Home->setMaximum(99999);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, en1Home);

        en2Label_2 = new QLabel(layoutWidget1);
        en2Label_2->setObjectName(QString::fromUtf8("en2Label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, en2Label_2);

        en2Home = new QSpinBox(layoutWidget1);
        en2Home->setObjectName(QString::fromUtf8("en2Home"));
        en2Home->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en2Home->setMinimum(-99999);
        en2Home->setMaximum(99999);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, en2Home);

        en3Label_2 = new QLabel(layoutWidget1);
        en3Label_2->setObjectName(QString::fromUtf8("en3Label_2"));
        en3Label_2->setEnabled(true);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, en3Label_2);

        en3Home = new QSpinBox(layoutWidget1);
        en3Home->setObjectName(QString::fromUtf8("en3Home"));
        en3Home->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en3Home->setMinimum(-99999);
        en3Home->setMaximum(99999);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, en3Home);

        en4Label_2 = new QLabel(layoutWidget1);
        en4Label_2->setObjectName(QString::fromUtf8("en4Label_2"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, en4Label_2);

        en4Home = new QSpinBox(layoutWidget1);
        en4Home->setObjectName(QString::fromUtf8("en4Home"));
        en4Home->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en4Home->setMinimum(-99999);
        en4Home->setMaximum(99999);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, en4Home);

        en5Label_2 = new QLabel(layoutWidget1);
        en5Label_2->setObjectName(QString::fromUtf8("en5Label_2"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, en5Label_2);

        en5Home = new QSpinBox(layoutWidget1);
        en5Home->setObjectName(QString::fromUtf8("en5Home"));
        en5Home->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en5Home->setMinimum(-99999);
        en5Home->setMaximum(99999);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, en5Home);

        en6Label_2 = new QLabel(layoutWidget1);
        en6Label_2->setObjectName(QString::fromUtf8("en6Label_2"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, en6Label_2);

        en6Home = new QSpinBox(layoutWidget1);
        en6Home->setObjectName(QString::fromUtf8("en6Home"));
        en6Home->setWrapping(false);
        en6Home->setFrame(true);
        en6Home->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        en6Home->setMinimum(-99999);
        en6Home->setMaximum(99999);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, en6Home);


        homeOffset->addLayout(formLayout_2);

        splitter->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        RoboSize = new QVBoxLayout(layoutWidget2);
        RoboSize->setObjectName(QString::fromUtf8("RoboSize"));
        RoboSize->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font3);
        label->setAlignment(Qt::AlignCenter);

        RoboSize->addWidget(label);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        l1Label = new QLabel(layoutWidget2);
        l1Label->setObjectName(QString::fromUtf8("l1Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, l1Label);

        l1Robot = new QDoubleSpinBox(layoutWidget2);
        l1Robot->setObjectName(QString::fromUtf8("l1Robot"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(l1Robot->sizePolicy().hasHeightForWidth());
        l1Robot->setSizePolicy(sizePolicy4);
        l1Robot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        l1Robot->setMinimum(-99999.000000000000000);
        l1Robot->setMaximum(99999.000000000000000);
        l1Robot->setSingleStep(0.500000000000000);
        l1Robot->setValue(5.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, l1Robot);

        l2Label = new QLabel(layoutWidget2);
        l2Label->setObjectName(QString::fromUtf8("l2Label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, l2Label);

        l2Robot = new QDoubleSpinBox(layoutWidget2);
        l2Robot->setObjectName(QString::fromUtf8("l2Robot"));
        sizePolicy4.setHeightForWidth(l2Robot->sizePolicy().hasHeightForWidth());
        l2Robot->setSizePolicy(sizePolicy4);
        l2Robot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        l2Robot->setMinimum(-99999.000000000000000);
        l2Robot->setMaximum(99999.000000000000000);
        l2Robot->setSingleStep(0.500000000000000);
        l2Robot->setValue(22.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, l2Robot);

        l3Label = new QLabel(layoutWidget2);
        l3Label->setObjectName(QString::fromUtf8("l3Label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, l3Label);

        l3Robot = new QDoubleSpinBox(layoutWidget2);
        l3Robot->setObjectName(QString::fromUtf8("l3Robot"));
        sizePolicy4.setHeightForWidth(l3Robot->sizePolicy().hasHeightForWidth());
        l3Robot->setSizePolicy(sizePolicy4);
        l3Robot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        l3Robot->setMinimum(-99999.000000000000000);
        l3Robot->setMaximum(99999.000000000000000);
        l3Robot->setSingleStep(0.500000000000000);
        l3Robot->setValue(22.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, l3Robot);

        l4Label = new QLabel(layoutWidget2);
        l4Label->setObjectName(QString::fromUtf8("l4Label"));

        formLayout->setWidget(3, QFormLayout::LabelRole, l4Label);

        d1Robot = new QDoubleSpinBox(layoutWidget2);
        d1Robot->setObjectName(QString::fromUtf8("d1Robot"));
        sizePolicy4.setHeightForWidth(d1Robot->sizePolicy().hasHeightForWidth());
        d1Robot->setSizePolicy(sizePolicy4);
        d1Robot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        d1Robot->setMinimum(-99999.000000000000000);
        d1Robot->setMaximum(99999.000000000000000);
        d1Robot->setSingleStep(0.500000000000000);
        d1Robot->setValue(2.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, d1Robot);

        l5Label = new QLabel(layoutWidget2);
        l5Label->setObjectName(QString::fromUtf8("l5Label"));

        formLayout->setWidget(4, QFormLayout::LabelRole, l5Label);

        d5Robot = new QDoubleSpinBox(layoutWidget2);
        d5Robot->setObjectName(QString::fromUtf8("d5Robot"));
        sizePolicy4.setHeightForWidth(d5Robot->sizePolicy().hasHeightForWidth());
        d5Robot->setSizePolicy(sizePolicy4);
        d5Robot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        d5Robot->setMinimum(-99999.000000000000000);
        d5Robot->setMaximum(99999.000000000000000);
        d5Robot->setSingleStep(0.500000000000000);
        d5Robot->setValue(3.000000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, d5Robot);

        scorSwHome = new QPushButton(layoutWidget2);
        scorSwHome->setObjectName(QString::fromUtf8("scorSwHome"));
        scorSwHome->setFont(font2);
        scorSwHome->setStyleSheet(QString::fromUtf8(""));

        formLayout->setWidget(5, QFormLayout::FieldRole, scorSwHome);


        RoboSize->addLayout(formLayout);

        splitter->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(splitter);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        en2deg = new QVBoxLayout(layoutWidget3);
        en2deg->setObjectName(QString::fromUtf8("en2deg"));
        en2deg->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignCenter);

        en2deg->addWidget(label_2);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setHorizontalSpacing(6);
        aLabel = new QLabel(layoutWidget3);
        aLabel->setObjectName(QString::fromUtf8("aLabel"));
        aLabel->setFont(font2);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, aLabel);

        alphaRobot = new QDoubleSpinBox(layoutWidget3);
        alphaRobot->setObjectName(QString::fromUtf8("alphaRobot"));
        sizePolicy4.setHeightForWidth(alphaRobot->sizePolicy().hasHeightForWidth());
        alphaRobot->setSizePolicy(sizePolicy4);
        alphaRobot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        alphaRobot->setMinimum(-99999.000000000000000);
        alphaRobot->setMaximum(99999.000000000000000);
        alphaRobot->setSingleStep(0.010000000000000);
        alphaRobot->setValue(0.010000000000000);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, alphaRobot);

        bLabel = new QLabel(layoutWidget3);
        bLabel->setObjectName(QString::fromUtf8("bLabel"));
        bLabel->setFont(font2);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, bLabel);

        betaRobot = new QDoubleSpinBox(layoutWidget3);
        betaRobot->setObjectName(QString::fromUtf8("betaRobot"));
        sizePolicy4.setHeightForWidth(betaRobot->sizePolicy().hasHeightForWidth());
        betaRobot->setSizePolicy(sizePolicy4);
        betaRobot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        betaRobot->setMinimum(-99999.000000000000000);
        betaRobot->setMaximum(99999.000000000000000);
        betaRobot->setSingleStep(0.010000000000000);
        betaRobot->setValue(0.010000000000000);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, betaRobot);

        cLabel = new QLabel(layoutWidget3);
        cLabel->setObjectName(QString::fromUtf8("cLabel"));
        cLabel->setFont(font2);

        formLayout_3->setWidget(2, QFormLayout::LabelRole, cLabel);

        gammaRobot = new QDoubleSpinBox(layoutWidget3);
        gammaRobot->setObjectName(QString::fromUtf8("gammaRobot"));
        sizePolicy4.setHeightForWidth(gammaRobot->sizePolicy().hasHeightForWidth());
        gammaRobot->setSizePolicy(sizePolicy4);
        gammaRobot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        gammaRobot->setMinimum(-99999.000000000000000);
        gammaRobot->setMaximum(99999.000000000000000);
        gammaRobot->setSingleStep(0.010000000000000);
        gammaRobot->setValue(0.010000000000000);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, gammaRobot);

        dLabel = new QLabel(layoutWidget3);
        dLabel->setObjectName(QString::fromUtf8("dLabel"));
        dLabel->setFont(font2);

        formLayout_3->setWidget(3, QFormLayout::LabelRole, dLabel);

        deltaRobot = new QDoubleSpinBox(layoutWidget3);
        deltaRobot->setObjectName(QString::fromUtf8("deltaRobot"));
        sizePolicy4.setHeightForWidth(deltaRobot->sizePolicy().hasHeightForWidth());
        deltaRobot->setSizePolicy(sizePolicy4);
        deltaRobot->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        deltaRobot->setMinimum(-99999.000000000000000);
        deltaRobot->setMaximum(99999.000000000000000);
        deltaRobot->setSingleStep(0.010000000000000);
        deltaRobot->setValue(0.010000000000000);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, deltaRobot);

        scorParamLoad = new QPushButton(layoutWidget3);
        scorParamLoad->setObjectName(QString::fromUtf8("scorParamLoad"));
        scorParamLoad->setFont(font2);
        scorParamLoad->setStyleSheet(QString::fromUtf8(""));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, scorParamLoad);

        scorParamReset = new QPushButton(layoutWidget3);
        scorParamReset->setObjectName(QString::fromUtf8("scorParamReset"));
        sizePolicy1.setHeightForWidth(scorParamReset->sizePolicy().hasHeightForWidth());
        scorParamReset->setSizePolicy(sizePolicy1);
        scorParamReset->setFont(font2);
        scorParamReset->setStyleSheet(QString::fromUtf8(""));

        formLayout_3->setWidget(5, QFormLayout::FieldRole, scorParamReset);


        en2deg->addLayout(formLayout_3);

        splitter->addWidget(layoutWidget3);
        tabReference->addTab(RoboSetup, QString());
        plot = new QCustomPlot(centralwidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(620, 180, 401, 261));
        layoutWidget4 = new QWidget(centralwidget);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 320, 121, 122));
        verticalLayout_21 = new QVBoxLayout(layoutWidget4);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        scorBoardSetup = new QPushButton(layoutWidget4);
        scorBoardSetup->setObjectName(QString::fromUtf8("scorBoardSetup"));

        verticalLayout_21->addWidget(scorBoardSetup);

        controlSet = new QPushButton(layoutWidget4);
        controlSet->setObjectName(QString::fromUtf8("controlSet"));

        verticalLayout_21->addWidget(controlSet);

        freeMove = new QPushButton(layoutWidget4);
        freeMove->setObjectName(QString::fromUtf8("freeMove"));

        verticalLayout_21->addWidget(freeMove);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(420, 180, 191, 171));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(2);
        verticalLayout_20 = new QVBoxLayout(frame);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font3);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_20->addWidget(label_7);

        splitter_5 = new QSplitter(frame);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        splitter_5->setOrientation(Qt::Horizontal);
        layoutWidget5 = new QWidget(splitter_5);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        Xattuale = new QLabel(layoutWidget5);
        Xattuale->setObjectName(QString::fromUtf8("Xattuale"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(Xattuale->sizePolicy().hasHeightForWidth());
        Xattuale->setSizePolicy(sizePolicy5);
        QFont font5;
        font5.setFamily(QString::fromUtf8(".SF NS Text"));
        font5.setPointSize(10);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        font5.setKerning(true);
        Xattuale->setFont(font5);
        Xattuale->setStyleSheet(QString::fromUtf8(""));
        Xattuale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_7->addWidget(Xattuale);

        Yattuale = new QLabel(layoutWidget5);
        Yattuale->setObjectName(QString::fromUtf8("Yattuale"));
        sizePolicy5.setHeightForWidth(Yattuale->sizePolicy().hasHeightForWidth());
        Yattuale->setSizePolicy(sizePolicy5);
        Yattuale->setFont(font4);
        Yattuale->setStyleSheet(QString::fromUtf8(""));
        Yattuale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_7->addWidget(Yattuale);

        Zattuale = new QLabel(layoutWidget5);
        Zattuale->setObjectName(QString::fromUtf8("Zattuale"));
        sizePolicy5.setHeightForWidth(Zattuale->sizePolicy().hasHeightForWidth());
        Zattuale->setSizePolicy(sizePolicy5);
        Zattuale->setFont(font4);
        Zattuale->setStyleSheet(QString::fromUtf8(""));
        Zattuale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_7->addWidget(Zattuale);

        en1Label_7 = new QLabel(layoutWidget5);
        en1Label_7->setObjectName(QString::fromUtf8("en1Label_7"));
        sizePolicy5.setHeightForWidth(en1Label_7->sizePolicy().hasHeightForWidth());
        en1Label_7->setSizePolicy(sizePolicy5);
        en1Label_7->setLayoutDirection(Qt::LeftToRight);
        en1Label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_7->addWidget(en1Label_7);

        en2Label_7 = new QLabel(layoutWidget5);
        en2Label_7->setObjectName(QString::fromUtf8("en2Label_7"));
        sizePolicy5.setHeightForWidth(en2Label_7->sizePolicy().hasHeightForWidth());
        en2Label_7->setSizePolicy(sizePolicy5);
        en2Label_7->setLayoutDirection(Qt::LeftToRight);
        en2Label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_7->addWidget(en2Label_7);


        horizontalLayout_5->addLayout(verticalLayout_7);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        xRead = new QLabel(layoutWidget5);
        xRead->setObjectName(QString::fromUtf8("xRead"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(xRead->sizePolicy().hasHeightForWidth());
        xRead->setSizePolicy(sizePolicy6);

        verticalLayout_17->addWidget(xRead);

        yRead = new QLabel(layoutWidget5);
        yRead->setObjectName(QString::fromUtf8("yRead"));
        sizePolicy6.setHeightForWidth(yRead->sizePolicy().hasHeightForWidth());
        yRead->setSizePolicy(sizePolicy6);

        verticalLayout_17->addWidget(yRead);

        zRead = new QLabel(layoutWidget5);
        zRead->setObjectName(QString::fromUtf8("zRead"));
        sizePolicy6.setHeightForWidth(zRead->sizePolicy().hasHeightForWidth());
        zRead->setSizePolicy(sizePolicy6);

        verticalLayout_17->addWidget(zRead);

        betaRead = new QLabel(layoutWidget5);
        betaRead->setObjectName(QString::fromUtf8("betaRead"));
        sizePolicy6.setHeightForWidth(betaRead->sizePolicy().hasHeightForWidth());
        betaRead->setSizePolicy(sizePolicy6);

        verticalLayout_17->addWidget(betaRead);

        omegaRead = new QLabel(layoutWidget5);
        omegaRead->setObjectName(QString::fromUtf8("omegaRead"));
        sizePolicy6.setHeightForWidth(omegaRead->sizePolicy().hasHeightForWidth());
        omegaRead->setSizePolicy(sizePolicy6);

        verticalLayout_17->addWidget(omegaRead);


        horizontalLayout_5->addLayout(verticalLayout_17);

        splitter_5->addWidget(layoutWidget5);
        layoutWidget6 = new QWidget(splitter_5);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        encrease1_3 = new QLabel(layoutWidget6);
        encrease1_3->setObjectName(QString::fromUtf8("encrease1_3"));
        sizePolicy5.setHeightForWidth(encrease1_3->sizePolicy().hasHeightForWidth());
        encrease1_3->setSizePolicy(sizePolicy5);
        encrease1_3->setFont(font2);
        encrease1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_18->addWidget(encrease1_3);

        encrease2_3 = new QLabel(layoutWidget6);
        encrease2_3->setObjectName(QString::fromUtf8("encrease2_3"));
        sizePolicy5.setHeightForWidth(encrease2_3->sizePolicy().hasHeightForWidth());
        encrease2_3->setSizePolicy(sizePolicy5);
        encrease2_3->setFont(font2);
        encrease2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_18->addWidget(encrease2_3);

        encrease3_3 = new QLabel(layoutWidget6);
        encrease3_3->setObjectName(QString::fromUtf8("encrease3_3"));
        sizePolicy5.setHeightForWidth(encrease3_3->sizePolicy().hasHeightForWidth());
        encrease3_3->setSizePolicy(sizePolicy5);
        encrease3_3->setFont(font2);
        encrease3_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrease3_3->setIndent(-1);

        verticalLayout_18->addWidget(encrease3_3);

        encrease3_5 = new QLabel(layoutWidget6);
        encrease3_5->setObjectName(QString::fromUtf8("encrease3_5"));
        sizePolicy5.setHeightForWidth(encrease3_5->sizePolicy().hasHeightForWidth());
        encrease3_5->setSizePolicy(sizePolicy5);
        encrease3_5->setFont(font2);
        encrease3_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrease3_5->setIndent(-1);

        verticalLayout_18->addWidget(encrease3_5);

        encrease3_4 = new QLabel(layoutWidget6);
        encrease3_4->setObjectName(QString::fromUtf8("encrease3_4"));
        sizePolicy5.setHeightForWidth(encrease3_4->sizePolicy().hasHeightForWidth());
        encrease3_4->setSizePolicy(sizePolicy5);
        encrease3_4->setFont(font2);
        encrease3_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrease3_4->setIndent(-1);

        verticalLayout_18->addWidget(encrease3_4);


        horizontalLayout_4->addLayout(verticalLayout_18);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        xEr = new QLabel(layoutWidget6);
        xEr->setObjectName(QString::fromUtf8("xEr"));
        sizePolicy6.setHeightForWidth(xEr->sizePolicy().hasHeightForWidth());
        xEr->setSizePolicy(sizePolicy6);
        xEr->setFont(font2);

        verticalLayout_19->addWidget(xEr);

        yEr = new QLabel(layoutWidget6);
        yEr->setObjectName(QString::fromUtf8("yEr"));
        sizePolicy6.setHeightForWidth(yEr->sizePolicy().hasHeightForWidth());
        yEr->setSizePolicy(sizePolicy6);
        yEr->setFont(font2);

        verticalLayout_19->addWidget(yEr);

        zEr = new QLabel(layoutWidget6);
        zEr->setObjectName(QString::fromUtf8("zEr"));
        sizePolicy6.setHeightForWidth(zEr->sizePolicy().hasHeightForWidth());
        zEr->setSizePolicy(sizePolicy6);
        zEr->setFont(font2);

        verticalLayout_19->addWidget(zEr);

        betaEr = new QLabel(layoutWidget6);
        betaEr->setObjectName(QString::fromUtf8("betaEr"));
        sizePolicy6.setHeightForWidth(betaEr->sizePolicy().hasHeightForWidth());
        betaEr->setSizePolicy(sizePolicy6);
        betaEr->setFont(font2);

        verticalLayout_19->addWidget(betaEr);

        omegaEr = new QLabel(layoutWidget6);
        omegaEr->setObjectName(QString::fromUtf8("omegaEr"));
        sizePolicy6.setHeightForWidth(omegaEr->sizePolicy().hasHeightForWidth());
        omegaEr->setSizePolicy(sizePolicy6);
        omegaEr->setFont(font2);

        verticalLayout_19->addWidget(omegaEr);


        horizontalLayout_4->addLayout(verticalLayout_19);

        splitter_5->addWidget(layoutWidget6);

        verticalLayout_20->addWidget(splitter_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy7(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy7);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_8);

        pinzaRead = new QProgressBar(frame);
        pinzaRead->setObjectName(QString::fromUtf8("pinzaRead"));
        pinzaRead->setValue(0);

        horizontalLayout_6->addWidget(pinzaRead);


        verticalLayout_20->addLayout(horizontalLayout_6);

        splitter_4 = new QSplitter(centralwidget);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setGeometry(QRect(420, 10, 671, 160));
        QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(splitter_4->sizePolicy().hasHeightForWidth());
        splitter_4->setSizePolicy(sizePolicy8);
        splitter_4->setOrientation(Qt::Horizontal);
        splitter_4->setHandleWidth(12);
        splitter_4->setChildrenCollapsible(true);
        enRead = new QFrame(splitter_4);
        enRead->setObjectName(QString::fromUtf8("enRead"));
        enRead->setFrameShape(QFrame::StyledPanel);
        enRead->setFrameShadow(QFrame::Sunken);
        enRead->setLineWidth(2);
        enRead->setMidLineWidth(0);
        verticalLayout_16 = new QVBoxLayout(enRead);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        label_4 = new QLabel(enRead);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font3);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(label_4);

        splitter_3 = new QSplitter(enRead);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter_3->setChildrenCollapsible(false);
        layoutWidget7 = new QWidget(splitter_3);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        QFont font6;
        layoutWidget7->setFont(font6);
        horizontalLayout_2 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Step1_direct = new QLabel(layoutWidget7);
        Step1_direct->setObjectName(QString::fromUtf8("Step1_direct"));
        sizePolicy1.setHeightForWidth(Step1_direct->sizePolicy().hasHeightForWidth());
        Step1_direct->setSizePolicy(sizePolicy1);
        Step1_direct->setFont(font2);
        Step1_direct->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Step1_direct);

        Step2_direct = new QLabel(layoutWidget7);
        Step2_direct->setObjectName(QString::fromUtf8("Step2_direct"));
        sizePolicy1.setHeightForWidth(Step2_direct->sizePolicy().hasHeightForWidth());
        Step2_direct->setSizePolicy(sizePolicy1);
        Step2_direct->setFont(font2);
        Step2_direct->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Step2_direct);

        Step3_direct = new QLabel(layoutWidget7);
        Step3_direct->setObjectName(QString::fromUtf8("Step3_direct"));
        sizePolicy1.setHeightForWidth(Step3_direct->sizePolicy().hasHeightForWidth());
        Step3_direct->setSizePolicy(sizePolicy1);
        Step3_direct->setFont(font2);
        Step3_direct->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Step3_direct);

        Step4_direct = new QLabel(layoutWidget7);
        Step4_direct->setObjectName(QString::fromUtf8("Step4_direct"));
        sizePolicy1.setHeightForWidth(Step4_direct->sizePolicy().hasHeightForWidth());
        Step4_direct->setSizePolicy(sizePolicy1);
        Step4_direct->setFont(font2);
        Step4_direct->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Step4_direct);

        Step5_direct = new QLabel(layoutWidget7);
        Step5_direct->setObjectName(QString::fromUtf8("Step5_direct"));
        sizePolicy1.setHeightForWidth(Step5_direct->sizePolicy().hasHeightForWidth());
        Step5_direct->setSizePolicy(sizePolicy1);
        Step5_direct->setFont(font2);
        Step5_direct->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Step5_direct);

        Step6_direct = new QLabel(layoutWidget7);
        Step6_direct->setObjectName(QString::fromUtf8("Step6_direct"));
        sizePolicy1.setHeightForWidth(Step6_direct->sizePolicy().hasHeightForWidth());
        Step6_direct->setSizePolicy(sizePolicy1);
        Step6_direct->setFont(font2);
        Step6_direct->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Step6_direct);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        enR1 = new QLabel(layoutWidget7);
        enR1->setObjectName(QString::fromUtf8("enR1"));
        sizePolicy4.setHeightForWidth(enR1->sizePolicy().hasHeightForWidth());
        enR1->setSizePolicy(sizePolicy4);
        enR1->setFont(font2);
        enR1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(enR1);

        enR2 = new QLabel(layoutWidget7);
        enR2->setObjectName(QString::fromUtf8("enR2"));
        sizePolicy4.setHeightForWidth(enR2->sizePolicy().hasHeightForWidth());
        enR2->setSizePolicy(sizePolicy4);
        enR2->setFont(font2);
        enR2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(enR2);

        enR3 = new QLabel(layoutWidget7);
        enR3->setObjectName(QString::fromUtf8("enR3"));
        sizePolicy4.setHeightForWidth(enR3->sizePolicy().hasHeightForWidth());
        enR3->setSizePolicy(sizePolicy4);
        enR3->setFont(font2);
        enR3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(enR3);

        enR4 = new QLabel(layoutWidget7);
        enR4->setObjectName(QString::fromUtf8("enR4"));
        sizePolicy4.setHeightForWidth(enR4->sizePolicy().hasHeightForWidth());
        enR4->setSizePolicy(sizePolicy4);
        enR4->setFont(font2);
        enR4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(enR4);

        enR5 = new QLabel(layoutWidget7);
        enR5->setObjectName(QString::fromUtf8("enR5"));
        sizePolicy4.setHeightForWidth(enR5->sizePolicy().hasHeightForWidth());
        enR5->setSizePolicy(sizePolicy4);
        enR5->setFont(font2);
        enR5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(enR5);

        enR6 = new QLabel(layoutWidget7);
        enR6->setObjectName(QString::fromUtf8("enR6"));
        sizePolicy4.setHeightForWidth(enR6->sizePolicy().hasHeightForWidth());
        enR6->setSizePolicy(sizePolicy4);
        enR6->setFont(font2);
        enR6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(enR6);


        horizontalLayout_2->addLayout(verticalLayout_4);

        splitter_3->addWidget(layoutWidget7);
        layoutWidget8 = new QWidget(splitter_3);
        layoutWidget8->setObjectName(QString::fromUtf8("layoutWidget8"));
        layoutWidget8->setFont(font6);
        horizontalLayout_3 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        encrease1 = new QLabel(layoutWidget8);
        encrease1->setObjectName(QString::fromUtf8("encrease1"));
        sizePolicy1.setHeightForWidth(encrease1->sizePolicy().hasHeightForWidth());
        encrease1->setSizePolicy(sizePolicy1);
        encrease1->setFont(font2);
        encrease1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_5->addWidget(encrease1);

        encrease2 = new QLabel(layoutWidget8);
        encrease2->setObjectName(QString::fromUtf8("encrease2"));
        sizePolicy1.setHeightForWidth(encrease2->sizePolicy().hasHeightForWidth());
        encrease2->setSizePolicy(sizePolicy1);
        encrease2->setFont(font2);
        encrease2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_5->addWidget(encrease2);

        encrease3 = new QLabel(layoutWidget8);
        encrease3->setObjectName(QString::fromUtf8("encrease3"));
        sizePolicy1.setHeightForWidth(encrease3->sizePolicy().hasHeightForWidth());
        encrease3->setSizePolicy(sizePolicy1);
        encrease3->setFont(font2);
        encrease3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrease3->setIndent(-1);

        verticalLayout_5->addWidget(encrease3);

        encrease4 = new QLabel(layoutWidget8);
        encrease4->setObjectName(QString::fromUtf8("encrease4"));
        sizePolicy1.setHeightForWidth(encrease4->sizePolicy().hasHeightForWidth());
        encrease4->setSizePolicy(sizePolicy1);
        encrease4->setFont(font2);
        encrease4->setScaledContents(false);
        encrease4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrease4->setMargin(0);

        verticalLayout_5->addWidget(encrease4);

        encrease5 = new QLabel(layoutWidget8);
        encrease5->setObjectName(QString::fromUtf8("encrease5"));
        sizePolicy1.setHeightForWidth(encrease5->sizePolicy().hasHeightForWidth());
        encrease5->setSizePolicy(sizePolicy1);
        encrease5->setFont(font2);
        encrease5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_5->addWidget(encrease5);

        encrease6 = new QLabel(layoutWidget8);
        encrease6->setObjectName(QString::fromUtf8("encrease6"));
        sizePolicy1.setHeightForWidth(encrease6->sizePolicy().hasHeightForWidth());
        encrease6->setSizePolicy(sizePolicy1);
        encrease6->setFont(font2);
        encrease6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_5->addWidget(encrease6);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        enEr1 = new QLabel(layoutWidget8);
        enEr1->setObjectName(QString::fromUtf8("enEr1"));
        sizePolicy4.setHeightForWidth(enEr1->sizePolicy().hasHeightForWidth());
        enEr1->setSizePolicy(sizePolicy4);
        enEr1->setFont(font2);
        enEr1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(enEr1);

        enEr2 = new QLabel(layoutWidget8);
        enEr2->setObjectName(QString::fromUtf8("enEr2"));
        sizePolicy4.setHeightForWidth(enEr2->sizePolicy().hasHeightForWidth());
        enEr2->setSizePolicy(sizePolicy4);
        enEr2->setFont(font2);
        enEr2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(enEr2);

        enEr3 = new QLabel(layoutWidget8);
        enEr3->setObjectName(QString::fromUtf8("enEr3"));
        sizePolicy4.setHeightForWidth(enEr3->sizePolicy().hasHeightForWidth());
        enEr3->setSizePolicy(sizePolicy4);
        enEr3->setFont(font2);
        enEr3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(enEr3);

        enEr4 = new QLabel(layoutWidget8);
        enEr4->setObjectName(QString::fromUtf8("enEr4"));
        sizePolicy4.setHeightForWidth(enEr4->sizePolicy().hasHeightForWidth());
        enEr4->setSizePolicy(sizePolicy4);
        enEr4->setFont(font2);
        enEr4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(enEr4);

        enEr5 = new QLabel(layoutWidget8);
        enEr5->setObjectName(QString::fromUtf8("enEr5"));
        sizePolicy4.setHeightForWidth(enEr5->sizePolicy().hasHeightForWidth());
        enEr5->setSizePolicy(sizePolicy4);
        enEr5->setFont(font2);
        enEr5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(enEr5);

        enEr6 = new QLabel(layoutWidget8);
        enEr6->setObjectName(QString::fromUtf8("enEr6"));
        sizePolicy4.setHeightForWidth(enEr6->sizePolicy().hasHeightForWidth());
        enEr6->setSizePolicy(sizePolicy4);
        enEr6->setFont(font2);
        enEr6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(enEr6);


        horizontalLayout_3->addLayout(verticalLayout_6);

        splitter_3->addWidget(layoutWidget8);

        verticalLayout_16->addWidget(splitter_3);

        splitter_4->addWidget(enRead);
        degRead = new QFrame(splitter_4);
        degRead->setObjectName(QString::fromUtf8("degRead"));
        degRead->setFrameShape(QFrame::StyledPanel);
        degRead->setFrameShadow(QFrame::Sunken);
        degRead->setLineWidth(2);
        verticalLayout_15 = new QVBoxLayout(degRead);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        label_5 = new QLabel(degRead);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font3);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_15->addWidget(label_5);

        splitter_2 = new QSplitter(degRead);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setChildrenCollapsible(false);
        layoutWidget9 = new QWidget(splitter_2);
        layoutWidget9->setObjectName(QString::fromUtf8("layoutWidget9"));
        layoutWidget9->setFont(font6);
        horizontalLayout_7 = new QHBoxLayout(layoutWidget9);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        teta1_dir = new QLabel(layoutWidget9);
        teta1_dir->setObjectName(QString::fromUtf8("teta1_dir"));
        sizePolicy1.setHeightForWidth(teta1_dir->sizePolicy().hasHeightForWidth());
        teta1_dir->setSizePolicy(sizePolicy1);
        teta1_dir->setFont(font2);
        teta1_dir->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(teta1_dir);

        teta2_dir = new QLabel(layoutWidget9);
        teta2_dir->setObjectName(QString::fromUtf8("teta2_dir"));
        sizePolicy1.setHeightForWidth(teta2_dir->sizePolicy().hasHeightForWidth());
        teta2_dir->setSizePolicy(sizePolicy1);
        teta2_dir->setFont(font2);
        teta2_dir->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(teta2_dir);

        teta3_dit = new QLabel(layoutWidget9);
        teta3_dit->setObjectName(QString::fromUtf8("teta3_dit"));
        sizePolicy1.setHeightForWidth(teta3_dit->sizePolicy().hasHeightForWidth());
        teta3_dit->setSizePolicy(sizePolicy1);
        teta3_dit->setFont(font2);
        teta3_dit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(teta3_dit);

        teta4_dit = new QLabel(layoutWidget9);
        teta4_dit->setObjectName(QString::fromUtf8("teta4_dit"));
        sizePolicy1.setHeightForWidth(teta4_dit->sizePolicy().hasHeightForWidth());
        teta4_dit->setSizePolicy(sizePolicy1);
        teta4_dit->setFont(font2);
        teta4_dit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(teta4_dit);

        teta5_dir = new QLabel(layoutWidget9);
        teta5_dir->setObjectName(QString::fromUtf8("teta5_dir"));
        sizePolicy1.setHeightForWidth(teta5_dir->sizePolicy().hasHeightForWidth());
        teta5_dir->setSizePolicy(sizePolicy1);
        teta5_dir->setFont(font2);
        teta5_dir->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(teta5_dir);

        teta6_dir = new QLabel(layoutWidget9);
        teta6_dir->setObjectName(QString::fromUtf8("teta6_dir"));
        sizePolicy1.setHeightForWidth(teta6_dir->sizePolicy().hasHeightForWidth());
        teta6_dir->setSizePolicy(sizePolicy1);
        teta6_dir->setFont(font2);
        teta6_dir->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(teta6_dir);


        horizontalLayout_7->addLayout(verticalLayout_8);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        thR1 = new QLabel(layoutWidget9);
        thR1->setObjectName(QString::fromUtf8("thR1"));
        sizePolicy4.setHeightForWidth(thR1->sizePolicy().hasHeightForWidth());
        thR1->setSizePolicy(sizePolicy4);
        thR1->setFont(font2);
        thR1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_11->addWidget(thR1);

        thR2 = new QLabel(layoutWidget9);
        thR2->setObjectName(QString::fromUtf8("thR2"));
        sizePolicy4.setHeightForWidth(thR2->sizePolicy().hasHeightForWidth());
        thR2->setSizePolicy(sizePolicy4);
        thR2->setFont(font2);
        thR2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_11->addWidget(thR2);

        thR3 = new QLabel(layoutWidget9);
        thR3->setObjectName(QString::fromUtf8("thR3"));
        sizePolicy4.setHeightForWidth(thR3->sizePolicy().hasHeightForWidth());
        thR3->setSizePolicy(sizePolicy4);
        thR3->setFont(font2);
        thR3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_11->addWidget(thR3);

        thR4 = new QLabel(layoutWidget9);
        thR4->setObjectName(QString::fromUtf8("thR4"));
        sizePolicy4.setHeightForWidth(thR4->sizePolicy().hasHeightForWidth());
        thR4->setSizePolicy(sizePolicy4);
        thR4->setFont(font2);
        thR4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_11->addWidget(thR4);

        thR5 = new QLabel(layoutWidget9);
        thR5->setObjectName(QString::fromUtf8("thR5"));
        sizePolicy4.setHeightForWidth(thR5->sizePolicy().hasHeightForWidth());
        thR5->setSizePolicy(sizePolicy4);
        thR5->setFont(font2);
        thR5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_11->addWidget(thR5);

        pinzaOpen = new QLabel(layoutWidget9);
        pinzaOpen->setObjectName(QString::fromUtf8("pinzaOpen"));
        sizePolicy4.setHeightForWidth(pinzaOpen->sizePolicy().hasHeightForWidth());
        pinzaOpen->setSizePolicy(sizePolicy4);
        pinzaOpen->setFont(font2);
        pinzaOpen->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_11->addWidget(pinzaOpen);


        horizontalLayout_7->addLayout(verticalLayout_11);

        splitter_2->addWidget(layoutWidget9);
        layoutWidget10 = new QWidget(splitter_2);
        layoutWidget10->setObjectName(QString::fromUtf8("layoutWidget10"));
        layoutWidget10->setFont(font6);
        horizontalLayout_8 = new QHBoxLayout(layoutWidget10);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        encrease1_2 = new QLabel(layoutWidget10);
        encrease1_2->setObjectName(QString::fromUtf8("encrease1_2"));
        sizePolicy1.setHeightForWidth(encrease1_2->sizePolicy().hasHeightForWidth());
        encrease1_2->setSizePolicy(sizePolicy1);
        encrease1_2->setFont(font2);
        encrease1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_9->addWidget(encrease1_2);

        encrease2_2 = new QLabel(layoutWidget10);
        encrease2_2->setObjectName(QString::fromUtf8("encrease2_2"));
        sizePolicy1.setHeightForWidth(encrease2_2->sizePolicy().hasHeightForWidth());
        encrease2_2->setSizePolicy(sizePolicy1);
        encrease2_2->setFont(font2);
        encrease2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_9->addWidget(encrease2_2);

        encrease3_2 = new QLabel(layoutWidget10);
        encrease3_2->setObjectName(QString::fromUtf8("encrease3_2"));
        sizePolicy1.setHeightForWidth(encrease3_2->sizePolicy().hasHeightForWidth());
        encrease3_2->setSizePolicy(sizePolicy1);
        encrease3_2->setFont(font2);
        encrease3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrease3_2->setIndent(-1);

        verticalLayout_9->addWidget(encrease3_2);

        encrease4_2 = new QLabel(layoutWidget10);
        encrease4_2->setObjectName(QString::fromUtf8("encrease4_2"));
        sizePolicy1.setHeightForWidth(encrease4_2->sizePolicy().hasHeightForWidth());
        encrease4_2->setSizePolicy(sizePolicy1);
        encrease4_2->setFont(font2);
        encrease4_2->setScaledContents(false);
        encrease4_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrease4_2->setMargin(0);

        verticalLayout_9->addWidget(encrease4_2);

        encrease5_2 = new QLabel(layoutWidget10);
        encrease5_2->setObjectName(QString::fromUtf8("encrease5_2"));
        sizePolicy1.setHeightForWidth(encrease5_2->sizePolicy().hasHeightForWidth());
        encrease5_2->setSizePolicy(sizePolicy1);
        encrease5_2->setFont(font2);
        encrease5_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_9->addWidget(encrease5_2);

        encrease6_2 = new QLabel(layoutWidget10);
        encrease6_2->setObjectName(QString::fromUtf8("encrease6_2"));
        sizePolicy1.setHeightForWidth(encrease6_2->sizePolicy().hasHeightForWidth());
        encrease6_2->setSizePolicy(sizePolicy1);
        encrease6_2->setFont(font2);
        encrease6_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_9->addWidget(encrease6_2);


        horizontalLayout_8->addLayout(verticalLayout_9);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        thEr1 = new QLabel(layoutWidget10);
        thEr1->setObjectName(QString::fromUtf8("thEr1"));
        sizePolicy4.setHeightForWidth(thEr1->sizePolicy().hasHeightForWidth());
        thEr1->setSizePolicy(sizePolicy4);
        thEr1->setFont(font2);
        thEr1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_12->addWidget(thEr1);

        thEr2 = new QLabel(layoutWidget10);
        thEr2->setObjectName(QString::fromUtf8("thEr2"));
        sizePolicy4.setHeightForWidth(thEr2->sizePolicy().hasHeightForWidth());
        thEr2->setSizePolicy(sizePolicy4);
        thEr2->setFont(font2);
        thEr2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_12->addWidget(thEr2);

        thEr3 = new QLabel(layoutWidget10);
        thEr3->setObjectName(QString::fromUtf8("thEr3"));
        sizePolicy4.setHeightForWidth(thEr3->sizePolicy().hasHeightForWidth());
        thEr3->setSizePolicy(sizePolicy4);
        thEr3->setFont(font2);
        thEr3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_12->addWidget(thEr3);

        thEr4 = new QLabel(layoutWidget10);
        thEr4->setObjectName(QString::fromUtf8("thEr4"));
        sizePolicy4.setHeightForWidth(thEr4->sizePolicy().hasHeightForWidth());
        thEr4->setSizePolicy(sizePolicy4);
        thEr4->setFont(font2);
        thEr4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_12->addWidget(thEr4);

        thEr5 = new QLabel(layoutWidget10);
        thEr5->setObjectName(QString::fromUtf8("thEr5"));
        sizePolicy4.setHeightForWidth(thEr5->sizePolicy().hasHeightForWidth());
        thEr5->setSizePolicy(sizePolicy4);
        thEr5->setFont(font2);
        thEr5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_12->addWidget(thEr5);

        pinzaOpenErr = new QLabel(layoutWidget10);
        pinzaOpenErr->setObjectName(QString::fromUtf8("pinzaOpenErr"));
        sizePolicy4.setHeightForWidth(pinzaOpenErr->sizePolicy().hasHeightForWidth());
        pinzaOpenErr->setSizePolicy(sizePolicy4);
        pinzaOpenErr->setFont(font2);
        pinzaOpenErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_12->addWidget(pinzaOpenErr);


        horizontalLayout_8->addLayout(verticalLayout_12);

        splitter_2->addWidget(layoutWidget10);

        verticalLayout_15->addWidget(splitter_2);

        splitter_4->addWidget(degRead);
        curRead = new QFrame(splitter_4);
        curRead->setObjectName(QString::fromUtf8("curRead"));
        sizePolicy5.setHeightForWidth(curRead->sizePolicy().hasHeightForWidth());
        curRead->setSizePolicy(sizePolicy5);
        curRead->setBaseSize(QSize(0, 0));
        curRead->setFrameShape(QFrame::StyledPanel);
        curRead->setFrameShadow(QFrame::Sunken);
        curRead->setLineWidth(2);
        verticalLayout_14 = new QVBoxLayout(curRead);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        label_6 = new QLabel(curRead);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy5.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy5);
        label_6->setFont(font3);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(label_6);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setSizeConstraint(QLayout::SetFixedSize);
        ma1 = new QLabel(curRead);
        ma1->setObjectName(QString::fromUtf8("ma1"));
        ma1->setEnabled(true);
        sizePolicy1.setHeightForWidth(ma1->sizePolicy().hasHeightForWidth());
        ma1->setSizePolicy(sizePolicy1);
        ma1->setFont(font2);
        ma1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(ma1);

        ma2 = new QLabel(curRead);
        ma2->setObjectName(QString::fromUtf8("ma2"));
        ma2->setEnabled(true);
        sizePolicy1.setHeightForWidth(ma2->sizePolicy().hasHeightForWidth());
        ma2->setSizePolicy(sizePolicy1);
        ma2->setFont(font2);
        ma2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(ma2);

        ma3 = new QLabel(curRead);
        ma3->setObjectName(QString::fromUtf8("ma3"));
        sizePolicy1.setHeightForWidth(ma3->sizePolicy().hasHeightForWidth());
        ma3->setSizePolicy(sizePolicy1);
        ma3->setFont(font2);
        ma3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(ma3);

        ma4 = new QLabel(curRead);
        ma4->setObjectName(QString::fromUtf8("ma4"));
        sizePolicy1.setHeightForWidth(ma4->sizePolicy().hasHeightForWidth());
        ma4->setSizePolicy(sizePolicy1);
        ma4->setFont(font2);
        ma4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(ma4);

        ma5 = new QLabel(curRead);
        ma5->setObjectName(QString::fromUtf8("ma5"));
        sizePolicy1.setHeightForWidth(ma5->sizePolicy().hasHeightForWidth());
        ma5->setSizePolicy(sizePolicy1);
        ma5->setFont(font2);
        ma5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(ma5);

        ma6 = new QLabel(curRead);
        ma6->setObjectName(QString::fromUtf8("ma6"));
        sizePolicy1.setHeightForWidth(ma6->sizePolicy().hasHeightForWidth());
        ma6->setSizePolicy(sizePolicy1);
        ma6->setFont(font2);
        ma6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(ma6);


        horizontalLayout_9->addLayout(verticalLayout_10);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setSizeConstraint(QLayout::SetDefaultConstraint);
        mA1 = new QLabel(curRead);
        mA1->setObjectName(QString::fromUtf8("mA1"));
        QSizePolicy sizePolicy9(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(mA1->sizePolicy().hasHeightForWidth());
        mA1->setSizePolicy(sizePolicy9);
        mA1->setFont(font2);
        mA1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_13->addWidget(mA1);

        mA2 = new QLabel(curRead);
        mA2->setObjectName(QString::fromUtf8("mA2"));
        sizePolicy9.setHeightForWidth(mA2->sizePolicy().hasHeightForWidth());
        mA2->setSizePolicy(sizePolicy9);
        mA2->setFont(font2);
        mA2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_13->addWidget(mA2);

        mA3 = new QLabel(curRead);
        mA3->setObjectName(QString::fromUtf8("mA3"));
        sizePolicy9.setHeightForWidth(mA3->sizePolicy().hasHeightForWidth());
        mA3->setSizePolicy(sizePolicy9);
        mA3->setFont(font2);
        mA3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_13->addWidget(mA3);

        mA4 = new QLabel(curRead);
        mA4->setObjectName(QString::fromUtf8("mA4"));
        sizePolicy9.setHeightForWidth(mA4->sizePolicy().hasHeightForWidth());
        mA4->setSizePolicy(sizePolicy9);
        mA4->setFont(font2);
        mA4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_13->addWidget(mA4);

        mA5 = new QLabel(curRead);
        mA5->setObjectName(QString::fromUtf8("mA5"));
        sizePolicy9.setHeightForWidth(mA5->sizePolicy().hasHeightForWidth());
        mA5->setSizePolicy(sizePolicy9);
        mA5->setFont(font2);
        mA5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_13->addWidget(mA5);

        mA6 = new QLabel(curRead);
        mA6->setObjectName(QString::fromUtf8("mA6"));
        sizePolicy9.setHeightForWidth(mA6->sizePolicy().hasHeightForWidth());
        mA6->setSizePolicy(sizePolicy9);
        mA6->setFont(font2);
        mA6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_13->addWidget(mA6);


        horizontalLayout_9->addLayout(verticalLayout_13);


        verticalLayout_14->addLayout(horizontalLayout_9);

        splitter_4->addWidget(curRead);
        layoutWidget11 = new QWidget(centralwidget);
        layoutWidget11->setObjectName(QString::fromUtf8("layoutWidget11"));
        layoutWidget11->setGeometry(QRect(1030, 180, 65, 261));
        verticalLayout_22 = new QVBoxLayout(layoutWidget11);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        motPlot1 = new QCheckBox(layoutWidget11);
        motPlot1->setObjectName(QString::fromUtf8("motPlot1"));
        motPlot1->setChecked(true);

        verticalLayout_22->addWidget(motPlot1);

        motPlot2 = new QCheckBox(layoutWidget11);
        motPlot2->setObjectName(QString::fromUtf8("motPlot2"));
        motPlot2->setChecked(true);

        verticalLayout_22->addWidget(motPlot2);

        motPlot3 = new QCheckBox(layoutWidget11);
        motPlot3->setObjectName(QString::fromUtf8("motPlot3"));
        motPlot3->setChecked(true);

        verticalLayout_22->addWidget(motPlot3);

        motPlot4 = new QCheckBox(layoutWidget11);
        motPlot4->setObjectName(QString::fromUtf8("motPlot4"));
        motPlot4->setChecked(true);

        verticalLayout_22->addWidget(motPlot4);

        motPlot5 = new QCheckBox(layoutWidget11);
        motPlot5->setObjectName(QString::fromUtf8("motPlot5"));
        motPlot5->setChecked(true);

        verticalLayout_22->addWidget(motPlot5);

        motPlot6 = new QCheckBox(layoutWidget11);
        motPlot6->setObjectName(QString::fromUtf8("motPlot6"));
        motPlot6->setChecked(true);

        verticalLayout_22->addWidget(motPlot6);

        image = new QLabel(centralwidget);
        image->setObjectName(QString::fromUtf8("image"));
        image->setGeometry(QRect(150, 320, 91, 101));
        image->setStyleSheet(QString::fromUtf8(""));
        image->setPixmap(QPixmap(QString::fromUtf8(":/img/Logo2 small.png")));
        image->setScaledContents(true);
        layoutWidget12 = new QWidget(centralwidget);
        layoutWidget12->setObjectName(QString::fromUtf8("layoutWidget12"));
        layoutWidget12->setGeometry(QRect(250, 320, 164, 84));
        verticalLayout = new QVBoxLayout(layoutWidget12);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        sendRef = new QPushButton(layoutWidget12);
        sendRef->setObjectName(QString::fromUtf8("sendRef"));
        sendRef->setFont(font3);

        verticalLayout->addWidget(sendRef);

        goHome = new QPushButton(layoutWidget12);
        goHome->setObjectName(QString::fromUtf8("goHome"));
        goHome->setFont(font3);

        verticalLayout->addWidget(goHome);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1100, 25));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuUartSetting = new QMenu(menuBar);
        menuUartSetting->setObjectName(QString::fromUtf8("menuUartSetting"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
#if QT_CONFIG(shortcut)
        en1Label_3->setBuddy(en1Home);
        en2Label_3->setBuddy(en2Home);
        en3Label_3->setBuddy(en3Home);
        en4Label_3->setBuddy(en4Home);
        en5Label_3->setBuddy(en5Home);
        en6Label_3->setBuddy(en6Home);
        en1Label_4->setBuddy(en1Home);
        en2Label_4->setBuddy(en2Home);
        en3Label_4->setBuddy(en3Home);
        en4Label_4->setBuddy(en4Home);
        en5Label_4->setBuddy(en5Home);
        en6Label_4->setBuddy(en6Home);
        en1Label_5->setBuddy(en1Home);
        en2Label_5->setBuddy(en2Home);
        en3Label_5->setBuddy(en3Home);
        en1Label_6->setBuddy(en1Home);
        en2Label_6->setBuddy(en2Home);
        en6Label_5->setBuddy(en6Home);
        en1Label_2->setBuddy(en1Home);
        en2Label_2->setBuddy(en2Home);
        en3Label_2->setBuddy(en3Home);
        en4Label_2->setBuddy(en4Home);
        en5Label_2->setBuddy(en5Home);
        en6Label_2->setBuddy(en6Home);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(tabReference, en1Ref);
        QWidget::setTabOrder(en1Ref, en2Ref);
        QWidget::setTabOrder(en2Ref, en3Ref);
        QWidget::setTabOrder(en3Ref, en4Ref);
        QWidget::setTabOrder(en4Ref, en5Ref);
        QWidget::setTabOrder(en5Ref, en6Ref);
        QWidget::setTabOrder(en6Ref, thetaRef1);
        QWidget::setTabOrder(thetaRef1, thetaRef2);
        QWidget::setTabOrder(thetaRef2, thetaRef3);
        QWidget::setTabOrder(thetaRef3, thetaRef4);
        QWidget::setTabOrder(thetaRef4, thetaRef5);
        QWidget::setTabOrder(thetaRef5, pinzaRef);
        QWidget::setTabOrder(pinzaRef, xDes);
        QWidget::setTabOrder(xDes, yDes);
        QWidget::setTabOrder(yDes, zDes);
        QWidget::setTabOrder(zDes, betaDes);
        QWidget::setTabOrder(betaDes, omegaDes);
        QWidget::setTabOrder(omegaDes, gH);
        QWidget::setTabOrder(gH, gL);
        QWidget::setTabOrder(gL, en1Home);
        QWidget::setTabOrder(en1Home, en2Home);
        QWidget::setTabOrder(en2Home, en3Home);
        QWidget::setTabOrder(en3Home, en4Home);
        QWidget::setTabOrder(en4Home, en5Home);
        QWidget::setTabOrder(en5Home, en6Home);
        QWidget::setTabOrder(en6Home, l1Robot);
        QWidget::setTabOrder(l1Robot, l2Robot);
        QWidget::setTabOrder(l2Robot, l3Robot);
        QWidget::setTabOrder(l3Robot, d1Robot);
        QWidget::setTabOrder(d1Robot, d5Robot);
        QWidget::setTabOrder(d5Robot, alphaRobot);
        QWidget::setTabOrder(alphaRobot, betaRobot);
        QWidget::setTabOrder(betaRobot, gammaRobot);
        QWidget::setTabOrder(gammaRobot, deltaRobot);
        QWidget::setTabOrder(deltaRobot, sendRef);
        QWidget::setTabOrder(sendRef, scorBoardSetup);
        QWidget::setTabOrder(scorBoardSetup, controlSet);
        QWidget::setTabOrder(controlSet, freeMove);
        QWidget::setTabOrder(freeMove, motPlot1);
        QWidget::setTabOrder(motPlot1, motPlot2);
        QWidget::setTabOrder(motPlot2, motPlot3);
        QWidget::setTabOrder(motPlot3, motPlot4);
        QWidget::setTabOrder(motPlot4, motPlot5);
        QWidget::setTabOrder(motPlot5, motPlot6);

        menuBar->addAction(menuUartSetting->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuAbout->addSeparator();
        menuAbout->addAction(actionInfo);
        menuAbout->addSeparator();
        menuUartSetting->addAction(actionConnection_Start);
        menuUartSetting->addAction(actionClose_connection);
        menuUartSetting->addSeparator();
        menuUartSetting->addAction(actionReset_Board);

        retranslateUi(MainWindow);

        tabReference->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ScorbotConnect", nullptr));
        actionInfo->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
        serialPort->setText(QCoreApplication::translate("MainWindow", "Serial Port", nullptr));
        actionConnection_Start->setText(QCoreApplication::translate("MainWindow", "Connection Start", nullptr));
        actionReset_Board->setText(QCoreApplication::translate("MainWindow", "Reset Board", nullptr));
        actionClose_connection->setText(QCoreApplication::translate("MainWindow", "Close connection", nullptr));
        actionSerial_Find->setText(QCoreApplication::translate("MainWindow", "Serial Find", nullptr));
        actionB9600->setText(QCoreApplication::translate("MainWindow", "B9600", nullptr));
        actionB57600->setText(QCoreApplication::translate("MainWindow", "B57600", nullptr));
        actionB115200->setText(QCoreApplication::translate("MainWindow", "B115200", nullptr));
        actionB230400->setText(QCoreApplication::translate("MainWindow", "B230400", nullptr));
        actionB460800->setText(QCoreApplication::translate("MainWindow", "B460800", nullptr));
        actionB921600->setText(QCoreApplication::translate("MainWindow", "B921600", nullptr));
        valMinScr_3->setText(QCoreApplication::translate("MainWindow", "En Reference", nullptr));
        en1Label_3->setText(QCoreApplication::translate("MainWindow", "En 1", nullptr));
        en2Label_3->setText(QCoreApplication::translate("MainWindow", "En 2", nullptr));
        en3Label_3->setText(QCoreApplication::translate("MainWindow", "En 3", nullptr));
        en4Label_3->setText(QCoreApplication::translate("MainWindow", "En 4", nullptr));
        en5Label_3->setText(QCoreApplication::translate("MainWindow", "En 5", nullptr));
        en6Label_3->setText(QCoreApplication::translate("MainWindow", "En 6", nullptr));
        tabReference->setTabText(tabReference->indexOf(Direct), QCoreApplication::translate("MainWindow", "Dir en", nullptr));
        valMinScr_4->setText(QCoreApplication::translate("MainWindow", "Angle Reference [\302\260]", nullptr));
        en1Label_4->setText(QCoreApplication::translate("MainWindow", "\316\2701", nullptr));
        en2Label_4->setText(QCoreApplication::translate("MainWindow", "\316\2702", nullptr));
        en3Label_4->setText(QCoreApplication::translate("MainWindow", "\316\2703", nullptr));
        en4Label_4->setText(QCoreApplication::translate("MainWindow", "\316\2704", nullptr));
        en5Label_4->setText(QCoreApplication::translate("MainWindow", "\316\2705", nullptr));
        en6Label_4->setText(QCoreApplication::translate("MainWindow", "Pinza %", nullptr));
        tabReference->setTabText(tabReference->indexOf(Direct_Angular), QCoreApplication::translate("MainWindow", "Dir deg", nullptr));
        valMinScr_5->setText(QCoreApplication::translate("MainWindow", "Pos desiderata", nullptr));
        en1Label_5->setText(QCoreApplication::translate("MainWindow", "Xdes", nullptr));
        en2Label_5->setText(QCoreApplication::translate("MainWindow", "Ydes", nullptr));
        en3Label_5->setText(QCoreApplication::translate("MainWindow", "Zdes", nullptr));
        valMinScr_6->setText(QCoreApplication::translate("MainWindow", "Orientamento [\302\260]", nullptr));
        en1Label_6->setText(QCoreApplication::translate("MainWindow", "\316\262d", nullptr));
        en2Label_6->setText(QCoreApplication::translate("MainWindow", "\317\211d", nullptr));
        en6Label_5->setText(QCoreApplication::translate("MainWindow", "Pinza %", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Gomito", nullptr));
        gH->setText(QCoreApplication::translate("MainWindow", "Alto", nullptr));
        gL->setText(QCoreApplication::translate("MainWindow", "Basso", nullptr));
        tabReference->setTabText(tabReference->indexOf(Inverse), QCoreApplication::translate("MainWindow", "Inv", nullptr));
        valMinScr_2->setText(QCoreApplication::translate("MainWindow", "Home offset", nullptr));
        en1Label_2->setText(QCoreApplication::translate("MainWindow", "En 1", nullptr));
        en2Label_2->setText(QCoreApplication::translate("MainWindow", "En 2", nullptr));
        en3Label_2->setText(QCoreApplication::translate("MainWindow", "En 3", nullptr));
        en4Label_2->setText(QCoreApplication::translate("MainWindow", "En 4", nullptr));
        en5Label_2->setText(QCoreApplication::translate("MainWindow", "En 5", nullptr));
        en6Label_2->setText(QCoreApplication::translate("MainWindow", "En 6", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Robot Size", nullptr));
        l1Label->setText(QCoreApplication::translate("MainWindow", "L1", nullptr));
        l2Label->setText(QCoreApplication::translate("MainWindow", "L2", nullptr));
        l3Label->setText(QCoreApplication::translate("MainWindow", "L3", nullptr));
        l4Label->setText(QCoreApplication::translate("MainWindow", "d1", nullptr));
        l5Label->setText(QCoreApplication::translate("MainWindow", "d5", nullptr));
        scorSwHome->setText(QCoreApplication::translate("MainWindow", "SW Home", nullptr));
#if QT_CONFIG(tooltip)
        label_2->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Costanti\n"
"                                             per\n"
"                                             ottenere Radianti</p></body></html>\n"
"                                         ", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("MainWindow", "En \342\206\243 Rad", nullptr));
        aLabel->setText(QCoreApplication::translate("MainWindow", "\316\261", nullptr));
        bLabel->setText(QCoreApplication::translate("MainWindow", "\316\262", nullptr));
        cLabel->setText(QCoreApplication::translate("MainWindow", "\316\263", nullptr));
        dLabel->setText(QCoreApplication::translate("MainWindow", "\316\264", nullptr));
        scorParamLoad->setText(QCoreApplication::translate("MainWindow", "Load Parameter", nullptr));
        scorParamReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        tabReference->setTabText(tabReference->indexOf(RoboSetup), QCoreApplication::translate("MainWindow", "Robot Setup", nullptr));
        scorBoardSetup->setText(QCoreApplication::translate("MainWindow", "Board Setting", nullptr));
        controlSet->setText(QCoreApplication::translate("MainWindow", "Controll Setting", nullptr));
        freeMove->setText(QCoreApplication::translate("MainWindow", "Free move", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Pinza Pos", nullptr));
        Xattuale->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        Yattuale->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        Zattuale->setText(QCoreApplication::translate("MainWindow", "Z:", nullptr));
        en1Label_7->setText(QCoreApplication::translate("MainWindow", "\316\262", nullptr));
        en2Label_7->setText(QCoreApplication::translate("MainWindow", "\317\211", nullptr));
        xRead->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        yRead->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        zRead->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        betaRead->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        omegaRead->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        encrease1_3->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease2_3->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease3_3->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease3_5->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease3_4->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        xEr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        yEr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        zEr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        betaEr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        omegaEr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Pinza", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "En Read", nullptr));
        Step1_direct->setText(QCoreApplication::translate("MainWindow", "En 1", nullptr));
        Step2_direct->setText(QCoreApplication::translate("MainWindow", "En 2", nullptr));
        Step3_direct->setText(QCoreApplication::translate("MainWindow", "En 3", nullptr));
        Step4_direct->setText(QCoreApplication::translate("MainWindow", "En 4", nullptr));
        Step5_direct->setText(QCoreApplication::translate("MainWindow", "En 5", nullptr));
        Step6_direct->setText(QCoreApplication::translate("MainWindow", "En 6", nullptr));
        enR1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enR2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enR3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enR4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enR5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enR6->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        encrease1->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease2->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease3->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease4->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease5->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease6->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        enEr1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enEr2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enEr3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enEr4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enEr5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        enEr6->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Deg Read [\302\260]", nullptr));
        teta1_dir->setText(QCoreApplication::translate("MainWindow", "\316\2701:", nullptr));
        teta2_dir->setText(QCoreApplication::translate("MainWindow", "\316\2702:", nullptr));
        teta3_dit->setText(QCoreApplication::translate("MainWindow", "\316\2703:", nullptr));
        teta4_dit->setText(QCoreApplication::translate("MainWindow", "\316\2704:", nullptr));
        teta5_dir->setText(QCoreApplication::translate("MainWindow", "\316\2705:", nullptr));
        teta6_dir->setText(QCoreApplication::translate("MainWindow", "%P:", nullptr));
        thR1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thR2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thR3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thR4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thR5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pinzaOpen->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        encrease1_2->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease2_2->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease3_2->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease4_2->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease5_2->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        encrease6_2->setText(QCoreApplication::translate("MainWindow", "Error:", nullptr));
        thEr1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thEr2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thEr3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thEr4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        thEr5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pinzaOpenErr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Current Read", nullptr));
        ma1->setText(QCoreApplication::translate("MainWindow", "mA:", nullptr));
        ma2->setText(QCoreApplication::translate("MainWindow", "mA:", nullptr));
        ma3->setText(QCoreApplication::translate("MainWindow", "mA:", nullptr));
        ma4->setText(QCoreApplication::translate("MainWindow", "mA:", nullptr));
        ma5->setText(QCoreApplication::translate("MainWindow", "mA:", nullptr));
        ma6->setText(QCoreApplication::translate("MainWindow", "mA:", nullptr));
        mA1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        mA2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        mA3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        mA4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        mA5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        mA6->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        motPlot1->setText(QCoreApplication::translate("MainWindow", "Mot1", nullptr));
        motPlot2->setText(QCoreApplication::translate("MainWindow", "Mot2", nullptr));
        motPlot3->setText(QCoreApplication::translate("MainWindow", "Mot3", nullptr));
        motPlot4->setText(QCoreApplication::translate("MainWindow", "Mot4", nullptr));
        motPlot5->setText(QCoreApplication::translate("MainWindow", "Mot5", nullptr));
        motPlot6->setText(QCoreApplication::translate("MainWindow", "Mot6", nullptr));
#if QT_CONFIG(tooltip)
        image->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Developed by: Emanuele Alfano</p><p>alfystar1701@gmail.com</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        image->setText(QString());
        sendRef->setText(QCoreApplication::translate("MainWindow", "Send Reference", nullptr));
        goHome->setText(QCoreApplication::translate("MainWindow", "Go home", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
        menuUartSetting->setTitle(QCoreApplication::translate("MainWindow", "UartSetting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
