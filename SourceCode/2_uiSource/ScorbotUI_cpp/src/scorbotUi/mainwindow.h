#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/// Qt lib
#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <qmath.h>

/// SystemLib
#include <DataTransfert_AllInclude.h>
#include <iostream>
#include "settingBoardWindow.h"
#include "freeMoveWinsow.h"
#include "commonDefine.h"
#include <ScorCalc.h>

namespace Ui {
    class MainWindow; //Nome del windget radice nel file ui
}
using namespace DataPrimitive;
using namespace DataManipolation;

class MainWindow : public QMainWindow {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

public:
    ScoreCalc *calc;

    //// #####################################################################
    /// Oggetti nel tabWindget
    /// Variabili funzionali
    EncoderMot *ref, *offset;
    AllSensor *feedBack;

    /// Riferimenti da inviare Qt
    //TabWindget
    QTabWidget *tabReference;
    enum tabRefName {
        DirEn, DirDeg, Inv, RobSet
    };
    //Diretta en
    QSpinBox *enRef[nMot];
    //Diretta angolata
    QDoubleSpinBox *thetaRef[nMot - 1];
    QSlider *pinzaRef;
    //Inversa
    QDoubleSpinBox *pDes[3];
    QDoubleSpinBox *pOri[2];
    QSlider *pinzaInv;
    QRadioButton *gomito[2];

//// #####################################################################
    /// Robot Parameter to conversion
    QSpinBox *enHome[nMot];

//// #####################################################################
    /// Oggetti di visualizzazione
    QLabel *enRead[nMot];
    QLabel *enReadErr[nMot];
    QLabel *thetaRead[nMot];
    QLabel *thetaReadErr[nMot];
    QLabel *curRead[nMot];


    SettingBoardWindow *setBoardWin;
    FreeMoveWindow *freeMovWin;

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void encoderShow();

    void encoderShow(EncoderMot *e);

    void encoderShow(EncoderMot *e, EncoderMot *off);

    void currentShow(CurrentMot *c);

    void SettingShow(SettingBoard_C *s);


signals:

    void newRef(EncoderMot *en);

private slots:

    // Data send
    void sendRef_handler();

    // Robot Setup
    void scorParamLoad_handler(); // Parametri dimensionali Scorbot
    void scorParamReset_handler(); // Parametri dimensionali Scorbot
    // Other Windows
    void boardSet_handler();

    void controllSet_handler();

    void freeMove_handler();

    // Cin recalc
    void cinCalc_handler();

public:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
