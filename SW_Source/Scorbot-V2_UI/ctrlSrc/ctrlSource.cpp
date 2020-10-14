//
// Created by alfystar on 11/10/20.
//

#include "ctrlSource.h"

// <== Pid ==>
PIDScorbot *pidM[nMot];
float kp = 0.001;
float ki = 0;
float kd = 10;

// <== Sample time ==>
struct timespec enSample;

// <== Speed to Return ==>
SpeedMot pwm;   // Generato col costruttore di Default, dal compilatore

void CTRL::setup (ScorInterface *scorInterface){
    // ki = 0.0000000015
    pidM[Mot1] = new PIDScorbot(kp, ki, kd, 80, .8, 0.02);
    pidM[Mot2] = new PIDScorbot(kp, ki, kd, 80, 1.0, 0.02);
    pidM[Mot3] = new PIDScorbot(kp, ki, kd, 80, .8, 0.02);
    pidM[Mot4] = new PIDScorbot(kp, ki, kd, 130, .8, 0.02);
    pidM[Mot5] = new PIDScorbot(kp, ki, kd, 130, .8, 0.02);
    pidM[Mot6] = new PIDScorbot(kp, ki, kd, 85, .8, 0.02);

    // Imposto il tempo di Campionamento
    timeWriteSpec(&enSample, 0, 100 * 1000UL * 1000UL);    //10ms per il tempo di campionamento
    scorInterface->setSampleTimeEn(enSample.tv_nsec / 1000UL + enSample.tv_sec * 1000UL * 1000UL);

}

// Loop MUST be as short as possible
// Deve ritornare il riferimento a un oggetto SpeedMot, che verrà usato per copiare i valori
// senza modificare il valore passato.
SpeedMot &CTRL::loop (EncoderMot *refPid, EncoderMot *enFeed){
    short vPwm;
    for (int i = Mot1; i < nMot; i++){
        vPwm = pidM[Mot1 + i]->pid(refPid->getEn((motCode) i), enFeed->getEn((motCode) i), &enSample);
        pwm.pwmSet((motCode) i, vPwm);
    }
    return pwm;
}