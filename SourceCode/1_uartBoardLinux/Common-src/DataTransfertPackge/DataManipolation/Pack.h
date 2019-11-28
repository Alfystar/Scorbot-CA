//
// Created by alfyhack on 15/10/19.
//

#ifndef Pack_H
#define Pack_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../DataPrimitive.h"
#include "CurrentMot.h"
#include "EncoderMot.h"
#include "AllSensor.h"
#include "SpeedMot.h"
#include "SettingBoard_C.h"

#ifdef linuxSide

#include "typePackWrongExcept.h"

using std::max;
#else
#include <Arduino.h>
#endif
#if !defined(linuxSide) && !defined(ScorboarFirmware)
#warning ScorboarFirmware define not Declared, if you are compiling library to Arduino, add at the end of gcc compiler: -D ScorboarFirmware
#endif
namespace DataManipolation {
    using namespace DataPrimitive;

    class Pack {
    public:
        Pack();
        Pack(Pack &p);
        Pack(SPIPACK &s);
        ~Pack();
        /// utility method
        void clearPack();

        /// send/recive information
        int sizePack();
        SPIPACK &getSPIPACK();
        void setPackType(packType t);
        packType getPackType();

        /// Data interact
        SettingBoard_C &setting(packDest dest);
        SettingBoard_C &settingByType();

        SpeedMot &speed();
        CurrentMot &current();
        EncoderMot &encoder();
        AllSensor &allSens();

        ///Debug
        static void printPack(Pack *p);
        void printPack();
    private:
        SPIPACK data;
        AllSensor *sens;
        SpeedMot *vel;
        CurrentMot *cur;
        EncoderMot *en;
        SettingBoard_C *sets2Ard;
        SettingBoard_C *sets2Rasp;
    };
};
#endif // Pack_H
