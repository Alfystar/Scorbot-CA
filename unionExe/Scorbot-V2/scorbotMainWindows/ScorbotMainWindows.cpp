//
// Created by alfyhack on 24/12/19.
//

#include "ScorbotMainWindows.h"
#include "UI_useCase/uiSrc/scorbotUi/ui_source/ui_mainwindow.h"      //classe generata dal file di designer in automatico dal cmake

ScorbotMainWindows::ScorbotMainWindows(QWidget *parent) : MainWindow(parent) {

    this->uartConnect = new UartConnect(this);  //Gli passo il riferimento ai miei oggetti
    this->motCtrl = new MotorCTRL(this);
    this->dataShow = new DataShow(this);
    this->setupBoard = new SetupBoard(this);
    this->statusBar()->showMessage("Avvio interfaccia");
}

ScorbotMainWindows::~ScorbotMainWindows() {

}