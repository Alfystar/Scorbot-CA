#include "mainwindow.h"
#include "ui_source/ui_mainwindow.h" //classe generata dal file di designer in automatico dal cmake

MainWindow::MainWindow (QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    Q_INIT_RESOURCE(imgs);

    // My Ui
    ui->setupUi(this);

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
    pOri[0] = ui->betaDes;
    pOri[1] = ui->omegaDes;
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

    motPlot[Mot1] = ui->motPlot1;
    motPlot[Mot2] = ui->motPlot2;
    motPlot[Mot3] = ui->motPlot3;
    motPlot[Mot4] = ui->motPlot4;
    motPlot[Mot5] = ui->motPlot5;
    motPlot[Mot6] = ui->motPlot6;

    tabReference->setCurrentIndex(0);
    ///##########################################################


    ui->plot->legend->setVisible(true);
    ui->plot->legend->setFont(QFont("Helvetica", 9));
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft |
                                                              Qt::AlignTop); // make legend align in top left corner or axis rect
    QPen pen;
    QColor color;

    /// Graph line add:
    color.setHsv(0, 255, 255);        //rosso
    pen.setColor(color);
    pen.setWidth(3);

    ui->plot->addGraph();   //Aggiungo la linea per il Mot1 Encoder
    ui->plot->graph()->setPen(pen);
    ui->plot->graph()->setName("Mot1_mA");
    ui->plot->graph()->setLineStyle(QCPGraph::lsStepLeft);

    color.setHsv(35, 255, 255);       //arancione
    pen.setColor(color);
    ui->plot->addGraph();   //Aggiungo la linea per il Mot1 Encoder
    ui->plot->graph()->setPen(pen);
    ui->plot->graph()->setName("Mot2_mA");
    ui->plot->graph()->setLineStyle(QCPGraph::lsStepLeft);

    color.setHsv(100, 255, 255);      //verde
    pen.setColor(color);
    ui->plot->addGraph();   //Aggiungo la linea per il Mot1 Encoder
    ui->plot->graph()->setPen(pen);
    ui->plot->graph()->setName("Mot3_mA");
    ui->plot->graph()->setLineStyle(QCPGraph::lsStepLeft);

    color.setHsv(200, 255, 255);      //azzurro
    pen.setColor(color);
    ui->plot->addGraph();   //Aggiungo la linea per il Mot1 Encoder
    ui->plot->graph()->setPen(pen);
    ui->plot->graph()->setName("Mot4_mA");
    ui->plot->graph()->setLineStyle(QCPGraph::lsStepLeft);

    color.setHsv(250, 255, 255);      //Blu
    pen.setColor(color);
    ui->plot->addGraph();   //Aggiungo la linea per il Mot1 Encoder
    ui->plot->graph()->setPen(pen);
    ui->plot->graph()->setName("Mot5_mA");
    ui->plot->graph()->setLineStyle(QCPGraph::lsStepLeft);

    color.setHsv(280, 255, 255);      //Viola
    pen.setColor(color);
    ui->plot->addGraph();   //Aggiungo la linea per il Mot1 Encoder
    ui->plot->graph()->setPen(pen);
    ui->plot->graph()->setName("Mot6_mA");
    ui->plot->graph()->setLineStyle(QCPGraph::lsStepLeft);

    ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
    ui->plot->xAxis->scaleRange(1.1, ui->plot->xAxis->range().center());
    // set blank axis lines:
    ui->plot->xAxis->setTicks(true);
    ui->plot->yAxis->setTicks(true);
    ui->plot->xAxis->setTickLabels(true);
    ui->plot->yAxis->setTickLabels(true);

    ///##########################################################

    /// Button Signal
    //Parameter Scorbot
    connect(ui->scorParamLoad, SIGNAL (released()), this,
            SLOT (scorParamLoad_handler()));    // Parametri dimensionali Scorbot da File System
    connect(ui->scorParamReset, SIGNAL (released()), this,
            SLOT (scorParamReset_handler()));    // Parametri dimensionali Scorbot

    //Encoder send
    connect(ui->sendRef, SIGNAL (released()), this, SLOT (sendRef_handler()));
    connect(ui->breakSign, SIGNAL (released()), this, SLOT (breakSig_handler()));

    //External windows
    connect(ui->scorBoardSetup, SIGNAL (released()), this, SLOT (boardSet_handler()));
    connect(ui->controlSet, SIGNAL (released()), this, SLOT (controllSet_handler()));
    connect(ui->freeMove, SIGNAL (released()), this, SLOT (freeMove_handler()));


    /// Data change
    //dir en
    for (int i = Mot1; i < nMot; ++i){
        connect(enRef[i], SIGNAL (valueChanged(int)), this, SLOT (cinCalc_handler()));
    }

    //dir deg
    for (int i = Mot1; i < nMot - 1; ++i){
        connect(thetaRef[i], SIGNAL (valueChanged(double)), this, SLOT (cinCalc_handler()));
    }
    connect(pinzaRef, SIGNAL (valueChanged(int)), this, SLOT (cinCalc_handler()));
    //inv
    for (auto &pDe : pDes){
        connect(pDe, SIGNAL (valueChanged(double)), this, SLOT (cinCalc_handler()));
    }
    for (auto &i : pOri){
        connect(i, SIGNAL (valueChanged(double)), this, SLOT (cinCalc_handler()));
    }
    connect(pinzaInv, SIGNAL (valueChanged(int)), this, SLOT (cinCalc_handler()));
    for (auto &i : gomito){
        connect(i, SIGNAL (toggled(bool)), this, SLOT (cinCalc_handler()));
    }

    connect(this, SIGNAL (newEncoderShow()), this, SLOT (encoderShow()));
    connect(this, SIGNAL (newCurrentShow()), this, SLOT (currentShow()));
}

