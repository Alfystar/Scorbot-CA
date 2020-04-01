//sys/time.h
// Created by alfyhack on 12/11/19.
//

#ifndef PCLISTENUART_COMUARTADAPTER_H
#define PCLISTENUART_COMUARTADAPTER_H

#include <ScorInterface.h>

//#include <AdapterClasses/ParamSingletonFactory.h>

#include <UartDriver.h>
#include <string>
#include <mutex>
#include <termios.h>

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <sys/time.h>
#include <timeSpecOp.h>

#ifndef __USE_GNU
#define __USE_GNU
#endif

using namespace Uart;
class ComUartAdapter : public ScorInterface {//, public GetCom_int {
public:
    //singleton because in all process can be only one uart to board for time
    static ComUartAdapter &getInstance();
    static ComUartAdapter &getInstance(const std::string &device) noexcept(false);
    //The device for any reason should change, so updateSettingBoard state van be necessary
    void changeDevice(const std::string &device) noexcept(false);
    void changeDeviceVel(speed_t uartVel) noexcept(false);

    virtual ~ComUartAdapter();

    /// #### ObservableScorbot override and Extension####

    /// #### ScorInterface override ####
    bool isConnect() override;
    /// Set Data
    void goHome() override;
    void sendVel(SpeedMot &sp) override;
    void setSetting(SettingBoard_C &set) override;
    void setSampleTimeEn(uint32_t sEn) override;    //Sample time in Microseconds 10^(-6)
    void setSampleTimeCur(uint32_t sCur) override;  //Sample time in Microseconds 10^(-6)
    /// Get data
    EncoderMot *getEncoder() override;
    CurrentMot *getCurrent() override;
    AllSensor *getSensor() override;
    EncoderMot *getEncoder(struct timespec *t) override;
    CurrentMot *getCurrent(struct timespec *t) override;
    AllSensor *getSensor(struct timespec *en, struct timespec *cur) override;
    SettingBoard_C *getSetting_local() override;
    SettingBoard_C *getSetting_board() override;
    /// Valid question
    bool isEncoderValid() override;
    bool isCurrentValid() override;
    bool isAllSensorValid() override;

private:
    /// Variabili di funzionamento della classe nel sistema
    static std::mutex instanceMutex;
    static ComUartAdapter *instance;
    static UartDriver *uartDev;

    /// Thread di lettura della porta
    std::thread *readerUartDriverTh;      //Puntatore al Thread avviato


    /// Variabili di salvataggio dei pacchetti letti dal Thread uartReader
    settingsBoard setting;
    SettingBoard_C *set;

    mAll sensors;
    AllSensor *allSensor;
    struct timespec enTime, curTime;

    /// Variabili per validare i dati
    struct timeval sEn, sCur; // Sample time

    ComUartAdapter();
    static void uartReader(ComUartAdapter *u);
    bool timeValid(struct timespec *lastSensorTime, struct timeval *sampleTime);

    //Semaphore utility
    static void sem_postOnce(sem_t *s); // Mette esattamente 1 token nel semaforo
    static void sem_postRestorLimit(sem_t *s, int value);  // Ripristina il numero di Token a value
    static void sem_clearIthem(sem_t *s);
    static void dataSemWait(sem_t *s);
};

#endif //PCLISTENUART_COMUARTADAPTER_H
