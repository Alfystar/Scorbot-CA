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

using namespace DataPrimitive;
using namespace DataManipolation;

class MotorCTRL: public QObject {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    MainWindow *win;

    ScorInterface *scorInterface = nullptr;
    ConcreteObserver *obs = nullptr;

    std::thread *ctrlTh;      //Puntatore al Thread avviato
    EncoderMot *enObj;      //Todo: gestire possibili conflitti di concorrenza nel cambio dati e lettura
    PIDScorbot *pidM[nMot];

public:
    MotorCTRL(MainWindow *parent);

private slots:

    void changeObj(EncoderMot *newObj);

private:
    static void ctrlThMain(MotorCTRL *m);
};

#endif //SCORBOTTERMINAL_MOTORCTRL_H
