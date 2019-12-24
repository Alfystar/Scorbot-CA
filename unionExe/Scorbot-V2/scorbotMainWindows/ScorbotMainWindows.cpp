//
// Created by alfyhack on 24/12/19.
//

#include "ScorbotMainWindows.h"
#include "uiSrc/scorbotUi/ui_source/ui_mainwindow.h" //classe generata dal file di designer in automatico dal cmake

ScorbotMainWindows::ScorbotMainWindows(QWidget *parent) : MainWindow(parent) {
    //this->ui->menuSerialPort->exec();
    connect(this->ui->menuSerialPort, SIGNAL (triggered(QAction * )), this, SLOT (serialPort_handler(QAction * )));
    connect(this->ui->actionSerial_Find, SIGNAL(triggered()), this, SLOT(serialSearch_handler()));
    connect(this->ui->actionConnection_Start, SIGNAL (triggered()), this, SLOT (serialConnect_handler()));
    connect(this->ui->actionClose_connection, SIGNAL (triggered()), this, SLOT (closeConnection_handler()));
    this->ui->actionClose_connection->setDisabled(true);
    connect(this->ui->actionReset_Board, SIGNAL (triggered()), this, SLOT (resetBoard_handler()));

}

ScorbotMainWindows::~ScorbotMainWindows() {

}

void ScorbotMainWindows::serialPort_handler(QAction *action) {
    QList<QAction *> list = this->ui->menuSerialPort->actions();
    for (int i = 1; i < list.count(); i++) {
        if (list[i]->isChecked()) {
            uartPath = list[i]->text().toStdString();
            std::cout << "serialPort_handler:\n" << uartPath << "\n";
            break;
        }
    }
}

void ScorbotMainWindows::serialSearch_handler() {
    std::cout << "serialSearch_handler" << "\n";
    //remove all list exept first
    QList<QAction *> list = this->ui->menuSerialPort->actions();
    for (int i = 1; i < list.count(); i++) {
        this->ui->menuSerialPort->removeAction(list[i]);
    }
    FILE *fp;
    char path[4066];

    /* Open the command for reading. */
    fp = popen("realpath /dev/serial/by-id/*  2>/dev/null", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(-1);
    }
    /* Read the output a line at a time - output it. */
    QAction *newAct;
    while (fgets(path, sizeof(path), fp) != NULL) {
        newAct = new QAction(path);
        newAct->setCheckable(true);
        this->ui->menuSerialPort->addAction(newAct);
    }
    /* close */
    pclose(fp);
}

void ScorbotMainWindows::serialConnect_handler() {
    std::cout << "serialConnect_handler : " << uartPath << "\n";

    /// Comunicazione avvio
    try {
        //todo capire perchè non vede /dev/ttyUSB0 anche se nel file system è presente
        scorbot = &AdapterFactory::makeUart(uartPath, B921600);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, tr("Scorbot Connection"), tr(e.what()));
        return;
    }

    /// Controllo avvio
    ctrl = new std::thread(ctrlTh, this);

    //Per ora li disattivo pechè una volta creata la seriale non posso ancora chiuderla e cambiarla
    this->ui->actionConnection_Start->setDisabled(true);
    this->ui->menuSerialPort->setDisabled(true);

}

void ScorbotMainWindows::closeConnection_handler() {
    std::cout << "closeConnection_handler" << "\n";

}

void ScorbotMainWindows::resetBoard_handler() {
    std::cout << "resetBoard_handler" << "\n";

}


void ScorbotMainWindows::ctrlTh(ScorbotMainWindows *w) {
    w->refPid = new EncoderMot();
    w->pwm = new SpeedMot();
    w->refMutex.unlock();
    w->pidM[Mot1] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, .8, 0.02);
    w->pidM[Mot2] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, 1.0, 0.02);
    w->pidM[Mot3] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, true, .8, 0.02);
    w->pidM[Mot4] = new PIDScorbot(0.00055, 0.0000000015, 10, 110, true, .8, 0.02);
    w->pidM[Mot5] = new PIDScorbot(0.00055, 0.0000000015, 10, 133, false, .8, 0.02);
    w->pidM[Mot6] = new PIDScorbot(0.00055, 0.0000000015, 10, 85, false, .8, 0.02);
    sleep(1);
    struct timespec tsEn, tsCur;   // Tempo di campionamento Encoder e Corrente
    timeWriteSpec(&tsEn, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento
    w->scorbot->setSampleTimeEn(tsEn.tv_nsec / 1000UL + tsEn.tv_sec * 1000000UL);
    timeWriteSpec(&tsCur, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento
    w->scorbot->setSampleTimeCur(tsCur.tv_nsec / 1000UL + tsCur.tv_sec * 1000000UL);

    /// Prendo la prima misura
    w->enFeed = w->scorbot->getEncoder();
    while (true) {
        w->refMutex.lock();
        /// Passaggio dei parametri al pid e calcolo del corrispettivo pwm
        for (int i = Mot1; i < Mot4; i++) {
            w->pwm->pwmSet((motCode) i,
                           w->pidM[i]->pid(w->refPid->getEn((motCode) i), w->enFeed->getEn((motCode) i), &tsEn));
            printf("mot[Mot%d]=%d\n\n", i + 1, w->pwm->getPwm((motCode) i));
        }
        w->refMutex.unlock();

        /// Invia il pacchetto il prima possibile
        w->scorbot->sendVel(*w->pwm);
        /// Pulisco la memoria e aspetto un nuovo pacchetto
        delete w->enFeed;
        w->enFeed = w->scorbot->getValidEncoderWait();
        printf("\n\n\n\n\n");
    }
}

