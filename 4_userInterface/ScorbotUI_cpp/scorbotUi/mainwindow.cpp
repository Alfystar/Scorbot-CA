#include "mainwindow.h"
#include "ui_source/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setBoardWin = new SettingBoardWindow(this);    //creo la finestra e la faccio mia figlia
    freeMovWin = new FreeMoveWindow(this);

    ///##### Set important obj pointer to future use #####///

    /// Riferimenti da inviare
    tabReference = ui->tabReference;
    //Diretta en
    enRef[Mot1] = ui->en1Ref;
    enRef[Mot2] = ui->en2Ref;
    enRef[Mot3] = ui->en3Ref;
    enRef[Mot4] = ui->en4Ref;
    enRef[Mot5] = ui->en5Ref;
    enRef[Mot6] = ui->en6Ref;
    //Diretta angolata
    thetaRef[Mot1] = ui->thetaRef1;
    thetaRef[Mot2] = ui->thetaRef2;
    thetaRef[Mot3] = ui->thetaRef3;
    thetaRef[Mot4] = ui->thetaRef4;
    thetaRef[Mot5] = ui->thetaRef5;
    pinzaRef = ui->pinzaRef;
    //Inversa
    pDes[0] = ui->xDes;
    pDes[1] = ui->yDes;
    pDes[2] = ui->zDes;
    pOri[0] = ui->bdDes;
    pOri[1] = ui->wdDes;
    pinzaInv = ui->pinzaInv;
    gomito[0] = ui->gH;
    gomito[1] = ui->gL;
    //Button Inv
    scorParamSet = ui->scorParamSet;
    scorParamReset = ui->scorParamReset;

    //External button
    sendRef = ui->sendRef;
    scorBoardSetup = ui->scorBoardSetup;
    controlSet = ui->controlSet;
    freeMove = ui->freeMove;
    connect(scorParamSet, SIGNAL (released()), this, SLOT (scorParamSet_handler()));
    connect(scorParamReset, SIGNAL (released()), this, SLOT (scorParamReset_handler()));
    connect(sendRef, SIGNAL (released()), this, SLOT (sendRef_handler()));
    connect(scorBoardSetup, SIGNAL (released()), this, SLOT (boardSet_handler()));
    connect(controlSet, SIGNAL (released()), this, SLOT (controllSet_handler()));
    connect(freeMove, SIGNAL (released()), this, SLOT (freeMove_handler()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::sendRef_handler() {
    //todo: In base al tab selezionato calcola i valori per gli altri e invia gli encoder alla fine


}

void MainWindow::scorParamSet_handler() {

}

void MainWindow::scorParamReset_handler() {

}

void MainWindow::boardSet_handler() {
    setBoardWin->show();
}

void MainWindow::controllSet_handler() {

}

void MainWindow::freeMove_handler() {
    freeMovWin->show();
}

void MainWindow::testPrint() {
    std::cout << "testPrint\n";
}
