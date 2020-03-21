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
    calc = setBoardWin->getScorCalcSetuped();
    freeMovWin = new FreeMoveWindow(this);

    // Data get and send
    ref = new EncoderMot();
    feedBack = new AllSensor();


    ///##### Set important enObj pointer to future use #####///

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
    connect(scorParamSet, SIGNAL (released()), this, SLOT (scorParamSet_handler()));    // Parametri dimensionali Scorbot
    connect(scorParamReset, SIGNAL (released()), this, SLOT (scorParamReset_handler()));    // Parametri dimensionali Scorbot
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

    ///##########################################################
    enRead[Mot1] = ui->enR1;
    enRead[Mot2] = ui->enR2;
    enRead[Mot3] = ui->enR3;
    enRead[Mot4] = ui->enR4;
    enRead[Mot5] = ui->enR5;
    enRead[Mot6] = ui->enR6;

    thetaRead[Mot1] = ui->thR1;
    thetaRead[Mot2] = ui->thR2;
    thetaRead[Mot3] = ui->thR3;
    thetaRead[Mot4] = ui->thR4;
    thetaRead[Mot5] = ui->thR5;
    thetaRead[Mot6] = ui->PinzaOpen;

    curRead[Mot1] = ui->mA1;
    curRead[Mot2] = ui->mA2;
    curRead[Mot3] = ui->mA3;
    curRead[Mot4] = ui->mA4;
    curRead[Mot5] = ui->mA5;
    curRead[Mot6] = ui->mA6;
}

MainWindow::~MainWindow() {
    delete ui;
    delete setBoardWin;
    delete freeMovWin;
    /// Variabili fuznionali
    delete ref;
    delete feedBack;
}

void MainWindow::encoderShow(EncoderMot *e) {
    feedBack->copyEn(*e);
    for (int i = Mot1; i < nMot; ++i) {
        enRead[i]->setNum(feedBack->getEn((motCode)i));
        //todo: tramite scorCalc, convertire gli encoder letti in angoli
        thetaRead[i]->setNum(e->getEn((motCode)i));
    }

}

void MainWindow::currentShow(CurrentMot *c) {
    feedBack->copyCur(*c);
    for (int i = Mot1; i < nMot; ++i) {
        curRead[i]->setNum(feedBack->getCurrent((motCode)i));
    }
}




void MainWindow::sendRef_handler() {
    //todo: In base al tab selezionato calcola i valori per gli altri e invia gli encoder alla fine
    //è già stato chiamato cinCalc_handler() e ho tutti i dati in enRef
    for (char i = Mot1; i < nMot; i++) {
        ref->enSet((motCode) i, (short) enRef[i]->value());
    }
    emit newRef(ref);
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


