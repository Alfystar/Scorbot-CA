//
// Created by alfyhack on 20/03/20.
// Classe che attivamente cambia e gestisce le modalità di controllo dei motori
// Estende QObject per poter catturare i segnali generati dagli eventi sulla UI
//

#ifndef SCORBOTTERMINAL_MOTORCTRL_H
#define SCORBOTTERMINAL_MOTORCTRL_H

//qt
#include <QApplication>
#include "scorbotUi/mainwindow.h"
#include <QAction>
#include <QtWidgets/QMessageBox>

//Exeption
#include <UartConnectExeption.h>


//scorInterface subsystem
#include <dataTransfert_AllInclude.h>
#include <uartSubSystem.h>
#include <ConcreteObserver.h>

//Control
#include <ctrlSource.h>

//Linux
#include <iostream>
#include <unistd.h>
#include <QtWidgets/QToolButton>
#include <QtCore/QSignalMapper>




using namespace DataPrimitive;
using namespace DataManipolation;

//Responsabilità della classe è il controllo dei motori, siano essi in automatico mediante il controllo
//O attraverso il controllo diretto tramite l'interfaccia freeMoveCtrl
class MotorCTRL : public QObject{
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    MainWindow *win;
    ScorInterface *scorInterface = nullptr;
    ConcreteObserver *obs = nullptr;
    std::thread *ctrlTh;      //Puntatore al Thread avviato
    EncoderMot *enObj;

    QPushButton *mn[nMot];
    QPushButton *mp[nMot];
    QPushButton *roll[2];
    QPushButton *pitch[2];
    QSignalMapper *signalMapper;
    enum MotState{ controllMode, freeMode, stopMode };
    MotState motState = stopMode;


public:
    MotorCTRL (MainWindow *parent);

private slots:

    void changeObj (EncoderMot *newObj);
    void breakAllMot ();
    void goHome ();
    void freeMoveWindowsShowing (bool show);

private:
    [[noreturn]] static void ctrlThMain (MotorCTRL *m);
};

#endif //SCORBOTTERMINAL_MOTORCTRL_H
