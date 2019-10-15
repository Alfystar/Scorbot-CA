//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_CURRENTMOT_H
#define SPIRASP_TERMINAL_CURRENTMOT_H
#include "../DataPrimitive.h"
#include <stdio.h>
#include <string.h>

namespace DataManipolation {
    using namespace DataPrimitive;
    class CurrentMot {
    public:
        CurrentMot(mCurrent& c);
        void changePack(mCurrent& c);
        void copyPack(CurrentMot& c);
        void copyPack(mCurrent & c);
        mCurrent& getCurrent();
        short getCurrent(motCode mot);
        void curSet(motCode mot, short cur);
        void printCurrent();
        static void printCurrent(mCurrent& c);

    private:
        mCurrent* curPack;
    };
};



#endif //SPIRASP_TERMINAL_CURRENTMOT_H
