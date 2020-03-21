//
// Created by alfyhack on 24/12/19.
//

#include "ScorbotMainWindows.h"
#include "UI_useCase/uiSrc/scorbotUi/ui_source/ui_mainwindow.h"      //classe generata dal file di designer in automatico dal cmake

ScorbotMainWindows::ScorbotMainWindows(QWidget *parent) : MainWindow(parent) {
    std::cout << "ScorbotMainWindows constructor\n";
    this->uartConnect = new UartConnect(this);  //Gli passo il riferimento ai miei oggetti
    this->motCtrl = new MotorCTRL(this);
    this->dataShow = new DataShow(this);

}

ScorbotMainWindows::~ScorbotMainWindows() {

}


//void ScorbotMainWindows::ctrlTh(ScorbotMainWindows *w) {
//    w->refPid = new EncoderMot();
//    w->pwm = new SpeedMot();
//    w->refMutex.unlock();
//    w->pidM[Mot1] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, .8, 0.02);
//    w->pidM[Mot2] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, 1.0, 0.02);
//    w->pidM[Mot3] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, true, .8, 0.02);
//    w->pidM[Mot4] = new PIDScorbot(0.00055, 0.0000000015, 10, 110, true, .8, 0.02);
//    w->pidM[Mot5] = new PIDScorbot(0.00055, 0.0000000015, 10, 133, false, .8, 0.02);
//    w->pidM[Mot6] = new PIDScorbot(0.00055, 0.0000000015, 10, 85, false, .8, 0.02);
//    sleep(1);
//    struct timespec tsEn, tsCur;   // Tempo di campionamento Encoder e Corrente
//    timeWriteSpec(&tsEn, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento
//    w->scorInterface->setSampleTimeEn(tsEn.tv_nsec / 1000UL + tsEn.tv_sec * 1000000UL);
//    timeWriteSpec(&tsCur, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento
//    w->scorInterface->setSampleTimeCur(tsCur.tv_nsec / 1000UL + tsCur.tv_sec * 1000000UL);
//
//    /// Prendo la prima misura
//    w->enFeed = w->scorInterface->getEncoder();
//    while (true) {
//        w->refMutex.lock();
//        /// Passaggio dei parametri al pid e calcolo del corrispettivo pwm
//        for (int i = Mot1; i < Mot4; i++) {
//            w->pwm->pwmSet((motCode) i,
//                           w->pidM[i]->pid(w->refPid->getEn((motCode) i), w->enFeed->getEn((motCode) i), &tsEn));
//            printf("mot[Mot%d]=%d\n\n", i + 1, w->pwm->getPwm((motCode) i));
//        }
//        w->refMutex.unlock();
//
//        /// Invia il pacchetto il prima possibile
//        w->scorInterface->sendVel(*w->pwm);
//        /// Pulisco la memoria e aspetto un nuovo pacchetto
//        delete w->enFeed;
//        w->enFeed = w->scorInterface->getValidEncoderWait();
//        printf("\n\n\n\n\n");
//    }
//}

