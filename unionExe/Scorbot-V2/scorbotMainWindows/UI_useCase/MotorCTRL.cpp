//
// Created by alfyhack on 20/03/20.
//

#include "MotorCTRL.h"
#include "uiSrc/scorbotUi/ui_source/ui_mainwindow.h"      //classe generata dal file di designer in automatico dal cmake
#include "uiSrc/scorbotUi/ui_source/ui_freeMoveWindow.h"      //classe generata dal file di designer in automatico dal cmake

MotorCTRL::MotorCTRL(MainWindow *parent) {
    this->win = parent;
    this->enObj = new EncoderMot();

    this->scorInterface = &ComUartAdapter::getInstance();
    this->obs = new ConcreteObserver(scorInterface);
    connect(win, SIGNAL (newRef(EncoderMot * )), this, SLOT (changeObj(EncoderMot * )));
    connect(win->ui->goHome, SIGNAL(clicked()), this, SLOT(goHome()));


    pidM[Mot1] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, .8, 0.02);
    pidM[Mot2] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, false, 1.0, 0.02);
    pidM[Mot3] = new PIDScorbot(0.00055, 0.0000000015, 10, 50, true, .8, 0.02);
    pidM[Mot4] = new PIDScorbot(0.00055, 0.0000000015, 10, 110, true, .8, 0.02);
    pidM[Mot5] = new PIDScorbot(0.00055, 0.0000000015, 10, 133, false, .8, 0.02);
    pidM[Mot6] = new PIDScorbot(0.00055, 0.0000000015, 10, 85, false, .8, 0.02);

    mn[Mot1] = win->freeMovWin->ui->mn1;
    mn[Mot2] = win->freeMovWin->ui->mn2;
    mn[Mot3] = win->freeMovWin->ui->mn3;
    mn[Mot4] = win->freeMovWin->ui->mn4;
    mn[Mot5] = win->freeMovWin->ui->mn5;
    mn[Mot6] = win->freeMovWin->ui->mn6;

    mp[Mot1] = win->freeMovWin->ui->mp1;
    mp[Mot2] = win->freeMovWin->ui->mp2;
    mp[Mot3] = win->freeMovWin->ui->mp3;
    mp[Mot4] = win->freeMovWin->ui->mp4;
    mp[Mot5] = win->freeMovWin->ui->mp5;
    mp[Mot6] = win->freeMovWin->ui->mp6;

//    signalMapper = new QSignalMapper(this);
//    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(motorDirectControl(int)));
//
//    for (int i = 0; i < nMot; ++i) {
//        signalMapper->setMapping(mn[i], (motPush) (Mot1n + 2 * i));
//        signalMapper->setMapping(mp[i], (motPush) (Mot1p + 2 * i));
//
//        connect(mn[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
//        connect(mp[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
//    }

    connect(win->freeMovWin, SIGNAL(widgetVisibilityChanged(bool)), this, SLOT(freeMoveWindowsShowing(bool)));


    this->ctrlTh = new std::thread(this->ctrlThMain, this);
}

void MotorCTRL::changeObj(EncoderMot *newObj) {
//    std::cout << "changeObj call: ";
    this->enObj->copyEn(*newObj);
    enObj->printEncoder();
}

void MotorCTRL::goHome() {
    scorInterface->goHome();
    goingToHome = true;
}

void MotorCTRL::motorDirectControl(int push) {
//    std::string s = b->objectName().toStdString();
//    std::cout << s.substr(0, 2) << "\n";
//    if (s.substr(0, 2).compare("mn")) {    // Pulsanti negativi
//
//    }
//    if (s.substr(0, 2).compare("mp")) {    // Pulsanti negativi
//
//    }
    std::cout << push << "\n";

}

void MotorCTRL::freeMoveWindowsShowing(bool show) {
    freeMoveCtrl = show;
    std::cout << "freeMoveWindowsShowing(" << show << ")\n";
}


void MotorCTRL::ctrlThMain(MotorCTRL *m) {

    /// Variabili del Controllore
    EncoderMot *enFeed; //Puntatore per i dati ricevuti
    EncoderMot *refPid = new EncoderMot();
    SpeedMot *pwm = new SpeedMot();

    struct timespec ts;
    timeWriteSpec(&ts, 0, 10 * 1000000UL);    //10ms per il tempo di campionamento

    while (!m->scorInterface->isConnect())
        sleep(5);

    m->scorInterface->setSampleTimeEn(ts.tv_nsec / 1000UL + ts.tv_sec * 1000000UL);
    /// Prendo la prima misura
    enFeed = m->scorInterface->getEncoder();
    refPid->copyEn(*m->enObj);

    m->obs->enableEncoderData(true);
    while (true) {
        if (m->goingToHome) {
            sleep(10);  //todo: capire sul campo se serve
            m->goingToHome = false;
        }
        if (m->freeMoveCtrl) {  // Se sono in modalità free move
            int speed = m->win->freeMovWin->ui->pwmSpeed->value();
            int sign = 1;
            for (int i = Mot1; i < nMot; i++) {
                if (m->mp[i]->isDown()) {
//                    std::cout << "mp[" << i << "] = true\n";
                    sign = 1;
                } else if (m->mn[i]->isDown()) {
//                    std::cout << "mn[" << i << "] = true\n";
                    sign = -1;
                } else {
//                    std::cout << "mp[" << i << "] && mn[" << i << "] = false\n";
                    sign = 0;
                }
                pwm->pwmSet((motCode) i, sign * speed);
            }
            pwm->printSpeed();
            /// Invia il pacchetto il prima possibile
            m->scorInterface->sendVel(*pwm);
            usleep(20 * 1000U); // aggiorno ogni 20 ms (50 fps)
        } else {    //Sono in modalità controllo
            /// Passaggio dei parametri al pid e calcolo del corrispettivo pwm

            for (int i = Mot1; i < nMot; i++) {
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

    }
    m->obs->enableEncoderData(false);

}
