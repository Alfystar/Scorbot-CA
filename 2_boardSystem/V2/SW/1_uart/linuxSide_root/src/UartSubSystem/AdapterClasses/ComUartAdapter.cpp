//
// Created by alfyhack on 12/11/19.
//

#include "ComUartAdapter.h"

//Dichiarazione per il linker delle variabili statiche
ComUartAdapter *ComUartAdapter::instance = nullptr;
UartDriver *ComUartAdapter::uartDev = nullptr;
std::mutex ComUartAdapter::instanceMutex;
std::mutex ComUartAdapter::setNew, ComUartAdapter::enNew, ComUartAdapter::curNew;

ComUartAdapter &ComUartAdapter::getInstance() {
    std::lock_guard<std::mutex> myLock(ComUartAdapter::instanceMutex);
    if (!ComUartAdapter::instance) {
        ComUartAdapter::instance = new ComUartAdapter();
    }
    if (ComUartAdapter::instance->uartDev == nullptr) {
        try {
            ComUartAdapter::instance->uartDev = ComUartAdapter::instance->uartFactory.getLastUartClass();
        } catch (std::exception e) {
            perror(e.what());
            throw std::runtime_error(std::string("Impossibile creare una com Funzionante:").append(e.what()));
        }

    }
    return *ComUartAdapter::instance;
}

ComUartAdapter &ComUartAdapter::getInstance(const std::string &device) noexcept(false) {
    std::lock_guard<std::mutex> myLock(ComUartAdapter::instanceMutex);
    if (!ComUartAdapter::instance) {
        ComUartAdapter::instance = new ComUartAdapter();
    }
    ComUartAdapter::instance->changeDevice(device);
    sleep(1);  // wait for 1s to take time to set the class and concurrency
    return *ComUartAdapter::instance;
}

void ComUartAdapter::changeDevice(const std::string &device) noexcept(false) {
    uartDev = uartFactory.getUartClass(device);
}

void ComUartAdapter::changeDeviceVel(speed_t uartVel) noexcept(false) {
    if (!uartDev)
        throw std::runtime_error("ComUartAdapter::changeDeviceVel, uartDev not define jet");
    uartDev->uartSpeed(uartVel);
}

ComUartAdapter::~ComUartAdapter() {

}

void ComUartAdapter::goHome() {
    uartDev->packSend(goHomeUart, nullptr);
}

void ComUartAdapter::sendVel(SpeedMot &sp) {
    uartDev->packSend(mSpeedData, (data2Ard *) &sp.getPwm());
}

void ComUartAdapter::setSetting(SettingBoard_C &set) {
    this->set->copyPack(set);
    ComUartAdapter::setNew.unlock();    // di persè è un nuovo dato
    uartDev->packSend(settingBoardData, (data2Ard *) &set.getSetting());
}

void ComUartAdapter::setSampleTimeEn(uint32_t sEn) {
    this->sEn.tv_usec = sEn;  // time in micro-Second, like arduino expected
    uartDev->packSend(sampleTimeEn, (data2Ard *) &sEn);
}

void ComUartAdapter::setSampleTimeCur(uint32_t sCur) {
    this->sCur.tv_usec = sCur; // time in micro-Second, like arduino expected
    uartDev->packSend(sampleTimeCur, (data2Ard *) &sCur);
}


EncoderMot *ComUartAdapter::getEncoder() {
    EncoderMot *e = new EncoderMot();
    e->copyEn(allSensor->getEn());
    return e;
}

CurrentMot *ComUartAdapter::getCurrent() {
    CurrentMot *c = new CurrentMot();
    c->copyCur(allSensor->getCurrent());
    return c;
}

AllSensor *ComUartAdapter::getSensor() {
    AllSensor *all = new AllSensor();
    all->copyPack(allSensor->getSens());
    return all;
}

EncoderMot *ComUartAdapter::getEncoder(struct timespec *t) {
    memcpy(t, &enTime, sizeof(struct timespec));
    return getEncoder();
}

CurrentMot *ComUartAdapter::getCurrent(struct timespec *t) {
    memcpy(t, &curTime, sizeof(struct timespec));
    return getCurrent();
}

