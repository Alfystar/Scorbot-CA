//
// Created by alfyhack on 12/11/19.
//

#include "ComUartAdapter.h"

//Dichiarazione per il linker delle variabili statiche
ComUartAdapter *ComUartAdapter::instance = nullptr;
UartDriver *ComUartAdapter::uartDev = nullptr;
std::mutex ComUartAdapter::instanceMutex;
//sem_t ComUartAdapter::setNew, ComUartAdapter::enNew, ComUartAdapter::curNew;

ComUartAdapter &ComUartAdapter::getInstance (){
    std::lock_guard <std::mutex> myLock(ComUartAdapter::instanceMutex);
    if (!ComUartAdapter::instance){
        ComUartAdapter::instance = new ComUartAdapter();
    }

    return *ComUartAdapter::instance;
}

ComUartAdapter &ComUartAdapter::getInstance (const std::string &device) noexcept(false){
    std::lock_guard <std::mutex> myLock(ComUartAdapter::instanceMutex);
    if (!ComUartAdapter::instance){
        ComUartAdapter::instance = new ComUartAdapter();
    }
    ComUartAdapter::instance->changeDevice(device);
    sleep(1);  // wait for 1s to take time to set the class and concurrency
    return *ComUartAdapter::instance;
}

void ComUartAdapter::changeDevice (const std::string &device) noexcept(false){
    if (!uartDev){
        uartDev = new UartDriver(device);
    }
    else{
        delete uartDev;
        uartDev = new UartDriver(device);
    }
}

void ComUartAdapter::changeDeviceVel (speed_t uartVel) noexcept(false){
    if (!uartDev)
        throw std::runtime_error("ComUartAdapter::changeDeviceVel, uartDev not define jet");
    uartDev->uartSpeed(uartVel);
}

ComUartAdapter::~ComUartAdapter (){
}

bool ComUartAdapter::isConnect (){
    return uartDev != nullptr;
}

void ComUartAdapter::goHome (){
    uartDev->packSend(goHomeUart, nullptr);
}

void ComUartAdapter::sendVel (SpeedMot &sp){
    uartDev->packSend(mSpeedData, (data2Ard *) &sp.getPwm());
}

void ComUartAdapter::setSetting (SettingBoard_C &set){
    this->set->copyPack(set);
    //    sem_postRestorLimit(&setNew, numReciver);    // di persè è un nuovo dato
    uartDev->packSend(settingBoardData, (data2Ard *) &set.getSetting());
}

void ComUartAdapter::setSampleTimeEn (uint32_t sEn){
    this->sEn.tv_usec = sEn;  // time in micro-Second, like arduino expected
    uartDev->packSend(sampleTimeEn, (data2Ard *) &sEn);
}

void ComUartAdapter::setSampleTimeCur (uint32_t sCur){
    this->sCur.tv_usec = sCur; // time in micro-Second, like arduino expected
    uartDev->packSend(sampleTimeCur, (data2Ard *) &sCur);
}

EncoderMot *ComUartAdapter::getEncoder (){
    EncoderMot *e = new EncoderMot();
    e->copyEn(allSensor->getEn());
    return e;
}

CurrentMot *ComUartAdapter::getCurrent (){
    CurrentMot *c = new CurrentMot();
    c->copyCur(allSensor->getCurrent());
    return c;
}

AllSensor *ComUartAdapter::getSensor (){
    AllSensor *all = new AllSensor();
    all->copyPack(allSensor->getSens());
    return all;
}

EncoderMot *ComUartAdapter::getEncoder (struct timespec *t){
    memcpy(t, &enTime, sizeof(struct timespec));
    return getEncoder();
}

CurrentMot *ComUartAdapter::getCurrent (struct timespec *t){
    memcpy(t, &curTime, sizeof(struct timespec));
    return getCurrent();
}

AllSensor *ComUartAdapter::getSensor (struct timespec *en, struct timespec *cur){
    memcpy(en, &enTime, sizeof(struct timespec));
    memcpy(cur, &curTime, sizeof(struct timespec));
    return getSensor();
}

