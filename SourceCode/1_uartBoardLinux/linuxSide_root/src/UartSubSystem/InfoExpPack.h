//
// Created by alfyhack on 12/11/19.
//

#ifndef PCLISTENUART_INFOEXPPACK_H
#define PCLISTENUART_INFOEXPPACK_H

#include <DataTransfert_AllInclude.h>
#include "GetCom_int.h"
#include <time.h>

using namespace DataPrimitive;
using namespace DataManipolation;

class InfoExpPack {
public:
    static InfoExpPack &getInstance();

    /// Setting to board and class
    void setSampleTimeEn(uint32_t sEn);
    void setSampleTimeCur(uint32_t sCur);
    SettingBoard_C &settingSet(SettingBoard_C &set);
    SettingBoard_C &settingSet(settingsBoard &set);

    /// Get first to class and after to board
    SettingBoard_C &getSetting(GetCom_int *asker);
    EncoderMot &getEncoder(GetCom_int *asker);
    CurrentMot &getCurrent(GetCom_int *asker);
    AllSensor &getSensor(GetCom_int *asker);
private:
    static const InfoExpPack *instance;
    uint32_t sEn, sCur; // nanosecond time
    struct timespec lastEnSample, lastCurSample;
    // Read data without any change, isn't real time, but the monotonic encrease form unknow moment in the past
    // clock_gettime(CLOCK_MONOTONIC_RAW, struct timespec *tp);

    SettingBoard_C set;
    EncoderMot &en;
    CurrentMot &cur;
    AllSensor &allSensor;


    InfoExpPack();

};

#endif //PCLISTENUART_INFOEXPPACK_H
