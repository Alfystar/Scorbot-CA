#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H

#include "Arduino.h"
#include <stdlib.h>
#include "../globalDef.h"

//#define ISPDEBUG 1 //attiva/disattiva compilazione del codice per printare i byte della spi

using namespace spiPack;
namespace InternalDevice {
    class SpiDevice {
    public:
        SpiDevice();
        //static SpiDevice& getIstance();
        //## EXECUTION ##//
        void isrFunxISP();
        void dataLoad(Pack &p);
        //## GET VALUE ##//
        byte spiAvailable();
        Pack &getLastRecive();
    private:
        Pack sp[2];
        volatile byte idTransf, startConv, dRecive, newRecive;
        //static SpiDevice *instance;
        //## HARDWARE ##//
    };
} //END namespace SpiLib_Ard

#ifndef __IN_ECLIPSE__

#include "spiScorebot.cpp"

#endif
#endif
