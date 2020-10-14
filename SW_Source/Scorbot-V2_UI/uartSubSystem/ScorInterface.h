//
// Created by alfyhack on 12/11/19.
//

#ifndef PCLISTENUART_SCORINTERFACE_H
#define PCLISTENUART_SCORINTERFACE_H

#include <dataTransfert_AllInclude.h>
#include <AdapterClasses/ObservableScorbot.h>
#include <ctime>

using namespace DataPrimitive;
using namespace DataManipolation;

// If the asker class is son of ObservableScorbot, it can be notifySettingBoard by the arriving of
// new data form scorbot
class ScorInterface : public ObservableScorbot{
public:

    virtual bool isConnect () = 0;
    /// Set Data
    virtual void goHome () = 0;
    virtual void sendVel (SpeedMot &sp) = 0;
    virtual void setSetting (SettingBoard_C &set) = 0;
    virtual void setSampleTimeEn (uint32_t sEn) = 0;         //Sample time in Microseconds 10^(-6)
    virtual void setSampleTimeCur (uint32_t sCur) = 0;       //Sample time in Microseconds 10^(-6)

    /// Get data
    // Return the last recive value
    virtual EncoderMot *getEncoder () = 0;
    virtual CurrentMot *getCurrent () = 0;
    virtual AllSensor *getSensor () = 0;
    virtual EncoderMot *getEncoder (struct timespec *t) = 0;
    virtual CurrentMot *getCurrent (struct timespec *t) = 0;
    virtual AllSensor *getSensor (struct timespec *en, struct timespec *cur) = 0;
    virtual SettingBoard_C *getSetting_local () = 0;     //last send board data
    virtual SettingBoard_C *getSetting_board () = 0;     //ask directly to board, wait constant time

    /// Valid question
    virtual bool isEncoderValid () = 0;      //true if Now <= LastPack+enSample
    virtual bool isCurrentValid () = 0;      //true if Now <= LastPack+curSample
    virtual bool isAllSensorValid () = 0;    //true if Encoder and Current in time

};

#endif //PCLISTENUART_SCORINTERFACE_H
