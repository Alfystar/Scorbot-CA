//
// Created by alfyhack on 03/09/19.
//
#include "SpiPack.h"

namespace spiPack {
    Pack::Pack() {
        this->clearPack();
    }

    Pack::Pack(Pack &p) {
        Pack(p.data);
    }

    Pack::Pack(SPIPACK &s) {
        memmove(&this->data, (const void *) &s, sizeof(SPIPACK));
    }

    Pack::~Pack() {
//for now nothings to delete
    }

    void Pack::clearPack() {
        memset(&this->data, 0, sizeof(SPIPACK));
    }

    void Pack::printPack() {
        switch (this->data.type) {
            case PWMsend_EnRet:
                printf("PackType: PWMsend_EnRet\n");
                printf("Sending actual speed:\n");
                printf("Vel:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forArd.up.speed[Mot1 + i]);
                }
                printf("\nReciving actual encoder:\n");
                printf("En:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forRasp.up.en[Mot1 + i]);
                }
                break;
            case CurrentGet:
                printf("PackType: CurrentGet\n");
                printf("Sending: no parameters\n");
                printf("Reciving actual currents:\n");
                printf("Curr:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forRasp.up.cur[Mot1 + i]);
                }
                break;
            case SettingGet:
                printf("PackType: SettingGet\n");
                printf("Reciving actual settings:\n");
                printf("maxEn:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forRasp.up.prop.maxEn[Mot1 + i]);
                }
                printf("\nminEn:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forRasp.up.prop.minEn[Mot1 + i]);
                }
                printf("\nmaxCurrMed:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forRasp.up.prop.maxCurrMed[Mot1 + i]);
                }
                printf("\nadcReference voltage:\t");
                switch (this->data.forArd.up.prop.adcVref) {
                    case in1V1:
                        printf("Internal Reference 1.1V\n");
                        break;
                    case in2V56:
                        printf("Internal Reference 2.56V\n");
                        break;
                    case ext:
                        printf("External Source (Trimmer Reference)\n");
                        break;
                }
                break;
            case SettingSet:
                printf("PackType: SettingSet\n");
                printf("Sending this parameters\n");
                printf("maxEn:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forArd.up.prop.maxEn[Mot1 + i]);
                }
                printf("\nminEn:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forArd.up.prop.minEn[Mot1 + i]);
                }
                printf("\nmaxCurrMed:\t");
                for (int i = 0; i < nMot; i++) {
                    printf("%d)%hd\t", i + 1, this->data.forArd.up.prop.maxCurrMed[Mot1 + i]);
                }
                printf("\nadcReference voltage:\t");
                switch (this->data.forArd.up.prop.adcVref) {
                    case in1V1:
                        printf("Internal Reference 1.1V\n");
                        break;
                    case in2V56:
                        printf("Internal Reference 2.56V\n");
                        break;
                    case ext:
                        printf("External Source (Trimmer Reference)\n");
                        break;
                }
                printf("Reciving: no parameters:\n");
                break;
            case goHome:
                printf("PackType: goHomePack\n");
                printf("Sending: no parameters\n");
                printf("Reciving: no parameters\n");
                break;
        }
        printf("\n-------------------------------------------------------\n");
    }

    int Pack::sizePack() {
        switch (this->data.type) {
            case invalid:
                return -1;
                break;
            case PWMsend_EnRet:
                return std::max(sizeof(mSpeed), sizeof(mEncoder));
                break;
            case PWMsend_CurRet:
                return std::max(sizeof(mSpeed), sizeof(mCurrent));
                break;
            case PWMsend_AllRet:
                return std::max(sizeof(mSpeed), sizeof(mAll));
                break;
            case CurrentGet:
                return sizeof(mCurrent);
                break;
            case SettingGet:
                return sizeof(settingsBoard);
                break;
            case SettingSet:
                return sizeof(settingsBoard);
                break;
            case goHome:
                return 0;
                break;
        }
        return -1;
    }

    SPIPACK &Pack::getSPIPACK() {
        return this->data;
    }

    void Pack::setPackType(packType t) {
        this->data.type = t;
    }

    packType Pack::getPackType() {
        return this->data.type;
    }

    void Pack::pwmSet(mSpeed &pwms) {
        this->pwmSet(pwms[Mot1], pwms[Mot2], pwms[Mot3], pwms[Mot4], pwms[Mot5], pwms[Mot6]);
    }

    void Pack::pwmSet(short m1, short m2, short m3, short m4, short m5, short m6) {
        this->pwmSet(Mot1, m1);
        this->pwmSet(Mot2, m2);
        this->pwmSet(Mot3, m3);
        this->pwmSet(Mot4, m4);
        this->pwmSet(Mot5, m5);
        this->pwmSet(Mot6, m6);
    }

    void Pack::pwmSet(motCode mot, short mVal) {
        if (mVal == freeRun || mVal == hardStop || mVal == softStop || mVal == ignore || abs(mVal) <= 255)
            this->data.forArd.up.speed[mot] = mVal;
        else
            this->data.forArd.up.speed[mot] = ignore;
    }

    void Pack::setEncoder(mEncoder &en) {
        if(this->data.type==PWMsend_EnRet)
            memmove(&this->data.forRasp.up.en, &en, sizeof(mEncoder));
        else if(this->data.type==PWMsend_AllRet)
            memmove(&this->data.forRasp.up.sens.en, &en, sizeof(mEncoder));
#ifndef Arduino_h
        else
            throw typePackWrongExcept("This pack can't set Encoder");
#endif
    }

