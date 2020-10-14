//
// Created by alfyhack on 15/03/20.
// Classe preposta alla gestione della finestra per la scelta della seriale
//

#ifndef SCORBOTTERMINAL_UARTCONNECT_H
#define SCORBOTTERMINAL_UARTCONNECT_H

//qt
#include <QApplication>
#include <QAction>
#include <QtWidgets/QMessageBox>
#include "scorbotUi/mainwindow.h"
#include "scorbotUi/uartChoose.h"

//Exeption
#include <UartConnectExeption.h>

//scorInterface subsystem
#include <dataTransfert_AllInclude.h>
#include <uartSubSystem.h>

//linux
#include <iostream>
#include <unistd.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class UartConnect : public UartChoose{
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

private:
    ComUartAdapter *comUartAdapter = nullptr;
    std::string uartPath;
    UartChoose *uartChoise; //Gestore della finestara grafica

    MainWindow *win;    //Puntatore di ritorno per impostare le variabili

    /// Function to support Controll

public:
    ScorInterface *scorInterface = nullptr;
    //Prendo il riferimento alla finestra da controllare, e mi collego ai suoi segnali
    explicit UartConnect (MainWindow *parent = nullptr);
    ~UartConnect ();


    ///Controll Thread
signals:
    void uartMake ();

private slots:
    //    void serialPort_handler(QAction *action);
    //    void serialSearch_handler();
    void serialConnect_handler ();
    void uartChoised_handler ();
    void closeConnection_handler ();
    void resetBoard_handler ();
};

#endif //SCORBOTTERMINAL_UARTCONNECT_H
