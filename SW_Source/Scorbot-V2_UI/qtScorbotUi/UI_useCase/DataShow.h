//
// Created by alfyhack on 21/03/20.
// Classe che attivamente resta in ascolto per aggiornare encoder e corrente all'interno della UI
//

#ifndef SCORBOTTERMINAL_DATASHOW_H
#define SCORBOTTERMINAL_DATASHOW_H

//qt
#include <QApplication>
#include <QAction>
#include <QtWidgets/QMessageBox>

//scorInterface subsystem
#include <dataTransfert_AllInclude.h>
#include <uartSubSystem.h>
#include <scorbotUi/mainwindow.h>

#include <ConcreteObserver.h>
//linux
#include <iostream>
#include <unistd.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class DataShow : public QObject{
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    MainWindow *win;
    ScorInterface *scorInterface = nullptr;
    ConcreteObserver *obs = nullptr;
    EncoderMot *enOffset;
    std::thread *updateEnTh;
    std::thread *updateCurTh;

public:
    DataShow (MainWindow *parent);
    [[noreturn]] static void updateThEnMain (DataShow *d);
    [[noreturn]] static void updateThCurMain (DataShow *d);

private slots:

    void setHome_handler ();
    void swHome_handler ();
};

#endif //SCORBOTTERMINAL_DATASHOW_H