MainWindow::~MainWindow (){
    delete ui;
    delete setBoardWin;
    delete freeMovWin;
    /// Variabili fuznionali
    delete ref;
    delete feedBack;
    Q_CLEANUP_RESOURCE(imgs);
}

void MainWindow::encoderShow (){
    QString s;  // variabile utitly per impostare i numeri col giusto numero di cifre decimali

    mEncoder swEn, swObj, swEnErr;
    for (int i = Mot1; i < nMot; ++i){
        swEn[i] = feedBack->getEn((motCode) i) - offset->getEn((motCode) i);
        enRead[i]->setNum(swEn[i]);
        swObj[i] = ref->getEn((motCode) i);
        swEnErr[i] = swObj[i] - swEn[i];
        enReadErr[i]->setNum(swEnErr[i]);
    }


    //Conversion En --> Theta
    thetaMot th, thObj, thErr;
    conParamsUpdate();
    calc->en2th(swEn, th, &par);
    calc->en2th(swObj, thObj, &par);
    //    calc->en2th(swEnErr, thErr, &par);
    for (int i = Mot1; i < nMot; ++i){
        s = s.setNum(qRadiansToDegrees(th[i]), 'f', 2);
        thetaRead[i]->setText(s);
        thErr[i] = th[i] - thObj[i];
        s = s.setNum(qRadiansToDegrees(thErr[i]), 'f', 2);
        thetaReadErr[i]->setText(s);
    }

    positionRobot pos, posObj;
    geometryRobotUpdate();
    // Tetha --> claw position now
    calc->dirCin(th, &pos, &g);

    s = s.setNum(pos.x, 'f', 2);
    ui->xRead->setText(s);

    s = s.setNum(pos.y, 'f', 2);
    ui->yRead->setText(s);

    s = s.setNum(pos.z, 'f', 2);
    ui->zRead->setText(s);

    s = s.setNum(qRadiansToDegrees(pos.beta), 'f', 2);
    ui->betaRead->setText(s);

    s = s.setNum(qRadiansToDegrees(pos.omega), 'f', 2);
    ui->omegaRead->setText(s);

    int value = (int) (th[Mot6] * 100.0);
    if (value < 0)
        value = 0;
    if (value > 100)
        value = 100;
    ui->pinzaRead->setValue(value);

    // TethaObj && Theta now --> claw position error
    calc->dirCin(thObj, &posObj, &g);

    s = s.setNum(posObj.x - pos.x, 'f', 2);
    ui->xEr->setText(s);

    s = s.setNum(posObj.y - pos.y, 'f', 2);
    ui->yEr->setText(s);

    s = s.setNum(posObj.z - pos.z, 'f', 2);
    ui->zEr->setText(s);

    s = s.setNum(qRadiansToDegrees(posObj.beta - pos.beta), 'f', 2);
    ui->betaEr->setText(s);

    s = s.setNum(qRadiansToDegrees(posObj.omega - pos.omega), 'f', 2);
    ui->omegaEr->setText(s);
}

