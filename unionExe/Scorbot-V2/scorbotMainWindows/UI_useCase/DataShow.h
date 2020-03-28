//
// Created by alfyhack on 21/03/20.
//

#ifndef SCORBOTTERMINAL_DATASHOW_H
#define SCORBOTTERMINAL_DATASHOW_H

//qt
#include <QApplication>
#include <QAction>
#include <QtWidgets/QMessageBox>

//scorInterface subsystem
#include <DataTransfert_AllInclude.h>
#include <UartSubSystem.h>
#include <uiSrc/scorbotUi/mainwindow.h>

#include <ConcreteObserver.h>
//linux
#include <iostream>
#include <unistd.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class DataShow : public QObject {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

    MainWindow *win;

    ScorInterface *scorInterface = nullptr;
    ConcreteObserver *obs = nullptr;

    EncoderMot *enOffset;

    std::thread *updateEnTh;
    std::thread *updateCurTh;

public:
    DataShow(MainWindow *parent);

    static void updateThEnMain(DataShow *d);

    static void updateThCurMain(DataShow *d);

private slots:

    void setHome_handler();

    void swHome_handler();

};

#endif //SCORBOTTERMINAL_DATASHOW_H
