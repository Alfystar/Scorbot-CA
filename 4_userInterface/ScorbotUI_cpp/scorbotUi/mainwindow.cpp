#include "mainwindow.h"
#include "ui_source/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    /// Set important obj pointer to future use

    /// Riferimenti da inviare
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
    sendRef = ui->sendRef;
    connect(sendRef, SIGNAL (released()), this, SLOT (this->testPrint()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::testPrint() {
    std::cout << "testPrint\n";

}
