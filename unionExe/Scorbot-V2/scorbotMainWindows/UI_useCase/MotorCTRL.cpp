//
// Created by alfyhack on 20/03/20.
//

#include "MotorCTRL.h"
#include "uiSrc/scorbotUi/ui_source/ui_mainwindow.h"      //classe generata dal file di designer in automatico dal cmake

MotorCTRL::MotorCTRL(MainWindow *parent) {
    this->win = parent;
    this->enObj = new EncoderMot();

    this->scorInterface = &ComUartAdapter::getInstance();
    this->obs = new ConcreteObserver(scorInterface);
    connect(win, SIGNAL (newRef(EncoderMot *)), this, SLOT (changeObj(EncoderMot * )));

    pidM[Mot1] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, .8, 0.02);
    pidM[Mot2] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, 1.0, 0.02);
    pidM[Mot3] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, true, .8, 0.02);
    pidM[Mot4] = new PIDScorbot(0.00055, 0.0000000015, 10, 110, true, .8, 0.02);
    pidM[Mot5] = new PIDScorbot(0.00055, 0.0000000015, 10, 133, false, .8, 0.02);
    pidM[Mot6] = new PIDScorbot(0.00055, 0.0000000015, 10, 85, false, .8, 0.02);

    this->ctrlTh = new std::thread(this->ctrlThMain, this);
}

void MotorCTRL::changeObj(EncoderMot *newObj) {
    std::cout << "changeObj call: ";
    this->enObj->copyEn(*newObj);
    enObj->printEncoder();
}


void MotorCTRL::ctrlThMain(MotorCTRL *m) {

    /// Variabili del Controllore
    EncoderMot *enFeed; //Puntatore per i dati ricevuti
    EncoderMot *refPid = new EncoderMot();
    SpeedMot *pwm = new SpeedMot();

    struct timespec ts;
    timeWriteSpec(&ts, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento

    while (!m->scorInterface->isConnect())
        sleep(1);

    m->scorInterface->setSampleTimeEn(ts.tv_nsec / 1000UL + ts.tv_sec * 1000000UL);
    /// Prendo la prima misura
    enFeed = m->scorInterface->getEncoder();
    refPid->copyEn(*m->enObj);

    m->obs->enableEncoderData(true);
    while (true) {
        /// Passaggio dei parametri al pid e calcolo del corrispettivo pwm

        for (int i = Mot1; i <= Mot6; i++) {
            pwm->pwmSet((motCode) i, m->pidM[i]->pid(refPid->getEn((motCode) i), enFeed->getEn((motCode) i), &ts));
//            printf("mot[Mot%d]=%d\n\n", i + 1, pwm->getPwm((motCode) i));
        }

        /// Invia il pacchetto il prima possibile
        m->scorInterface->sendVel(*pwm);
        /// Pulisco la memoria e aspetto un nuovo pacchetto
        delete enFeed;
        enFeed = m->obs->getValidEncoderWait();
        refPid->copyEn(*m->enObj);
//        std::cout << "new Ref: ";
//        refPid->printEncoder();
//        printf("\n\n\n\n\n");
    }
    m->obs->enableEncoderData(false);

}
