//
// Created by alfyhack on 24/12/19.
//

#ifndef SCORBOTTERMINAL_QTSCORBOTUI_H
#define SCORBOTTERMINAL_QTSCORBOTUI_H

//qt
#include <QApplication>
#include "UI_useCase/scorbotUi/mainwindow.h"
#include <QAction>
#include <QtWidgets/QMessageBox>

//USE-Case Class
#include <UI_useCase/UartConnect.h>

//scorInterface subsystem
#include <PIDScorbot.h>
#include <dataTransfert_AllInclude.h>
#include <uartSubSystem.h>

//linux
#include <iostream>
#include <unistd.h>
#include <UI_useCase/MotorCTRL.h>
#include <UI_useCase/DataShow.h>
#include <UI_useCase/SetupBoard.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class QtScorbotUi : public MainWindow{
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

private:
    ScorInterface *scorbot;
    std::string uartPath;
    //Classi che gestiscono i vari UseCase:
    UartConnect *uartConnect;
    MotorCTRL *motCtrl;
    DataShow *dataShow;
    SetupBoard *setupBoard;

public:
    explicit QtScorbotUi (QWidget *parent = nullptr);
    ~QtScorbotUi ();

private slots:

    // Appena si instaura la connessione, fa da ponte e fa richiedere a setupBoard le impostazioni salvate nella scheda
    // così da far aggiornare ScorCalc con le variabili giuste
    void connectionStartEvent ();
    void infoShow ();
};

#endif //SCORBOTTERMINAL_QTSCORBOTUI_H
