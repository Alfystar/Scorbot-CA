//
// Created by alfyhack on 21/03/20.
//

#ifndef SCORBOTTERMINAL_SETUPBOARD_H
#define SCORBOTTERMINAL_SETUPBOARD_H

//qt
#include <QApplication>
#include <QAction>
#include <QtWidgets/QMessageBox>

//scorInterface subsystem
#include <DataTransfert_AllInclude.h>
#include <UartSubSystem.h>
#include <uiSrc/scorbotUi/mainwindow.h>
#include <uiSrc/scorbotUi/settingBoardWindow.h>
#include <ConcreteObserver.h>
//linux
#include <iostream>
#include <unistd.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class SetupBoard : public SettingBoardWindow {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    MainWindow *win;
    ScorInterface *scorInterface = nullptr;
public:
    SetupBoard(MainWindow *parent);
private slots:
    void settingBoardSend();
    void settingBoardLoad();
    void settingBoardRestored();
};

#endif //SCORBOTTERMINAL_SETUPBOARD_H
