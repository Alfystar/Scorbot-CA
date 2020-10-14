//
// Created by alfyhack on 21/03/20.
// Classe che cattura gli eventi di invio e load dei setting della scheda dalla UI e li attua verso la board
//

#ifndef SCORBOTTERMINAL_SETUPBOARD_H
#define SCORBOTTERMINAL_SETUPBOARD_H

//qt
#include <QApplication>
#include <QAction>
#include <QtWidgets/QMessageBox>

//scorInterface subsystem
#include <dataTransfert_AllInclude.h>
#include <uartSubSystem.h>
#include <scorbotUi/mainwindow.h>
#include <scorbotUi/settingBoardWindow.h>
#include <ConcreteObserver.h>
//linux
#include <iostream>
#include <unistd.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class SetupBoard : public QObject{
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    MainWindow *win;
    ScorInterface *scorInterface = nullptr;
public:
    SetupBoard (MainWindow *parent);

public slots:

    void settingBoardSend ();
    void settingBoardLoad ();
    void settingBoardRestored ();
};

#endif //SCORBOTTERMINAL_SETUPBOARD_H
