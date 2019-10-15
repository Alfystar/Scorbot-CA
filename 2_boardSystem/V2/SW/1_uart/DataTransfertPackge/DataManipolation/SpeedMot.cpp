//
// Created by alfyhack on 15/10/19.
//

#include "SpeedMot.h"

namespace DataManipolation{


    SpeedMot::SpeedMot(mSpeed &s) {
        this->changePack(s);
    }

    void SpeedMot::changePack(mSpeed &speed) {
        this->speedPack=&speed;
    }

    void SpeedMot::copyPack(SpeedMot &speed) {
        this->copyPack(speed.getPwm());
    }

    void SpeedMot::copyPack(mSpeed &speed) {
        memcpy(this->speedPack,&speed, sizeof(mSpeed));
    }

    mSpeed &SpeedMot::getPwm() {
        return *this->speedPack;
    }

    short SpeedMot::getPwm(motCode mot) {
        return *(this->speedPack)[mot];
    }

    void SpeedMot::pwmSet(mSpeed &pwms) {
        this->pwmSet(pwms[Mot1], pwms[Mot2], pwms[Mot3], pwms[Mot4], pwms[Mot5], pwms[Mot6]);
    }

    void SpeedMot::pwmSet(short m1, short m2, short m3, short m4, short m5, short m6) {
        this->pwmSet(Mot1, m1);
        this->pwmSet(Mot2, m2);
        this->pwmSet(Mot3, m3);
        this->pwmSet(Mot4, m4);
        this->pwmSet(Mot5, m5);
        this->pwmSet(Mot6, m6);
    }

    void SpeedMot::pwmSet(motCode mot, short mVal) {
        if (mVal == freeRun || mVal == hardStop || mVal == softStop || mVal == ignore || abs(mVal) <= 255)
            *(this->speedPack)[mot] = mVal;
        else
            *(this->speedPack)[mot] = ignore;
    }

    void SpeedMot::printSpeed() {
        this->printSpeed(this->getPwm());
    }

    void SpeedMot::printSpeed(mSpeed &speed) {
#ifdef ScorboarFirmware
        Serial.flush();
        Serial.println("Receving Speed Settings:");
        for (byte i = Mot1; i < nMot; i++) {
            Serial.print("\tspeed[Mot");
            Serial.print(i+1);
            Serial.print("]:");
            Serial.println(this->speed[i]);
        }
#else
        printf("Speed:\t");
        for (char i = Mot1; i < nMot; i++) {
            printf("%d)%hd\t", i + 1, speed[i]);
        }
        printf("\n");
#endif
    }
};

