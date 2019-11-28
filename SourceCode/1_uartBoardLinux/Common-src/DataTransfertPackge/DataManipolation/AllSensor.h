//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_ALLSENSOR_H
#define SPIRASP_TERMINAL_ALLSENSOR_H

#include "EncoderMot.h"
#include "CurrentMot.h"
#include "../DataPrimitive.h"
#include "../DataFactory.h"

namespace DataManipolation {
    using namespace DataPrimitive;

    class AllSensor : public CurrentMot, public EncoderMot {
    public:
        AllSensor(mAll &all);
        AllSensor(mAll *all);
#ifdef linuxSide
        AllSensor();   // creo al mio interno il Pack
        ~AllSensor();
#endif
        void changePack(mAll &all);
        void copyPack(mAll *all);
        void copyPack(mAll &all);
        void copyPack(AllSensor &all);
        mAll &getSens();
        void printAll();
        static void printAll(mAll *all);
        static void printAll(mAll &all);
    private:
        mAll *allPack;
#ifdef linuxSide
        bool allMine = false;
#endif
    };
};
#endif //SPIRASP_TERMINAL_ALLSENSOR_H