SettingBoard_C *ComUartAdapter::getSetting_local (){
    SettingBoard_C *set = new SettingBoard_C();
    set->copyPack(*this->set);
    return set;
}

SettingBoard_C *ComUartAdapter::getSetting_board (){
    //get data from boart
    uartDev->packSend(settingAsk, nullptr);
    usleep(100 * 1000U);  //100 ms per far copiare il dato
    SettingBoard_C *p = new SettingBoard_C();
    p->copyPack(*set);
    return p;
}

bool ComUartAdapter::isEncoderValid (){
    return timeValid(&enTime, &sEn);
}

bool ComUartAdapter::isCurrentValid (){
    return timeValid(&curTime, &sCur);
}

bool ComUartAdapter::isAllSensorValid (){
    return isEncoderValid() && isCurrentValid();
}

ComUartAdapter::ComUartAdapter () : ScorInterface(){//,
    //                                   GetCom_int(),
    //                                   uartFactory(ParamSingletonFactory::getInstance()) {
    this->set = new SettingBoard_C(this->setting);
    this->allSensor = new AllSensor(this->sensors);

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

#define ms (1000UL * 1000UL)  //time in millisecond
void ComUartAdapter::uartReader (ComUartAdapter *u){
    struct timespec timeOut, timeToAdd, now;
    struct timespec timePack;

    usleep(10 * 1000UL);  // wait for 10ms to take time to set the class
    while (true){
        while (!u->uartDev){
            std::cerr << "[ComUartAdapter::uartReader] Nessuna com aperta, attendo 1s\n";
            sleep(1);
        }
        clock_gettime(CLOCK_REALTIME, &now);

        timeWriteSpec(&timeToAdd, 0, 500 * ms);
        timeraddSpec(&now, &timeToAdd, &timeOut);
        uart2Linux *dato = nullptr;
        try{
            dato = u->uartDev->getDataWait_timePack(&timeOut, &timePack);
        }catch (std::exception &e){
            std::cerr << e.what() << "\n";
            sleep(1);
        }
        if (dato){
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Waddress-of-packed-member"
            switch (dato->type){
                case settingBoardData:
                    u->set->copyPack(dato->pack.up.prop);
                    u->notifySettingBoard();    // Notifico l'arrivo di un dato, al ricevente capire quale e se è interessato
                    break;
                case mEncoderData:
                    memcpy(&u->enTime, &timePack, sizeof(struct timespec));
                    u->allSensor->copyEn(&dato->pack.up.en);
                    u->notifyEncoderData();
                    break;
                case mCurrentData:
                    memcpy(&u->curTime, &timePack, sizeof(struct timespec));
                    u->allSensor->copyCur(&dato->pack.up.cur);
                    u->notifyCurrentData();
                    break;
                case mAllData:
                    memcpy(&u->enTime, &timePack, sizeof(struct timespec));
                    memcpy(&u->curTime, &u->enTime, sizeof(u->enTime));
                    u->allSensor->copyPack(&dato->pack.up.sens);
                    u->notifyEncoderData();
                    u->notifyCurrentData();
                    break;
                default:
                    fprintf(stderr, "Arrivato un pacchetto impssibile, tipo:%d\n", dato->type);
                    break;
            }
            #pragma GCC diagnostic pop
        }
        else{
            fprintf(stderr, "[ComUartAdapter::uartReader] Nessuna connessione da %lds %ldms\n", timeToAdd.tv_sec,
                    timeToAdd.tv_nsec / ms);
        }
    }//while end
}
#undef ms

bool ComUartAdapter::timeValid (struct timespec *lastSensorTime, struct timeval *sampleTime){
    struct timespec now;
    struct timeval nowVal, lastSensorTimeVal, delta;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    TIMESPEC_TO_TIMEVAL(&nowVal, &now);
    TIMESPEC_TO_TIMEVAL(&lastSensorTimeVal, lastSensorTime);
    timersub(&nowVal, &lastSensorTimeVal, &delta);
    return (timercmp(&delta, sampleTime, <));    //il dato è ancora valido

}




