#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/// Qt lib
#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QRadioButton>

/// SystemLib
#include <DataTransfert_AllInclude.h>
#include <iostream>
#include "settingBoardWindow.h"
#include "freeMoveWinsow.h"
#include "commonDefine.h"
namespace Ui {
    class MainWindow; //Nome del windget radice nel file ui
}
using namespace DataPrimitive;
using namespace DataManipolation;

class MainWindow : public QMainWindow {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

public:
    explicit MainWindow(QWidget *parent = 0, struct extFooCall *extF = nullptr);
    ~MainWindow();
    // Data update
    void enSample(EncoderMot &en);
    void currSample(CurrentMot &cur);
    void controllSample(SpeedMot &speed);
private slots:
    // Data send
    void sendRef_handler();
    // Robot Setup
    void scorParamSet_handler();
    void scorParamReset_handler();
    // Other Windows
    void boardSet_handler();
    void controllSet_handler();
    void freeMove_handler();
    // Cin recalc
    void cinCalc_handler();


    void testPrint();
private:
    Ui::MainWindow *ui;
    SettingBoardWindow *setBoardWin;
    FreeMoveWindow *freeMovWin;

    /// Variabili funznionali
    EncoderMot *ref;
    AllSensor *feedBack;

    /// Funzioni di esportazione Comandi
    ctrlRefSendFoo ctrlFunx;
    SettingSendFoo setSendFunx;
    SettingGetFoo setGetFunx;

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

    /// Data send
    QPushButton *sendRef;

    ///Robot Setup
    QPushButton *scorParamSet;
    QPushButton *scorParamReset;

    ///External button
    QPushButton *scorBoardSetup;
    QPushButton *controlSet;
    QPushButton *freeMove;


};

#endif // MAINWINDOW_H
