//
// Created by alfyhack on 15/10/19.
//

#include "CurrentMot.h"

namespace DataManipolation{
    CurrentMot::CurrentMot(mCurrent &c) {
        this->changePack(c);
    }

    void CurrentMot::changePack(mCurrent &c) {
        this->curPack=&c;
    }

    void CurrentMot::copyPack(CurrentMot &c) {
        this->copyPack(c.getCurrent());
    }

    void CurrentMot::copyPack(mCurrent &c) {
        memcpy(this->curPack,&c, sizeof(mCurrent));
    }

    mCurrent &CurrentMot::getCurrent() {
        return *this->curPack;
    }

    short CurrentMot::getCurrent(motCode mot) {
        return *(this->curPack)[mot];
    }

    void CurrentMot::curSet(motCode mot, short cur) {
        *(this->curPack)[mot]=cur;
    }

    void CurrentMot::printCurrent() {
        this->printCurrent(this->getCurrent());
    }

    void CurrentMot::printCurrent(mCurrent &c) {
#ifdef ScorboarFirmware
        Serial.flush();
        Serial.println("Sended Current Value:");
        for (byte i = Mot1; i < nMot; i++) {
            Serial.print("\tencoder[Mot");
            Serial.print(i+1);
            Serial.print("]:");
            Serial.println(this->c[i]);
        }
#else
        printf("Curr:\t");
        for (char i = Mot1; i < nMot; i++) {
            printf("%d)%hd\t", i + 1, c[i]);
        }
        printf("\n");
#endif
    }
};