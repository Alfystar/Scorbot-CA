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

    connect(ui->actionInfo, SIGNAL (triggered()), this, SLOT (infoShow()));

    connect(uartConnect, SIGNAL(uartMake()), this, SLOT(connectionStartEvent()));

    this->statusBar()->showMessage("Avvio interfaccia");
}

ScorbotMainWindows::~ScorbotMainWindows() {

}


void ScorbotMainWindows::connectionStartEvent() {
    setupBoard->settingBoardLoad();
    this->statusBar()->showMessage("Connesione Stabilita");

}

void ScorbotMainWindows::infoShow() {
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowModality(Qt::NonModal);
    std::string s;
    s = "Programma sviluppato da:\n\t\tEmanuele Alfano\n\t\talfystar1701@gmail.com\n";
    s.append("Project repository:\n\thttps://github.com/Alfystar/Scorbot-CA\n");
    s.append("Interfaccia grafica dello ScorTerminal:\n\t\t\tV1.0\n");
    s.append("Interfaccia di comunicazione UART:\n\t\t\tV1.0\n");
    s.append("Protocollo di Comunicazione:\n\t\t\tV1.0\n");
    s.append("Verificare su un terminale seriale, se la Scheda ha un firmware compatibile");
    msgBox->setText(QString(s.data()));
    msgBox->setDefaultButton(QMessageBox::Ok);
    msgBox->show();

}
