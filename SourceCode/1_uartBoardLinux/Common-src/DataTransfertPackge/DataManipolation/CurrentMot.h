//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_CURRENTMOT_H
#define SPIRASP_TERMINAL_CURRENTMOT_H

#include <stdio.h>
#include <string.h>
#include "../DataPrimitive.h"
#include "../DataFactory.h"

#ifdef ScorboarFirmware
#include "Arduino.h"
#endif
namespace DataManipolation {
    using namespace DataPrimitive;

    class CurrentMot {
    public:
        CurrentMot(mCurrent &c);
        CurrentMot(mCurrent *c);
#ifdef linuxSide
        CurrentMot();   // creo al mio interno il Pack
        ~CurrentMot();
#endif
        void changePack(mCurrent &c);
        void changePack(mCurrent *c);
        void copyCur(CurrentMot &c);
        void copyCur(mCurrent *c);
        void copyCur(mCurrent &c);
        mCurrent &getCurrent();
        short getCurrent(motCode mot);
        void curSet(motCode mot, short cur);
        void printCurrent();
        static void printCurrent(mCurrent *c);
        static void printCurrent(mCurrent &c);
    private:
        mCurrent *curPack = nullptr;
#ifdef linuxSide
        bool curMine = false;
#endif
    };
};
#endif //SPIRASP_TERMINAL_CURRENTMOT_H