    void Pack::setEncoder(motCode mot, short en) {
        if(this->data.type==PWMsend_EnRet)
            this->data.forRasp.up.cur[mot] = en;
        else if(this->data.type==PWMsend_AllRet)
            this->data.forRasp.up.sens.cur[mot] = en;
#ifndef Arduino_h
        else
            throw typePackWrongExcept("This pack can't set Encoder");
#endif
    }

    void Pack::setCurrent(mCurrent &c) {
        if(this->data.type==PWMsend_CurRet)
            memmove(&this->data.forRasp.up.cur, &c, sizeof(mCurrent));
        else if(this->data.type==PWMsend_AllRet)
            memmove(&this->data.forRasp.up.sens.cur, &c, sizeof(mCurrent));
#ifndef Arduino_h
        else
            throw typePackWrongExcept("This pack can't set Current");
#endif
    }

    void Pack::setCurrent(motCode mot, short cur) {
        if (cur < 0) cur = 0;
        if(this->data.type==PWMsend_CurRet)
            this->data.forRasp.up.cur[mot] = cur;
        else if(this->data.type==PWMsend_AllRet)
            this->data.forRasp.up.sens.cur[mot] = cur;
#ifndef Arduino_h
        else
            throw typePackWrongExcept("This pack can't set Encoder");
#endif
    }

    void Pack::setSetting(settingsBoard &sets, packDest dest) {
        if (dest == pack4Ard)
            memmove(&this->data.forRasp.up.prop, &sets, sizeof(settingsBoard));
        else if (dest == pack4Rasp)
            memmove(&this->data.forArd.up.prop, &sets, sizeof(settingsBoard));
    }

    void Pack::setMotorLimit(packDest dest, motCode mot, short enMax, short enMin, short cur) {
        //Set variable inside the pack to send-out
        this->setMaxEn(dest, mot, enMax);
        this->setMinEn(dest, mot, enMin);
        this->setMaxCurrentMed(dest, mot, enMax);
    }

    void Pack::setMaxEn(packDest dest, motCode mot, short en) {
        //Set variable inside the pack to send-out
        if (dest == pack4Ard)
            this->data.forRasp.up.prop.maxEn[mot] = en;
        else if (dest == pack4Rasp)
            this->data.forArd.up.prop.maxEn[mot] = en;
    }

    void Pack::setMinEn(packDest dest, motCode mot, short en) {
        //Set variable inside the pack to send-out
        if (dest == pack4Ard)
            this->data.forRasp.up.prop.minEn[mot] = en;
        else if (dest == pack4Rasp)
            this->data.forArd.up.prop.minEn[mot] = en;
    }

    void Pack::setMaxCurrentMed(packDest dest, motCode mot, short current) {
        //Set variable inside the pack to send-out
        if (dest == pack4Ard)
            this->data.forRasp.up.prop.maxCurrMed[mot] = current;
        else if (dest == pack4Rasp)
            this->data.forArd.up.prop.maxCurrMed[mot] = current;
    }

    void Pack::setAdcRef(packDest dest, adcRef adc) {
        //Set variable inside the pack to send-out
        if (dest == pack4Ard)
            this->data.forRasp.up.prop.adcVref = adc;
        else if (dest == pack4Rasp)
            this->data.forArd.up.prop.adcVref = adc;
    }

    mSpeed &Pack::getPwm() {
#ifndef Arduino_h
        if(this->data.type!=PWMsend_EnRet && this->data.type!=PWMsend_CurRet && this->data.type!=PWMsend_AllRet)
            throw typePackWrongExcept("This pack not contain PWM");
#endif
        return this->data.forArd.up.speed;
    }

    mEncoder &Pack::getEncoder() {
        if(this->data.type==PWMsend_EnRet)
            return this->data.forRasp.up.en;
        else if(this->data.type==PWMsend_AllRet)
            return this->data.forRasp.up.sens.en;
#ifndef Arduino_h
        else
            throw typePackWrongExcept("This pack not contain Encoder");
#endif
    }

    mCurrent &Pack::getCurrent() {
        if(this->data.type==PWMsend_CurRet)
            return this->data.forRasp.up.cur;
        else if(this->data.type==PWMsend_AllRet)
            return this->data.forRasp.up.sens.cur;
#ifndef Arduino_h
        else
            throw typePackWrongExcept("This pack not contain Current");
#endif
    }

    mAll &Pack::getSens() noexcept(false) {
        if(this->data.type==PWMsend_AllRet)
            return this->data.forRasp.up.sens;
#ifndef Arduino_h
        else
            throw typePackWrongExcept("This pack not contain Sensor Data");
#endif
    }

    settingsBoard &Pack::getSetting(packDest dest) {
#ifndef Arduino_h
        if(this->data.type!=SettingSet && this->data.type!=SettingGet)
        throw typePackWrongExcept("This pack not contain Settings");
#endif
        if (dest == pack4Ard)
            return this->data.forArd.up.prop;
        else if (dest == pack4Rasp)
            return this->data.forRasp.up.prop;
    }

    settingsBoard &Pack::getSetting() noexcept(false) {
#ifndef Arduino_h
        if(this->data.type!=SettingSet && this->data.type!=SettingGet)
            throw typePackWrongExcept("This pack not contain Settings");
#endif
        if (this->data.type==SettingSet)
            return this->data.forArd.up.prop;
        else if (this->data.type==SettingGet)
            return this->data.forRasp.up.prop;
    }

    SPIPACK *makeSPIPACK() {
        SPIPACK *p = (SPIPACK *) malloc(sizeof(SPIPACK));
        memset(p, 0, sizeof(SPIPACK));
        return p;
    }

    void freeSPIPACK(SPIPACK *p) {
        free(p);
    }

}