int j = 0;
#define graphSize 100

void MainWindow::currentShow (){
    float cur;
    j++;
    for (int i = Mot1; i < nMot; ++i){
        cur = calc->adc2curr(feedBack->getCurrent((motCode) i));
        curRead[i]->setNum(cur);
    }
    #ifdef PLOT_ON
    for (int i = Mot1; i < nMot; ++i){
        ui->plot->graph(i)->addData(j, cur);
        ui->plot->graph(i)->data()->removeBefore(j - graphSize);
        ui->plot->graph(i)->rescaleAxes(true);
        ui->plot->graph(i)->setVisible(motPlot[i]->isChecked());
    }
    ui->plot->yAxis->rescale(true);
    //    ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
    ui->plot->xAxis->setRange(j, graphSize, Qt::AlignRight);
    ui->plot->replot();
    #endif
}

#undef graphSize

void MainWindow::conParamsUpdate (){
    par.alpha = ui->alphaRobot->value();
    par.beta = ui->betaRobot->value();
    par.gamma = ui->gammaRobot->value();
    par.delta = ui->deltaRobot->value();
    par.maxClaw = setBoardWin->setting->getSetting().maxEn[Mot6];
}

void MainWindow::geometryRobotUpdate (){
    g.l1 = ui->l1Robot->value();
    g.l2 = ui->l2Robot->value();
    g.l3 = ui->l3Robot->value();
    g.d1 = ui->d1Robot->value();
    g.d5 = ui->d5Robot->value();
}

void MainWindow::encoderShow (EncoderMot *e){
    feedBack->copyEn(*e);
    emit newEncoderShow();
}

void MainWindow::encoderShow (EncoderMot *e, EncoderMot *off){
    feedBack->copyEn(*e);
    offset->copyEn(*off);
    emit newEncoderShow();
}

void MainWindow::currentShow (CurrentMot *c){
    feedBack->copyCur(*c);
    emit newCurrentShow();
}

void MainWindow::sendRef_handler (){
    //è già stato chiamato cinCalc_handler() e ho tutti i dati aggiornati in enRef
    for (unsigned char i = Mot1; i < nMot; i++){
        ref->enSet((motCode) i, (short) enRef[i]->value());
    }
    ref->enAdd(*offset);
    emit newRef(ref);
}

void MainWindow::breakSig_handler (){
    std::cout << "[MainWindow::breakSig_handler]" << std::endl;
    emit breakSig();
}

void MainWindow::scorParamLoad_handler (){
    //Far scegliere dei parametri di default tra quelli salvati nel file config
    std::cout << "[MainWindow::scorParamLoad_handler]" << std::endl;

}

void MainWindow::scorParamReset_handler (){
    //Ripristinare i valori di avvio, in futuro da un file config di defautl
    ui->l1Robot->setValue(5.0);
    ui->l2Robot->setValue(22.0);
    ui->l3Robot->setValue(22.0);
    ui->d1Robot->setValue(2.0);
    ui->d5Robot->setValue(3.0);

    ui->alphaRobot->setValue(0.1);
    ui->betaRobot->setValue(0.1);
    ui->gammaRobot->setValue(0.1);
    ui->deltaRobot->setValue(0.1);

    for (int i = 0; i < nMot; ++i){
        enHome[i]->setValue(0);
    }
}

void MainWindow::boardSet_handler (){
    setBoardWin->show();
}

void MainWindow::controllSet_handler (){
}

void MainWindow::freeMove_handler (){
    freeMovWin->show();
}

