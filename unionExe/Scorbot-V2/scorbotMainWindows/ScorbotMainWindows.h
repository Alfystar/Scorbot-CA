//
// Created by alfyhack on 24/12/19.
//

#ifndef SCORBOTTERMINAL_SCORBOTMAINWINDOWS_H
#define SCORBOTTERMINAL_SCORBOTMAINWINDOWS_H

//qt
#include <QApplication>
#include "uiSrc/scorbotUi/mainwindow.h"
#include <QAction>
#include <QtWidgets/QMessageBox>


//scorbot subsystem
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
    explicit ScorbotMainWindows(QWidget *parent = 0);
    ~ScorbotMainWindows();

    ///Controll Thread
private:
    PIDScorbot *pidM[nMot];
    EncoderMot *enFeed; //Puntatore per i dati letti
    EncoderMot *refPid;
    std::mutex refMutex;    //Per evitare cambio di riferimenti incontrollato
    SpeedMot *pwm;
    std::thread *ctrl;
    static void ctrlTh(ScorbotMainWindows *w);
private slots:
    void serialPort_handler(QAction *action);
    void serialSearch_handler();
    void serialConnect_handler();
    void closeConnection_handler();
    void resetBoard_handler();

};

#endif //SCORBOTTERMINAL_SCORBOTMAINWINDOWS_H
