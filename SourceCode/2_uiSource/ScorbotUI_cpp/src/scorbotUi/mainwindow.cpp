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
    offset = new EncoderMot();
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

    // Robot Parameter
    enHome[Mot1] = ui->en1Home;
    enHome[Mot2] = ui->en2Home;
    enHome[Mot3] = ui->en3Home;
    enHome[Mot4] = ui->en4Home;
    enHome[Mot5] = ui->en5Home;
    enHome[Mot6] = ui->en6Home;

    /// Button Signal
    //Parameter Scorbot
    connect(ui->scorParamLoad, SIGNAL (released()), this,
            SLOT (scorParamLoad_handler()));    // Parametri dimensionali Scorbot da File System
    connect(ui->scorParamReset, SIGNAL (released()), this,
            SLOT (scorParamReset_handler()));    // Parametri dimensionali Scorbot

    //Encoder send
    connect(ui->sendRef, SIGNAL (released()), this, SLOT (sendRef_handler()));

    //External windows
    connect(ui->scorBoardSetup, SIGNAL (released()), this, SLOT (boardSet_handler()));
    connect(ui->controlSet, SIGNAL (released()), this, SLOT (controllSet_handler()));
    connect(ui->freeMove, SIGNAL (released()), this, SLOT (freeMove_handler()));
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

    enReadErr[Mot1] = ui->enEr1;
    enReadErr[Mot2] = ui->enEr2;
    enReadErr[Mot3] = ui->enEr3;
    enReadErr[Mot4] = ui->enEr4;
    enReadErr[Mot5] = ui->enEr5;
    enReadErr[Mot6] = ui->enEr6;


    thetaRead[Mot1] = ui->thR1;
    thetaRead[Mot2] = ui->thR2;
    thetaRead[Mot3] = ui->thR3;
    thetaRead[Mot4] = ui->thR4;
    thetaRead[Mot5] = ui->thR5;
    thetaRead[Mot6] = ui->pinzaOpen;

    thetaReadErr[Mot1] = ui->thEr1;
    thetaReadErr[Mot2] = ui->thEr2;
    thetaReadErr[Mot3] = ui->thEr3;
    thetaReadErr[Mot4] = ui->thEr4;
    thetaReadErr[Mot5] = ui->thEr5;
    thetaReadErr[Mot6] = ui->pinzaOpenErr;


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


void MainWindow::encoderShow() {
    mEncoder swEn, swEnErr;
    for (int i = Mot1; i < nMot; ++i) {
        swEn[i] = feedBack->getEn((motCode) i) - offset->getEn((motCode) i);
        enRead[i]->setNum(swEn[i]);
        swEnErr[i] = swEn[i] - ref->getEn((motCode) i);
        enReadErr[i]->setNum(swEnErr[i]);
    }

    //Conversion En --> Theta
    conParams par;
    par.alpha = ui->alphaRobot->value();
    par.beta = ui->betaRobot->value();
    par.gamma = ui->gammaRobot->value();
    par.delta = ui->deltaRobot->value();
    par.maxClaw = setBoardWin->setting->getSetting().maxEn[Mot6];
    thetaMot th, thErr;
    calc->en2th(swEn, th, &par);
    calc->en2th(swEnErr, thErr, &par);
    QString s;
    for (int i = Mot1; i < nMot; ++i) {
        s = s.setNum(th[i], 'f', 2);
        thetaRead[i]->setText(s);
        s = s.setNum(thErr[i], 'f', 2);
        thetaReadErr[i]->setText(s);
    }

    //Dir Cinematic
//    l1 = self.structVal[0].value()
//    l2 = self.structVal[1].value()
//    l3 = self.structVal[2].value()
//    d1 = self.structVal[3].value()
//    d5 = self.structVal[4].value()
//    betad = self.structVal[5].value()
//    omegad = self.structVal[6].value()
//
////# conversione degli angoli in radianti
//    t1r = math.radians(lista[0])
//    t2r = math.radians(lista[1])
//    t3r = math.radians(lista[2])
//    t4r = math.radians(lista[3])
//    t5r = math.radians(lista[4])
//# calcolo della posizione del polso
//    xpolso = math.cos(t1r) * (l1 + l2 * math.cos(t2r) + l3 * math.cos(t2r + t3r))
//    ypolso = math.sin(t1r) * (l1 + l2 * math.cos(t2r) + l3 * math.cos(t2r + t3r))
//    zpolso = d1 - l2 * math.sin(t2r) - l3 * math.sin(t2r + t3r)
//# calcolo della posizione della pinza(inserita direttamente nella lista)
//    ax.append(xpolso - math.cos(t1r) * d5 * math.sin(t2r + t3r + t4r))
//    ax.append(ypolso - math.sin(t1r) * d5 * math.sin(t2r + t3r + t4r))
//    ax.append(zpolso - d5 * math.cos(t2r + t3r + t4r))
//    return ax
}

void MainWindow::encoderShow(EncoderMot *e) {
    feedBack->copyEn(*e);
    encoderShow();

}

void MainWindow::encoderShow(EncoderMot *e, EncoderMot *off) {
    feedBack->copyEn(*e);
    offset->copyEn(*off);
    encoderShow();
}

void MainWindow::currentShow(CurrentMot *c) {
    feedBack->copyCur(*c);
    for (int i = Mot1; i < nMot; ++i) {
        curRead[i]->setNum(feedBack->getCurrent((motCode) i));
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

void MainWindow::scorParamLoad_handler() {
    //Far scegliere dei parametri di default tra quelli salvati nel file config

}

void MainWindow::scorParamReset_handler() {
    //Ripristinare i valori di avvio, in futuro da un file config di defautl
    ui->l1Robot->setValue(5.0);
    ui->l2Robot->setValue(22.0);
    ui->l3Robot->setValue(22.0);
    ui->d1Robot->setValue(2.0);
    ui->d5Robot->setValue(3.0);

    ui->alphaRobot->setValue(0.41);
    ui->betaRobot->setValue(0.2);
    ui->gammaRobot->setValue(0.3);
    ui->deltaRobot->setValue(0.4);

    for (int i = 0; i < nMot; ++i) {
        enHome[i]->setValue(0);
    }
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