void MainWindow::cinCalc_handler (){
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

    // Variabili di appoggio nei vari switch
    mEncoder en;
    thetaMot th;
    positionRobot pos;
    bool gom;

    conParamsUpdate();
    geometryRobotUpdate();
    switch (tabReference->currentIndex()){
        case DirEn: // Leggi i valori e calcola DirDeg e Inv
            //Creo il vettore dall'interfaccia grafica, degli encoder desiderati
            for (unsigned char i = Mot1; i < nMot; i++){
                en[i] = enRef[i]->value();
            }

            //Calcolo i theta equivalenti e li scrivo sull'intefaccia grafica
            calc->en2th(en, th, &par);
            for (int i = 0; i < Mot6; ++i){
                thetaRef[i]->setValue(qRadiansToDegrees(th[i]));
            }
            pinzaRef->setValue(th[Mot6] * 100);

            // Calcolo la cinematica Diretta e la scrivo sull'interfaccia grafica
            calc->dirCin(th, &pos, &g);
            ui->xDes->setValue(pos.x);
            ui->yDes->setValue(pos.y);
            ui->zDes->setValue(pos.z);
            ui->betaDes->setValue(qRadiansToDegrees(pos.beta));
            ui->omegaDes->setValue(qRadiansToDegrees(pos.omega));
            pinzaInv->setValue(pinzaRef->value());

            ui->gL->setAutoExclusive(false);
            ui->gL->setAutoExclusive(false);
            ui->gL->setChecked(false);
            ui->gH->setChecked(false);
            ui->gL->setAutoExclusive(true);
            ui->gH->setAutoExclusive(true);

            break;
        case DirDeg: // Leggi i valori e calcola DirEn e Inv
            //Creo il vettore dall'interfaccia grafica, dei theta desiderati
            for (int i = 0; i < Mot6; ++i){
                th[i] = qDegreesToRadians(thetaRef[i]->value());
            }
            th[Mot6] = pinzaRef->value() / 100.0;

            //Calcolo gli encoder equivalenti e li scrivo sull'intefaccia grafica
            calc->th2en(th, en, &par);
            for (unsigned char i = Mot1; i < nMot; i++){
                enRef[i]->setValue(en[i]);
            }

            // Calcolo la cinematica Diretta e la scrivo sull'interfaccia grafica
            calc->dirCin(th, &pos, &g);
            ui->xDes->setValue(pos.x);
            ui->yDes->setValue(pos.y);
            ui->zDes->setValue(pos.z);
            ui->betaDes->setValue(qRadiansToDegrees(pos.beta));
            ui->omegaDes->setValue(qRadiansToDegrees(pos.omega));
            pinzaInv->setValue(pinzaRef->value());

            ui->gL->setAutoExclusive(false);
            ui->gL->setAutoExclusive(false);
            ui->gL->setChecked(false);
            ui->gH->setChecked(false);
            ui->gL->setAutoExclusive(true);
            ui->gH->setAutoExclusive(true);
            break;
        case Inv: // Leggi i valori e calcola DirEn e DirDeg
        case RobSet: // Leggi i valori e calcola Inv, da lì DirEn e DirDeg
            //Creo il vettore dall'interfaccia grafica, delle coordinate desiderate e del gomito
            pos.x = ui->xDes->value();
            pos.y = ui->yDes->value();
            pos.z = ui->zDes->value();
            pos.beta = qDegreesToRadians(ui->betaDes->value());
            pos.omega = qDegreesToRadians(ui->omegaDes->value());
            if (!ui->gH->isChecked() && ui->gL->isChecked())
                ui->gH->setChecked(true);
            gom = ui->gH->isChecked(); //auto exlusive

            //Calcolo i theta equivalenti e li scrivo sull'intefaccia grafica
            calc->invCin(&pos, &g, gom, th);
            for (int i = 0; i < Mot6; ++i){
                thetaRef[i]->setValue(qRadiansToDegrees(th[i]));
            }
            pinzaRef->setValue(pinzaInv->value());
            th[Mot6] = pinzaInv->value() / 100.0;


            //Calcolo gli encoder equivalenti e li scrivo sull'intefaccia grafica
            calc->th2en(th, en, &par);
            for (unsigned char i = Mot1; i < nMot; i++){
                enRef[i]->setValue(en[i]);
            }

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




