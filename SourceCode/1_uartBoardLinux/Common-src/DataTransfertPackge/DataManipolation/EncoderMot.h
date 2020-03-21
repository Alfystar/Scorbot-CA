//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_ENCODERMOT_H
#define SPIRASP_TERMINAL_ENCODERMOT_H

#include <string.h>
#include <stdio.h>
#include "../DataPrimitive.h"
#include "../DataFactory.h"

#ifdef ScorboarFirmware
#include "Arduino.h"
#endif
namespace DataManipolation {
    using namespace DataPrimitive;

    class EncoderMot {
    public:
        EncoderMot(mEncoder &en);
        EncoderMot(mEncoder *en);
#ifdef linuxSide
        EncoderMot();   // creo al mio interno Pack
        ~EncoderMot();
#endif
        void changePack(mEncoder &en);
        void changePack(mEncoder *en);
        void copyEn(EncoderMot &en);
        void copyEn(mEncoder *en);
        void copyEn(mEncoder &en);
        mEncoder &getEn();
        short getEn(motCode mot);
        void enSet(motCode mot, short en);
        void printEncoder();
        static void printEncoder(mEncoder *en);
        static void printEncoder(mEncoder &en);
    private:
        mEncoder *enPack = nullptr;
#ifdef linuxSide
        bool enMine = false;
#endif

    };
};
#endif //SPIRASP_TERMINAL_ENCODERMOT_H
