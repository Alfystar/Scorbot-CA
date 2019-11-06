//
// Created by alfyhack on 15/10/19.
//

#ifndef SPIRASP_TERMINAL_ALLSENSOR_H
#define SPIRASP_TERMINAL_ALLSENSOR_H
#include "../DataPrimitive.h"
#include "EncoderMot.h"
#include "CurrentMot.h"
namespace DataManipolation {
    using namespace DataPrimitive;

    class AllSensor : public CurrentMot, public EncoderMot {
    public:
        AllSensor(mAll& all);
        void changePack(mAll& all);
        void copyPack(mAll& all);
        void copyPack(AllSensor& all);
        mAll& getSens();
        void printAll();
        static void printAll(mAll& all);
    private:
        mAll* allPack;
    };
};


#endif //SPIRASP_TERMINAL_ALLSENSOR_H
