//
// Created by alfyhack on 15/03/20.
//

#include "UartConnect.h"
#include "scorbotUi/ui_source/ui_mainwindow.h" //classe generata dal file di designer in automatico dal cmake
#include "scorbotUi/ui_source/ui_uartChoose.h" //classe generata dal file di designer in automatico dal cmake

UartConnect::UartConnect (MainWindow *parent) : UartChoose(parent){

    this->win = parent;

    connect(win->ui->actionConnection_Start, SIGNAL (triggered()), this, SLOT (serialConnect_handler()));
    connect(win->ui->actionClose_connection, SIGNAL (triggered()), this, SLOT (closeConnection_handler()));
    win->ui->actionClose_connection->setDisabled(true);
    connect(win->ui->actionReset_Board, SIGNAL (triggered()), this, SLOT (resetBoard_handler()));
    connect(this, SIGNAL (uartChoised()), this, SLOT (uartChoised_handler()));
}

UartConnect::~UartConnect (){
}

void UartConnect::serialConnect_handler (){
    this->show();
}

void UartConnect::uartChoised_handler (){
    uartPath = this->ui->uartFind->currentText().toStdString();
    std::string speed = this->ui->speedChose->currentText().toStdString();
    std::cout << "[UartConnect::uartChoised_handler] " << uartPath << "\t" << speed << "\n";

    /// Comunicazione avvio
    try{
        comUartAdapter = &ComUartAdapter::getInstance();
        comUartAdapter->changeDevice(uartPath);
        if (speed.compare("B9600") == 0)
            comUartAdapter->changeDeviceVel(B9600);
        else if (speed.compare("B57600") == 0)
            comUartAdapter->changeDeviceVel(B57600);
        else if (speed.compare("B115200") == 0)
            comUartAdapter->changeDeviceVel(B115200);
        else if (speed.compare("B921600") == 0)
            comUartAdapter->changeDeviceVel(B921600);
    }catch (const std::exception &e){
        QMessageBox::warning(win, tr("Scorbot Connection"), tr(e.what()));
        return;
    }
    // Sul Firmware sono presenti delle velocità di default
    /// Notifica di avvio
    win->ui->actionConnection_Start->setDisabled(true);
    emit uartMake();
}

void UartConnect::closeConnection_handler (){
    std::cout << "[UartConnect::closeConnection_handler]" << "\n";
}

void UartConnect::resetBoard_handler (){
    std::cout << "[UartConnect::resetBoard_handler]" << "\n";
}
