//
// Created by alfyhack on 24/12/19.
//

#ifndef SCORBOTTERMINAL_SCORBOTMAINWINDOWS_H
#define SCORBOTTERMINAL_SCORBOTMAINWINDOWS_H

//qt
#include <QApplication>
#include "UI_useCase/uiSrc/scorbotUi/mainwindow.h"
#include <QAction>
#include <QtWidgets/QMessageBox>

//USE-Case Class
#include <UI_useCase/UartConnect.h>

//scorInterface subsystem
#include <PIDScorbot.h>
#include <DataTransfert_AllInclude.h>
#include <UartSubSystem.h>

//linux
#include <iostream>
#include <unistd.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class ScorbotMainWindows : public MainWindow {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

private:
    ScorInterface *scorbot;
    std::string uartPath;

/// Function to support Controll



public:
    explicit ScorbotMainWindows(QWidget *parent = nullptr);
    ~ScorbotMainWindows();

    ///Controll Thread
private:
    //Classi che gestiscono i vari UseCase:
    UartConnect *uartConnect;

    PIDScorbot *pidM[nMot];
    EncoderMot *enFeed; //Puntatore per i dati letti
    EncoderMot *refPid;
    std::mutex refMutex;    //Per evitare cambio di riferimenti incontrollato
    SpeedMot *pwm;
    std::thread *ctrl;


//    static void ctrlTh(ScorbotMainWindows *w);
private slots:

};

#endif //SCORBOTTERMINAL_SCORBOTMAINWINDOWS_H
