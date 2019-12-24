#include "mainwindow.h"
#include "ui_source/ui_mainwindow.h" //classe generata dal file di designer in automatico dal cmake

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    // My Ui
    ui->setupUi(this);
    //todo: imparare a usare il file .qrc
    ui->image->setPixmap(
            QPixmap("/home/alfyhack/Documenti/Scorbot-CA/2_uiSource/ScorbotUI_cpp/scorbotUi/ui_source/img/Logo-Uni-Tor-Vergata.png_256x256.png"));

    // Other Windows
    setBoardWin = new SettingBoardWindow(this);    //creo la finestra e la faccio mia figlia
    freeMovWin = new FreeMoveWindow(this);

    // Data get and send
    ref = new EncoderMot();
    feedBack = new AllSensor();

    // Function to call
//    this->ctrlFunx = extF->ctrlFunx;
//    this->setSendFunx = extF->setSendFunx;
//    this->setGetFunx = extF->setGetFunx;

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
    /// Button Signal
    connect(scorParamSet, SIGNAL (released()), this, SLOT (scorParamSet_handler()));
    connect(scorParamReset, SIGNAL (released()), this, SLOT (scorParamReset_handler()));
    connect(sendRef, SIGNAL (released()), this, SLOT (sendRef_handler()));
    connect(scorBoardSetup, SIGNAL (released()), this, SLOT (boardSet_handler()));
    connect(controlSet, SIGNAL (released()), this, SLOT (controllSet_handler()));
    connect(freeMove, SIGNAL (released()), this, SLOT (freeMove_handler()));
    /// Data change
    //dir en
    for (int i = Mot1; i < nMot; ++i) {
        connect(enRef[i], SIGNAL (valueChanged(int)), this, SLOT (cinCalc_handler()));
    }

    //dir deg
    for (int i = Mot1; i < nMot - 1; ++i) {
        connect(thetaRef[i], SIGNAL (valueChanged(double)), this, SLOT (cinCalc_handler()));
    }
    connect(pinzaRef, SIGNAL (valueChanged(int)), this, SLOT (cinCalc_handler()));
    //inv
    for (int i = 0; i < 3; ++i) {
        connect(pDes[i], SIGNAL (valueChanged(double)), this, SLOT (cinCalc_handler()));
    }
    for (int i = 0; i < 2; ++i) {
        connect(pOri[i], SIGNAL (valueChanged(double)), this, SLOT (cinCalc_handler()));
    }
    connect(pinzaInv, SIGNAL (valueChanged(int)), this, SLOT (cinCalc_handler()));
    for (int i = 0; i < 2; ++i) {
        connect(gomito[i], SIGNAL (toggled(bool)), this, SLOT (cinCalc_handler()));
    }


}

MainWindow::~MainWindow() {
    delete ui;
    delete setBoardWin;
    delete freeMovWin;
    /// Variabili fuznionali
    delete ref;
    delete feedBack;
}

void MainWindow::enSample(EncoderMot &en) {

}

void MainWindow::currSample(CurrentMot &cur) {

}

void MainWindow::controllSample(SpeedMot &speed) {

}

void MainWindow::sendRef_handler() {
    //todo: In base al tab selezionato calcola i valori per gli altri e invia gli encoder alla fine
    //è già stato chiamato cinCalc_handler() e ho tutti i dati in enRef
    for (char i = Mot1; i < nMot; i++) {
        ref->enSet((motCode) i, (short) enRef[i]->value());
    }
    ref->printEncoder();
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

void MainWindow::cinCalc_handler() {
    /// Disable all Signal to change data
    //dir en
    for (int i = Mot1; i < nMot; ++i)
        enRef[i]->blockSignals(true);
    //dir deg
    for (int i = Mot1; i < nMot - 1; ++i)
        thetaRef[i]->blockSignals(true);
    pinzaRef->blockSignals(true);
    //inv
    for (int i = 0; i < 3; ++i)
        pDes[i]->blockSignals(true);
    for (int i = 0; i < 2; ++i)
        pOri[i]->blockSignals(true);
    pinzaInv->blockSignals(true);
    for (int i = 0; i < 2; ++i)
        gomito[i]->blockSignals(true);
    switch (tabReference->currentIndex()) {
        case DirEn:
            //todo: Leggi i valori e calcola DirDeg e Inv
            break;
        case DirDeg:
            //todo: Leggi i valori e calcola DirEn e Inv
            break;
        case Inv:
            //todo: Leggi i valori e calcola DirEn e DirDeg
            break;
        case RobSet:
            //todo: Leggi i valori e calcola Inv, da lì DirEn e DirDeg
            break;
        default:
            std::cerr << "cinCalc_handler(), tap in Default:" << tabReference->currentIndex() << "\n";
            break;
    }

    /// Enable all Signal to change data
    //dir en
    for (int i = Mot1; i < nMot; ++i)
        enRef[i]->blockSignals(false);
    //dir deg
    for (int i = Mot1; i < nMot - 1; ++i)
        thetaRef[i]->blockSignals(false);
    pinzaRef->blockSignals(false);
    //inv
    for (int i = 0; i < 3; ++i)
        pDes[i]->blockSignals(false);
    for (int i = 0; i < 2; ++i)
        pOri[i]->blockSignals(false);
    pinzaInv->blockSignals(false);
    for (int i = 0; i < 2; ++i)
        gomito[i]->blockSignals(false);


}

void MainWindow::testPrint() {
    std::cout << "testPrint\n";
}
