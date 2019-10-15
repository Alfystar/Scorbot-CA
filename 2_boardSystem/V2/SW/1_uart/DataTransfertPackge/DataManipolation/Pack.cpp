//
// Created by alfyhack on 03/09/19.
//
#include "Pack.h"
//#define PackDebug 1 //attiva/disattiva compilazione del codice per printare dati di debug della classe Pack

namespace DataManipolation {
    Pack::Pack() {
        this->clearPack();
        sens = new AllSensor(this->data.forRasp.up.sens);
        vel = new SpeedMot(this->data.forArd.up.speed);
        cur = new CurrentMot(this->data.forRasp.up.cur);
        en = new EncoderMot(this->data.forRasp.up.en);
        sets2Ard = new SettingBoard_C(this->data.forArd.up.prop);
        sets2Rasp = new SettingBoard_C(this->data.forRasp.up.prop);
#ifdef PackDebug
#ifdef ScorboarFirmware
        Serial.println("Data size:");
        Serial.print("packType size :");
        Serial.println(sizeof(packType));
        Serial.print("mEncoder size :");
        Serial.println(sizeof(mEncoder));
        Serial.print("mCurrent size :");
        Serial.println(sizeof(mCurrent));
        Serial.print("mAll size :");
        Serial.println(sizeof(mAll));
        Serial.print("settingsBoard size :");
        Serial.println(sizeof(settingsBoard));
        Serial.print("adcRef size :");
        Serial.println(sizeof(adcRef));
        Serial.print("bool(diff read) size :");
        Serial.println(sizeof(bool));
        Serial.print("pwmFreq size :");
        Serial.println(sizeof(pwmFreq));
        Serial.println();
#else
        printf("Data size:\n");
        printf("packType size : %d\n",sizeof(packType));
        printf("mEncoder size : %d\n",sizeof(mEncoder));
        printf("mCurrent size : %d\n",sizeof(mCurrent));
        printf("mAll size : %d\n",sizeof(mAll));
        printf("settingsBoard size : %d\n",sizeof(settingsBoard));
        printf("adcRef size : %d\n",sizeof(adcRef));
        printf("bool(diff read) size : %d\n",sizeof(bool));
        printf("pwmFreq size : %d\n\n",sizeof(pwmFreq));
#endif //#ifdef ScorboarFirmware

#endif //#ifdef PackDebug
    }

    Pack::Pack(Pack &p) {
        Pack(p.data);
    }

    Pack::Pack(SPIPACK &s) {
        Pack();
        memmove(&this->data, (const void *) &s, sizeof(SPIPACK));
    }

    Pack::~Pack() {
        //for now nothings to delete
    }

    void Pack::clearPack() {
        memset(&this->data, 0, sizeof(SPIPACK));
    }


    void Pack::printPack(Pack* p) {
        switch (p->data.type) {
            case PWMsend_EnRet:
            case PWMsend_CurRet:
            case PWMsend_AllRet:
#ifdef ScorboarFirmware
                Serial.flush();
                Serial.println("Master Ask 'PWMsend_EnRet || PWMsend_CurRet || PWMsend_AllRet', Parameter:");

#else
                printf("PackType: 'PWMsend_EnRet || PWMsend_CurRet || PWMsend_AllRet', Parameter:\n");
#endif
                /*Recive*/
                p->vel->printSpeed();
                /*Send*/
                if (p->getPackType() == PWMsend_EnRet || p->getPackType() == PWMsend_AllRet) {
                    p->en->printEncoder();
                }
                if (p->getPackType() == PWMsend_CurRet || p->getPackType() == PWMsend_AllRet) {
                    p->cur->printCurrent();
                }
                break;
            case SettingSet:
            case SettingGet:
                if (p->getPackType() == SettingSet) {
#ifdef ScorboarFirmware
                    Serial.flush();
                    Serial.println("Master Ask 'SettingSet':");
                    Serial.println("Recive new Settings:");
#else
                    printf("PackType: SettingSet\n");
                    printf("Sending new Settings:\n");
#endif
                    p->sets2Ard->printSetting();
                } else {
#ifdef ScorboarFirmware
                    Serial.flush();
                    Serial.println("Master Ask 'SettingGet':");
                    Serial.println("Sending my Settings:");
#else
                    printf("PackType: SettingGet\n");
                    printf("Recive current Settings:\n");
#endif
                    p->sets2Rasp->printSetting();
                }
                break;
            case goHome:
#ifdef ScorboarFirmware
                Serial.flush();
                Serial.println("Master Ask 'goHome', Parameter:\n");
                //Recive//
                Serial.print("\tNotting\n");
                //Send//
                Serial.print("\tNotting\n");
#else
                printf("PackType: goHomePack\n");
                printf("Sending: no parameters\n");
                printf("Reciving: no parameters\n");
#endif
                break;
        }
#ifdef ScorboarFirmware
        Serial.println("\n-------------------------------------------------------");
#else
        printf("\n-------------------------------------------------------\n");
#endif

    }

    void Pack::printPack() {
        this->printPack(this);
    }

    int Pack::sizePack() {
        switch (this->data.type) {
//            case invalid:
//                return -1;
//                break;
            case PWMsend_EnRet:
                return max(sizeof(mSpeed), sizeof(mEncoder));
                break;
            case PWMsend_CurRet:
                return max(sizeof(mSpeed), sizeof(mCurrent));
                break;
            case PWMsend_AllRet:
                return max(sizeof(mSpeed), sizeof(mAll));
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

    SettingBoard_C &Pack::setting(packDest dest) {
#ifndef ScorboarFirmware
        if (this->getPackType() != SettingSet && this->getPackType() != SettingGet)
            throw typePackWrongExcept("This pack not contain Settings");
#endif
        if(dest==pack4Ard)
            return *sets2Ard;
        else
            return *sets2Rasp;
    }

    SettingBoard_C &Pack::settingByType() {
#ifndef ScorboarFirmware
        if (this->getPackType() != SettingSet && this->getPackType() != SettingGet)
            throw typePackWrongExcept("This pack not contain Settings");
#endif
        if (this->data.type == SettingSet)
            return this->setting(pack4Ard);
        else if (this->data.type == SettingGet)
            return this->setting(pack4Rasp);
        return this->setting(pack4Ard);    //se non parte l'eccezione sono nell'arduino e ho la "fuga"
    }

    SpeedMot &Pack::speed() {
#ifndef ScorboarFirmware
        if (this->getPackType() != PWMsend_EnRet && this->getPackType() != PWMsend_CurRet && this->getPackType() != PWMsend_AllRet)
            throw typePackWrongExcept("This pack not contain Velocity");
#endif
        return *vel;
    }

    CurrentMot &Pack::current() {
#ifndef ScorboarFirmware
        if (this->getPackType() != PWMsend_CurRet)
            throw typePackWrongExcept("This pack not contain only Current");
#endif
        return *cur;
    }

    EncoderMot &Pack::encoder() {
#ifndef ScorboarFirmware
        if (this->getPackType() != PWMsend_EnRet)
            throw typePackWrongExcept("This pack not contain only Encoder");
#endif
        return *en;
    }

    AllSensor &Pack::allSens() {
#ifndef ScorboarFirmware
        if (this->getPackType() != PWMsend_AllRet)
            throw typePackWrongExcept("This pack not contain All Sensors");
#endif
        return *sens;
    }
}
