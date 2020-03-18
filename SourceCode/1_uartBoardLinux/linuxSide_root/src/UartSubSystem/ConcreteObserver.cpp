//
// Created by alfyhack on 18/03/20.
//

#include "ConcreteObserver.h"

ConcreteObserver::ConcreteObserver(ScorInterface *scorbot) : ObserverScorbot() {
    this->scorbot = scorbot;
    this->scorbot->add(this, mAllData);
    this->scorbot->add(this, settingBoardData);
    enableSettingBoard(false);
    enableCurrentData(false);
    enableEncoderData(false);
    if (sem_init(&enSem, 0, 0)) {
        perror("sem_int enNew fails for:");
    }
    if (sem_init(&curSem, 0, 0)) {
        perror("sem_int curNew fails for:");
    }
}

EncoderMot *ConcreteObserver::getValidEncoderWait() {
    dataSemWait(&enSem);
    return scorbot->getEncoder(&enTime);
}

CurrentMot *ConcreteObserver::getValidCurrentWait() {
    dataSemWait(&curSem);
    return scorbot->getCurrent(&curTime);
}


EncoderMot *ConcreteObserver::getValidEncoderWait(struct timespec *t) {
    EncoderMot *p = getValidEncoderWait();
    memcpy(t, &enTime, sizeof(struct timespec));
    return p;
}

CurrentMot *ConcreteObserver::getValidCurrentWait(struct timespec *t) {
    CurrentMot *p = getValidCurrentWait();
    memcpy(t, &curTime, sizeof(struct timespec));
    return p;
}

void ConcreteObserver::enableSettingBoard(bool en) {
    this->enSet = en;
}

void ConcreteObserver::enableCurrentData(bool en) {
    this->enCur = en;
}

void ConcreteObserver::enableEncoderData(bool en) {
    this->enEnc = en;
}

void ConcreteObserver::updateSettingBoard() {
    if (!enSet)
        return;
    SettingBoard_C *pNotified;
    std::cout << "ConcreteObserver:updateSettingBoard\n";
    pNotified = scorbot->getSetting_local();
    pNotified->printSetting();

}

void ConcreteObserver::updateCurrendData() {
    if (!enCur)
        return;
    std::cout << "ConcreteObserver:updateCurrendData\t";
    sem_postOnce(&curSem);

}

void ConcreteObserver::updateEncoderData() {
    if (!enEnc)
        return;
    std::cout << "ConcreteObserver:updateEncoderData\t";
    sem_postOnce(&enSem);

}

inline void ConcreteObserver::sem_postOnce(sem_t *s) {
    sem_postRestorLimit(s, 1);
}

inline void ConcreteObserver::sem_postRestorLimit(sem_t *s, int value) {
    int sval;
    //returns 0 on success; on error, -1 is returned and errno is set to indicate the error.
    if (sem_getvalue(s, &sval)) {
        perror("sem_getvalue fails for:");
    }

//      sem_getvalue()  places  the current value of the semaphore pointed to sem into the integer pointed to by sval.
//      If one or more processes or threads  are  blocked  waiting  to  lock  the  semaphore  with
//      sem_wait(3), POSIX.1 permits two possibilities for the value returned in sval:
//      either 0 is returned;
//      or a negative number whose absolute value is the count of  the  number  of  processes and threads currently blocked in sem_wait(3).
    while (sval < value) {
        if (sem_post(s)) {
            perror("sem_postRestorLimit:sem_post fails for:");
            return;
        }
        sval++;
    }
}

inline void ConcreteObserver::sem_clearItem(sem_t *s) {
    while (true) {   //repeat until the token is clean
        if ((sem_trywait(s) == -1))
            if (errno == EAGAIN)
                return;
            else
                perror("sem_trywait fail whit error:");
    }
}

inline void ConcreteObserver::dataSemWait(sem_t *s) {
    if (sem_wait(s)) {
        perror("sem_wait fails for:");
    }
}