//
// Created by alfyhack on 20/03/20.
//

#include "MotorCTRL.h"
#include "scorbotUi/ui_source/ui_mainwindow.h"      //classe generata dal file di designer in automatico dal cmake
#include "scorbotUi/ui_source/ui_freeMoveWindow.h"      //classe generata dal file di designer in automatico dal cmake

MotorCTRL::MotorCTRL (MainWindow *parent){
    this->win = parent;
    this->enObj = new EncoderMot();

    this->scorInterface = &ComUartAdapter::getInstance();
    this->obs = new ConcreteObserver(scorInterface);
    connect(win, SIGNAL (newRef(EncoderMot * )), this, SLOT (changeObj(EncoderMot * )));
    connect(win, SIGNAL (breakSig()), this, SLOT (breakAllMot()));
    connect(win->ui->goHome, SIGNAL(clicked()), this, SLOT(goHome()));

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
    roll[0] = win->freeMovWin->ui->rollClockWise;
    roll[1] = win->freeMovWin->ui->rollAntiClockWise;
    pitch[0] = win->freeMovWin->ui->pitchInning;
    pitch[1] = win->freeMovWin->ui->pitchOuting;

    connect(win->freeMovWin, SIGNAL(widgetVisibilityChanged(bool)), this, SLOT(freeMoveWindowsShowing(bool)));

    this->ctrlTh = new std::thread(this->ctrlThMain, this);
}

void MotorCTRL::changeObj (EncoderMot *newObj){
    this->enObj->copyEn(*newObj);
    motState = controllMode;
    enObj->printEncoder();
}

void MotorCTRL::breakAllMot (){
    motState = stopMode;
}

void MotorCTRL::goHome (){
    scorInterface->goHome();
    motState = stopMode;
}

void MotorCTRL::freeMoveWindowsShowing (bool show){
    if (show){
        motState = freeMode;
    }
    else{
        motState = stopMode;
    }
}

[[noreturn]] void MotorCTRL::ctrlThMain (MotorCTRL *m){

    /// Variabili del Controllore
    EncoderMot *enFeed; //Puntatore per i dati ricevuti
    EncoderMot *refPid = new EncoderMot();
    SpeedMot *pwm = new SpeedMot();

    while (!m->scorInterface->isConnect())
        sleep(1);

    CTRL::setup(m->scorInterface);

    /// Prendo la prima misura
    m->obs->enableEncoderData(true);
    short sign;
    int speed;
    while (true){
        // Ottengo il feedback dal robot
        enFeed = m->obs->getValidEncoderWait();
        refPid->copyEn(*m->enObj);

        switch (m->motState){
            case controllMode:

                pwm->copyPack(CTRL::loop(refPid, enFeed));
                break;
            case freeMode:
                speed = m->win->freeMovWin->ui->pwmSpeed->value();
                for (int i = Mot1; i < nMot; i++){
                    if (m->mp[i]->isDown()){
                        sign = 1;
                    }
                    else if (m->mn[i]->isDown()){
                        sign = -1;
                    }
                    else{
                        sign = 0;
                    }
                    pwm->pwmSet((motCode) i, sign * speed);
                }
                // <== Roll and Pitch Button ==>
                if(m->roll[0]->isDown()){
                    pwm->pwmSet(Mot4, -speed);
                    pwm->pwmSet(Mot5, -speed);
                }
                if(m->roll[1]->isDown()){
                    pwm->pwmSet(Mot4, speed);
                    pwm->pwmSet(Mot5, speed);
                }
                if(m->pitch[0]->isDown()){
                    pwm->pwmSet(Mot4, -speed);
                    pwm->pwmSet(Mot5, speed);
                }
                if(m->pitch[1]->isDown()){
                    pwm->pwmSet(Mot4, speed);
                    pwm->pwmSet(Mot5, -speed);
                }

                //pwm->printSpeed();
                break;
            case stopMode:
                pwm->softAllBreak();
                break;
            default:
                std::cerr << "[MotorCTRL::ctrlThMain] Default!!!" << std::endl;
        }

        /// Invia il pacchetto il prima possibile
        m->scorInterface->sendVel(*pwm);
        /// Pulisco la memoria e aspetto un nuovo pacchetto
        delete enFeed;
    }
    m->obs->enableEncoderData(false);
}


