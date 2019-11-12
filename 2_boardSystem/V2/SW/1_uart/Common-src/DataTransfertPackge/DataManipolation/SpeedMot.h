//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_SPEEDMOT_H
#define SPIRASP_TERMINAL_SPEEDMOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DataPrimitive.h"

#ifdef ScorboarFirmware
#include "Arduino.h"
#endif

namespace DataManipolation {
    using namespace DataPrimitive;
    class SpeedMot {
    public:
        SpeedMot(mSpeed& s);
        SpeedMot(mSpeed *s);
        void changePack(mSpeed& speed);
        void copyPack(SpeedMot& speed);
        void copyPack(mSpeed& speed);
        mSpeed& getPwm();
        short getPwm(motCode mot);
        void pwmSet(mSpeed &pwms);
        void pwmSet(short m1, short m2, short m3, short m4, short m5, short m6);
        void pwmSet(motCode mot, short pwm);
        void printSpeed();
        static void printSpeed(mSpeed *speed);
        static void printSpeed(mSpeed& speed);
    private:
        mSpeed* speedPack;
    };
};


#endif //SPIRASP_TERMINAL_SPEEDMOT_H
