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
#include <UI_useCase/MotorCTRL.h>
#include <UI_useCase/DataShow.h>
#include <UI_useCase/SetupBoard.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class ScorbotMainWindows : public MainWindow {
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
    explicit ScorbotMainWindows(QWidget *parent = nullptr);
    ~ScorbotMainWindows();

};

#endif //SCORBOTTERMINAL_SCORBOTMAINWINDOWS_H
