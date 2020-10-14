//
// Created by alfyhack on 18/03/20.
//

#ifndef PCLISTENUART_CONCRETEOBSERVER_H
#define PCLISTENUART_CONCRETEOBSERVER_H

#include <AdapterClasses/ObserverScorbot.h>
#include <ScorInterface.h>
#include <iostream>
#include <semaphore.h>

class ConcreteObserver : public ObserverScorbot{
    ScorInterface *scorbot;
    bool enSet, enCur, enEnc;
    sem_t curSem, enSem;
    struct timespec enTime, curTime;
public:
    ConcreteObserver (ScorInterface *scorbot);
    EncoderMot *getValidEncoderWait ();
    CurrentMot *getValidCurrentWait ();
    EncoderMot *getValidEncoderWait (struct timespec *t);
    CurrentMot *getValidCurrentWait (struct timespec *t);
    // Enabling data wanted
    void enableSettingBoard (bool en);
    void enableCurrentData (bool en);
    void enableEncoderData (bool en);
    /// ##### ObserverScorbot OVERRIDE #####
    void updateSettingBoard () override;
    void updateCurrentData () override;
    void updateEncoderData () override;
private:
    //Semaphore utility
    static void sem_postOnce (sem_t *s); // Mette esattamente 1 token nel semaforo
    static void sem_postRestorLimit (sem_t *s, int value);  // Ripristina il numero di Token a value
    static void sem_clearItem (sem_t *s);
    static void dataSemWait (sem_t *s);
};

#endif //PCLISTENUART_CONCRETEOBSERVER_H
