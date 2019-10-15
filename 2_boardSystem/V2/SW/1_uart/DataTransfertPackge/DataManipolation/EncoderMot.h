//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_ENCODERMOT_H
#define SPIRASP_TERMINAL_ENCODERMOT_H
#include "../DataPrimitive.h"
#include <string.h>
#include <stdio.h>

namespace DataManipolation {
    using namespace DataPrimitive;
    class EncoderMot {
    public:
        EncoderMot(mEncoder& en);
        void changePack(mEncoder& en);
        void copyPack(EncoderMot& en);
        void copyPack(mEncoder & en);
        mEncoder& getEn();
        short getEn(motCode mot);
        void enSet(motCode mot, short en);
        void printEncoder();
        static void printEncoder(mEncoder& en);
    private:
        mEncoder* enPack;
    };
};


#endif //SPIRASP_TERMINAL_ENCODERMOT_H