AllSensor *ComUartAdapter::getSensor(struct timespec *en, struct timespec *cur) {
    memcpy(en, &enTime, sizeof(struct timespec));
    memcpy(cur, &curTime, sizeof(struct timespec));
    return getSensor();
}

SettingBoard_C *ComUartAdapter::getSetting_local() {
    SettingBoard_C *set = new SettingBoard_C();
    set->copyPack(*this->set);
    return set;
}

SettingBoard_C *ComUartAdapter::getSetting_board() {
    //get data from boart
    SettingBoard_C &set = this->getSettingConrete();
    // update data on infoExpert
    return &set;

}

bool ComUartAdapter::isEncoderValid() {
    return timeValid(&enTime, &sEn);
}

bool ComUartAdapter::isCurrentValid() {
    return timeValid(&curTime, &sCur);
}

bool ComUartAdapter::isAllSensorValid() {
    return isEncoderValid() && isCurrentValid();
}

EncoderMot *ComUartAdapter::getValidEncoder() {
    if (isEncoderValid()) {
        EncoderMot *p = new EncoderMot();
        p->copyEn(allSensor->getEn());
        return p;
    } else
        return &getEncoderConrete();
}

CurrentMot *ComUartAdapter::getValidCurrent() {
    if (isCurrentValid()) {
        CurrentMot *p = new CurrentMot();
        p->copyCur(allSensor->getCurrent());
        return p;
    } else
        return &getCurrentConrete();
}

AllSensor *ComUartAdapter::getValidSensor() {
    if (isAllSensorValid()) {
        AllSensor *p = new AllSensor();
        p->copyPack(allSensor->getSens());
        return p;
    } else
        return &getSensorConrete();
}

EncoderMot *ComUartAdapter::getValidEncoder(struct timespec *t) {
    EncoderMot *p = getValidEncoder();
    memcpy(t, &enTime, sizeof(struct timespec));
    return p;
}

CurrentMot *ComUartAdapter::getValidCurrent(struct timespec *t) {
    CurrentMot *p = getValidCurrent();
    memcpy(t, &curTime, sizeof(struct timespec));
    return p;
}

AllSensor *ComUartAdapter::getValidSensor(struct timespec *en, struct timespec *cur) {
    AllSensor *p = getValidSensor();
    memcpy(en, &enTime, sizeof(struct timespec));
    memcpy(cur, &curTime, sizeof(struct timespec));
    return p;
}

EncoderMot *ComUartAdapter::getValidEncoderWait() {
    return &getEncoderConrete();
}

CurrentMot *ComUartAdapter::getValidCurrentWait() {
    return &getCurrentConrete();
}

AllSensor *ComUartAdapter::getValidSensorWait() {
    return &getSensorConrete();
}


EncoderMot *ComUartAdapter::getValidEncoderWait(struct timespec *t) {
    EncoderMot *p = getValidEncoderWait();
    memcpy(t, &enTime, sizeof(struct timespec));
    return p;
}

CurrentMot *ComUartAdapter::getValidCurrentWait(struct timespec *t) {
    CurrentMot *p = getValidCurrentWait();
    memcpy(t, &curTime, sizeof(struct timespec));
    return p;
}

AllSensor *ComUartAdapter::getValidSensorWait(struct timespec *en, struct timespec *cur) {
    AllSensor *p = getValidSensorWait();
    memcpy(en, &enTime, sizeof(struct timespec));
    memcpy(cur, &curTime, sizeof(struct timespec));
    return p;

}

EncoderMot &ComUartAdapter::getEncoderConrete() {
    enNew.lock();   //Quando uartReader riceverà un mEncoter verrò sbloccato
    EncoderMot *p = new EncoderMot();
    p->copyEn(allSensor->getEn());
    return *p;
}

CurrentMot &ComUartAdapter::getCurrentConrete() {
    curNew.lock();   //Quando uartReader riceverà un mCurrent verrò sbloccato
    CurrentMot *p = new CurrentMot();
    p->copyCur(allSensor->getCurrent());
    return *p;
}

AllSensor &ComUartAdapter::getSensorConrete() {
    std::lock(enNew, curNew); //Quando uartReader ha disponibili sia current che En
    AllSensor *p = new AllSensor();
    p->copyPack(allSensor->getSens());
    return *p;
}

