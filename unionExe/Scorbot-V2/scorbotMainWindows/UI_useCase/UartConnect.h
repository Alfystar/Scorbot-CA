//
// Created by alfyhack on 15/03/20.
//

#ifndef SCORBOTTERMINAL_UARTCONNECT_H
#define SCORBOTTERMINAL_UARTCONNECT_H

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

//linux
#include <iostream>
#include <unistd.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class UartConnect : public QObject {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

private:
    ScorInterface *scorInterface = nullptr;
    std::string uartPath;

    MainWindow *win;

/// Function to support Controll

public:
    //Prendo il riferimento alla finestra da controllare, e mi collego ai suoi segnali
    explicit UartConnect(MainWindow *parent = nullptr);
    ~UartConnect();

    ScorInterface *getScorInterface() noexcept(false);

    ///Controll Thread
private:
private slots:
    void serialPort_handler(QAction *action);
    void serialSearch_handler();
    void serialConnect_handler();
    void closeConnection_handler();
    void resetBoard_handler();

};

#endif //SCORBOTTERMINAL_UARTCONNECT_H
