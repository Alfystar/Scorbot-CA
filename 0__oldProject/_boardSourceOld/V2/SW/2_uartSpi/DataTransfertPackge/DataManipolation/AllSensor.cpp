//
// Created by alfyhack on 15/10/19.
//

#include "AllSensor.h"

namespace DataManipolation {
    AllSensor::AllSensor(mAll &all) :
            DataManipolation::CurrentMot(all.cur),
            DataManipolation::EncoderMot(all.en) {
        this->changePack(all);
    }

    void AllSensor::changePack(mAll &all) {
        this->allPack = &all;
    }

    void AllSensor::copyPack(mAll &all) {
        memcpy(this->allPack, &all, sizeof(mAll));
    }

    void AllSensor::copyPack(AllSensor &all) {
        this->copyPack(all.getSens());
    }

    mAll &AllSensor::getSens() {
        return *this->allPack;
    }

    void AllSensor::printAll() {
        this->printAll(this->getSens());
    }

    void AllSensor::printAll(mAll &all) {
        AllSensor::printEncoder(all.en);
        AllSensor::printCurrent(all.cur);
    }
};