SettingBoard_C &ComUartAdapter::getSettingConrete() {
    setNew.try_lock();   // voglio dati nuovi quindi sia se è unclock che lock lo metto a lock.
    uartDev->packSend(settingAsk, nullptr);
    setNew.lock();   //Quando uartReader riceverà un setting board verrò sbloccato
    SettingBoard_C *p = new SettingBoard_C();
    p->copyPack(*set);
    return *p;
}

ComUartAdapter::ComUartAdapter() : ScorInterface(),
                                   GetCom_int(),
                                   uartFactory(ParamSingletonFactory::getInstance()) {
    this->set = new SettingBoard_C(this->setting);
    this->allSensor = new AllSensor(this->sensors);
    //Imposto a lock tutti i mutex, non potendo essere già arrivati dei pacchetti
    setNew.try_lock();
    enNew.try_lock();
    curNew.try_lock();
    // Thread di lettura
    timerclear(&sEn);
    timerclear(&sCur);
    this->readerUartDriverTh = new std::thread(this->uartReader, this);
#ifdef RT_THREAD
    // encrease priority
    sched_param sch;
    int policy;
    pthread_getschedparam(this->readerUartDriverTh->native_handle(), &policy, &sch);
    sch.sched_priority = sched_get_priority_max(SCHED_FIFO);
    if (pthread_setschedparam(this->readerUartDriverTh->native_handle(), SCHED_FIFO, &sch)) {
        throw UartException("Failed to setschedparam: ", errno);
    }
#endif
}


void ComUartAdapter::uartReader(ComUartAdapter *u) {
    struct timespec timeOut, timeToAdd, now;
    usleep(10 * 1000UL);  // wait for 10ms to take time to set the class
    while (true) {
        while (!u->uartDev) {
            std::cerr << "Nessuna com aperta, attendo 1ms\n";
            usleep(1 * 1000UL);
        }
        clock_gettime(CLOCK_REALTIME, &now);
        // (1000UL * 1000UL)  //time in millisecond
        timeWriteSpec(&timeToAdd, 0, 500 * (1000UL * 1000UL));
        timeraddSpec(&now, &timeToAdd, &timeOut);
        uart2Rasp *dato = nullptr;
        try {
            dato = u->uartDev->getDataWait(&timeOut);
        } catch (std::exception &e) {
            std::cerr << e.what() << "\n";
            sleep(1);
        }
        if (dato) {
            switch (dato->type) {
                case settingBoardData:
                    u->set->copyPack(dato->pack.up.prop);
                    u->setNew.unlock();
                    break;
                case mEncoderData:
                    clock_gettime(CLOCK_MONOTONIC_RAW, &u->enTime);
                    u->allSensor->copyEn(&dato->pack.up.en);
                    u->enNew.unlock();
                    break;
                case mCurrentData:
                    clock_gettime(CLOCK_MONOTONIC_RAW, &u->curTime);
                    u->allSensor->copyCur(&dato->pack.up.cur);
                    u->curNew.unlock();
                    break;
                case mAllData:
                    clock_gettime(CLOCK_MONOTONIC_RAW, &u->enTime);
                    memcpy(&u->curTime, &u->enTime, sizeof(u->enTime));
                    u->allSensor->copyPack(&dato->pack.up.sens);
                    u->enNew.unlock();
                    u->curNew.unlock();
                    break;
                default:
                    fprintf(stderr, "Arrivato un pacchetto impssibile, tipo:%d\n", dato->type);
                    break;
            }
        } else {
            fprintf(stderr, "Nessuna connessione da %lds %ldms\n", timeToAdd.tv_sec,
                    timeToAdd.tv_nsec / (1000UL * 1000UL));
        }
    }//while end
}

bool ComUartAdapter::timeValid(struct timespec *lastSensorTime, struct timeval *sampleTime) {
    struct timespec now;
    struct timeval nowVal, lastSensorTimeVal, delta;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    TIMESPEC_TO_TIMEVAL(&nowVal, &now);
    TIMESPEC_TO_TIMEVAL(&lastSensorTimeVal, lastSensorTime);
    timersub(&nowVal, &lastSensorTimeVal, &delta);
    return (timercmp(&delta, sampleTime, <));    //il dato è ancora valido

}



