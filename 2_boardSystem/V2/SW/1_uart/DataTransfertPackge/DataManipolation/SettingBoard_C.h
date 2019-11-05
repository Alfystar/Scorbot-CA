//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_SETTINGBOARD_C_H
#define SPIRASP_TERMINAL_SETTINGBOARD_C_H

#include <stdio.h>
#include <string.h>
#include "../DataPrimitive.h"

#ifdef ScorboarFirmware
#include "Arduino.h"
#endif

namespace DataManipolation {
    using namespace DataPrimitive;
    class SettingBoard_C {
    public:
        SettingBoard_C(settingsBoard& s);
        void changePack(settingsBoard& sets);
        void copyPack(SettingBoard_C& sets);
        void copyPack(settingsBoard& sets);
        settingsBoard& getSetting();

        void setMotorLimit(motCode mot, short enMax, short enMin, short cur);
        void setMaxEn(motCode mot, short en);
        void setMinEn(motCode mot, short en);
        void setMaxCurrentMed( motCode mot, short current);
        void setAdcRef(adcRef adc);
        void setAdcDiff(bool diff);
        void setPWMfreq(pwmFreq freq);

        void printSetting();
        static void printSetting(settingsBoard& set);


    private:
    settingsBoard* setPack;
    };
};



#endif //SPIRASP_TERMINAL_SETTINGBOARD_C_H
