//
// Created by alfyhack on 20/03/20.
//

#ifndef SCORBOTTERMINAL_MOTORCTRL_H
#define SCORBOTTERMINAL_MOTORCTRL_H

//qt
#include <QApplication>
#include "uiSrc/scorbotUi/mainwindow.h"
#include <QAction>
#include <QtWidgets/QMessageBox>

//Exeption
#include <UartConnectExeption.h>


//scorInterface subsystem
#include <DataTransfert_AllInclude.h>
#include <UartSubSystem.h>
#include <ConcreteObserver.h>
#include <PIDScorbot.h>

//linux
#include <iostream>
#include <unistd.h>
#include <QtWidgets/QToolButton>
#include <QtCore/QSignalMapper>

using namespace DataPrimitive;
using namespace DataManipolation;

//Responsabilità della classe è il controllo dei motori, siano essi in automatico mediante il controllo
//O attraverso il controllo diretto tramite l'interfaccia freeMoveCtrl
class MotorCTRL : public QObject {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    MainWindow *win;

    ScorInterface *scorInterface = nullptr;
    ConcreteObserver *obs = nullptr;

    std::thread *ctrlTh;      //Puntatore al Thread avviato
    EncoderMot *enObj;      //Todo: gestire possibili conflitti di concorrenza nel cambio dati e lettura
    PIDScorbot *pidM[nMot];

    bool goingToHome = false;

    QPushButton *mn[nMot];
    QPushButton *mp[nMot];
    QSignalMapper *signalMapper;

//    enum motPush {
//        Mot1n, Mot1p,
//        Mot2n, Mot2p,
//        Mot3n, Mot3p,
//        Mot4n, Mot4p,
//        Mot5n, Mot5p,
//        Mot6n, Mot6p,
//        nMotnp
//    };
    bool freeMoveCtrl = false;

public:
    MotorCTRL(MainWindow *parent);

private slots:

    void changeObj(EncoderMot *newObj);

    void goHome();

    void motorDirectControl(int push);

    void freeMoveWindowsShowing(bool show);


private:
    static void ctrlThMain(MotorCTRL *m);
};

#endif //SCORBOTTERMINAL_MOTORCTRL_H
