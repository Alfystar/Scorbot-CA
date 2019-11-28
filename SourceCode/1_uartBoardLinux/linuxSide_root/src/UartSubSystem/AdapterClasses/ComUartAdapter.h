//sys/time.h
// Created by alfyhack on 12/11/19.
//

#ifndef PCLISTENUART_COMUARTADAPTER_H
#define PCLISTENUART_COMUARTADAPTER_H

#include <ScorInterface.h>
#include <GetCom_int.h>
#include <AdapterClasses/ParamSingletonFactory.h>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <sys/time.h>

#ifndef __USE_GNU
#define __USE_GNU
#endif

///###################################################################################################
///################################# Macro for Time Operation#########################################
///###################################################################################################
# define timerissetSpec(tvp)    ((tvp)->tv_sec || (tvp)->tv_nsec)
# define timerclearSpec(tvp)    ((tvp)->tv_sec = (tvp)->tv_nsec = 0)
# define timercmpSpec(a, b, CMP)        \
  (((a)->tv_sec == (b)->tv_sec) ?       \
   ((a)->tv_nsec CMP (b)->tv_nsec) :    \
   ((a)->tv_sec CMP (b)->tv_sec))
# define timeraddSpec(a, b, result)                     \
  do {                                                  \
    (result)->tv_sec = (a)->tv_sec + (b)->tv_sec;       \
    (result)->tv_nsec = (a)->tv_nsec + (b)->tv_nsec;    \
    if ((result)->tv_nsec >= 1000000000)                \
      {                                                 \
    ++(result)->tv_sec;                                 \
    (result)->tv_nsec -= 1000000000;                    \
      }                                                 \
  } while (0)
# define timersubSpec(a, b, result)                     \
  do {                                                  \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;       \
    (result)->tv_nsec = (a)->tv_nsec - (b)->tv_nsec;    \
    if ((result)->tv_nsec < 0) {                        \
      --(result)->tv_sec;                               \
      (result)->tv_nsec += 1000000000;                  \
    }                                                   \
  } while (0)
#define timeWriteSpec(ts, sec, nanoSec)                                     \
    do {                                                                    \
        (ts)->tv_sec=(long) sec + (long)nanoSec/( 1000UL* 1000UL * 1000UL); \
        (ts)->tv_nsec=(long) nanoSec%( 1000UL* 1000UL * 1000UL);            \
    }while(0)
#define timeStampSpec(ts, name) std::cout << name << ".tv_sec=" << (ts)->tv_sec << "\t" \
    << name << ".tv_nsec=" <<(ts)->tv_nsec << " (" << ((ts)->tv_nsec + (500UL * 1000UL)) /(1000UL * 1000UL) << "ms)\n"
///###################################################################################################


class ComUartAdapter : public ScorInterface, public GetCom_int {
public:
    //singleton because in all process can be only one uart to board for time
    static ComUartAdapter &getInstance();
    static ComUartAdapter &getInstance(const std::string &device) noexcept(false);
    //The device for any reason should change, so update state van be necessary
    void changeDevice(const std::string &device) noexcept(false);
    void changeDeviceVel(speed_t uartVel) noexcept(false);

    virtual ~ComUartAdapter();

    /// #### ScorInterface override ####
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
    /// Valid Get data
    EncoderMot *getValidEncoder() override;
    CurrentMot *getValidCurrent() override;
//    AllSensor *getValidSensor() override;
    EncoderMot *getValidEncoder(struct timespec *t) override;
    CurrentMot *getValidCurrent(struct timespec *t) override;
//    AllSensor *getValidSensor(struct timespec *en, struct timespec *cur) override;
    /// Wait Valid Get data
    EncoderMot *getValidEncoderWait() override;
    CurrentMot *getValidCurrentWait() override;
//    AllSensor *getValidSensorWait() override;
    EncoderMot *getValidEncoderWait(struct timespec *t) override;
    CurrentMot *getValidCurrentWait(struct timespec *t) override;
//    AllSensor *getValidSensorWait(struct timespec *en, struct timespec *cur) override;

    /// GetCom_int override
    // Nel caso della uart è inutile attendere attivamente la porta,
    // basta mettersi in attesa che il dato voluto torni valido, a leggere
    // la porta è presente un thread apposito che salva i dati
    // in infoExpPack appena arrivano
    EncoderMot &getEncoderConrete() override;
    CurrentMot &getCurrentConrete() override;
//    AllSensor &getSensorConrete() override;
    SettingBoard_C &getSettingConrete() override;
private:
    /// Variabili di funzionamento della classe nel sistema
    static std::mutex instanceMutex;
    static ComUartAdapter *instance;
    ParamSingletonFactory &uartFactory;
    static UartDriver *uartDev;

    /// Thread di lettura della porta
    std::thread *readerUartDriverTh;      //Puntatore al Thread avviato


    /// Variabili di salvataggio dei pacchetti letti dal Thread uartReader
    //static std::mutex setNew, enNew, curNew;
    // setNew, enNew, curNew specific for pack type
    static sem_t setNew, enNew, curNew;


    // L'uartReader unlock il mutex quando arriva un nuvo dato, così se un thread è in attesa del
    // dato viene risvegliato solo al momento della ricezione.
    // Un lettore lock il mutex a indicare che l'informazione è stata già letta
    settingsBoard setting;
    SettingBoard_C *set;

    // L'uartReader unlock il mutex quando arriva un nuvo dato, così se un thread è in attesa del
    // dato viene risvegliato solo al momento della ricezione.
    // Un lettore lock il mutex a indicare che l'informazione è stata già letta
    mAll sensors;
    AllSensor *allSensor;
    struct timespec enTime, curTime;

    /// Variabili per validare i dati
    struct timeval sEn, sCur; // Sample time

    ComUartAdapter();
    static void uartReader(ComUartAdapter *u);
    bool timeValid(struct timespec *lastSensorTime, struct timeval *sampleTime);

    //Semaphore utility
    static void sem_postOnce(sem_t *s);
    static void sem_clearIthem(sem_t *s);
    static void dataSemWait(sem_t *s);
};

#endif //PCLISTENUART_COMUARTADAPTER_H
