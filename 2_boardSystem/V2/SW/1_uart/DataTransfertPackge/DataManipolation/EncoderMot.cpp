//
// Created by alfyhack on 15/10/19.
//

#include "EncoderMot.h"

namespace DataManipolation{
    EncoderMot::EncoderMot(mEncoder &en) {
        this->enPack=&en;
    }

    void EncoderMot::changePack(mEncoder &en) {
        this->enPack=&en;
    }

    void EncoderMot::copyEn(EncoderMot &en) {
        this->copyEn(en.getEn());
    }

    void EncoderMot::copyEn(mEncoder &en) {
        memcpy(this->enPack,&en, sizeof(mEncoder));
    }

    mEncoder &EncoderMot::getEn() {
        return *this->enPack;
    }

    short EncoderMot::getEn(motCode mot) {
        return *(this->enPack)[mot];
    }

    void EncoderMot::enSet(motCode mot, short en) {
        *(this->enPack)[mot] = en;
    }

    void EncoderMot::printEncoder() {
        this->printEncoder(this->getEn());
    }

    void EncoderMot::printEncoder(mEncoder &en) {
#ifdef ScorboarFirmware
        Serial.flush();
        Serial.println("Sended Encoder Step:");
        for (byte i = Mot1; i < nMot; i++) {
            Serial.print("\tencoder[Mot");
            Serial.print(i+1);
            Serial.print("]:");
            Serial.println(en[i]);
        }
#else
        printf("En:\t");
        for (char i = Mot1; i < nMot; i++) {
            printf("%d)%hd\t", i + 1, en[i]);
        }
        printf("\n");
#endif
    }
};
