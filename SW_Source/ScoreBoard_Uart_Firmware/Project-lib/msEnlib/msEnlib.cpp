/*
 * msEnlib.cpp
 *
 *  Created on: 25 mar 2019
 *      Author: alfy
 */
#include "msEnlib.h"

namespace ScorebotRead {
    MotFeed::MotFeed (){
        //Memory clean
        memset(this->bufMem, 0, sizeMem * sizeof(mEncoder));
        memset(this->step, 0, sizeof(mEncoder));

        //make input pin
        DDRC &= 0b11000000;        //Fine Corsa
        DDRK = 0;                //Tutti e 6 chA e 2 chB
        DDRB = 0x0F;            //I 4 restanti chB

        //pull up pin
        PORTC = 0b00111111;        //Fine Corsa
        PINK = 0xFF;            //Tutti e 6 chA e 2 chB
        PORTB = 0xF0;            //I 4 restanti chB

        this->circularBuf = circular_buf_init((uint16_t *) this->bufMem, sizeMem);
        int ap;
        //ne metto 2 uguali per Predisporre la lettura
        circular_buf_put(this->circularBuf, this->enRead());
        circular_buf_get(this->circularBuf, (uint16_t *) &ap);
        circular_buf_put(this->circularBuf, ap);

        PCMSK2 = 0xFF;        //abilita tutti
        PCMSK0 = 0xF0;        //abilita la metà superiore

        MotFeed::interruptEn(true);
    }

    //VARIABILI PRIVATE DI calcStep
    //Dichiarate qui fisse e comuni a tutte le istanze
    //per accelerare l'elaborazione(riducendo gli accessi in memoria)
    #define im 0 //impossibile
    //						0   1  2   3   4  5   6    7   8   9  10 11  12  13  14 15
    int8_t const enc_states[] = {
            0, -1, 1, im, 1, 0, im, -1, -1, im, 0, 1, im, 1, -1, 0
    }; /*[old]BA-BA[new]*/
    byte chAold, chBold, chAnew, chBnew, code;

    void MotFeed::calcStep (int oldEn, int newEn){
        /* Monto i bit BA (A LSB)*/
        chAold = oldEn & 0x00FF;
        chBold = (oldEn & 0xFF00) >> 7;    //disallineo di 1 per semplificare l'or binario
        chAnew = newEn & 0x00FF;
        chBnew = (newEn & 0xFF00) >> 7;

        //Calcolo primo encoder
        code = ((chAold & 1) | (chBold & 0b10)) << 2;
        code |= ((chAnew & 1) | (chBnew & 0b10));
        this->step[0] += (enc_states[code]);
        //Calcolo Restanti 6
        for (byte i = 1; i < nMot; i++){
            chAold >>= 1;
            chBold >>= 1;
            code = ((chAold & 1) | (chBold & 0b10)) << 2;
            chAnew >>= 1;
            chBnew >>= 1;
            code |= ((chAnew & 1) | (chBnew & 0b10));
            this->step[i] += (enc_states[code]);
        }
    }

    unsigned short enNow, enOld;

    void MotFeed::isrFunxEN (){ //aggiungo solo se diverso e il buffer non vuoto
        circular_buf_put(circularBuf, enRead());
    }

    mEncoder &MotFeed::captureEn (){
        memcpy(this->tempStep, this->step, sizeof(mEncoder));
        return tempStep;
    }

    void MotFeed::setEn (motCode mot, short st){
        this->step[mot] = st;
    }

    short MotFeed::getEn (motCode mot){
        return this->step[mot];
    }

    byte enChA, enChB, ms;

    #ifdef ENCODER_DB
    void MotFeed::dSubDb (){
        ms = this->msRead();
        enChA = PINK & 0b00111111;
        enChB = ((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2);
        Db.print("MS: ");
        Db.print(ms, BIN);
        Db.print("  enChA: ");
        Db.print(enChA, BIN);
        Db.print("  enChB: ");
        Db.println(enChB, BIN);
        this->storedDataDb();
    }

    void MotFeed::storedDataDb (){
        Db.print("Circular size: ");
        Db.println(circular_buf_size(this->circularBuf));
    }
    mEncoder passiT;

    void MotFeed::printSteps (){
        memcpy(passiT, this->captureEn(), sizeof(mEncoder));
        for (byte i = 0; i < nMot; i++){
            Db.print("\tEn ");
            Db.print(i + 1);
            Db.print("= ");
            Db.print(passiT[i]);
            delay(1);
        }
        Db.println();
    }
    #endif

    byte MotFeed::msRead (){ //Ritorna MicroSwitch con logica 1-hot
        return (~PINC) & 0b00111111;
    }

    short MotFeed::enRead (){
        return ((((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2)) << 8) | (PINK & 0b00111111);
    }

    void MotFeed::updateStepEn (){
        int oldEn, newEn;
        while (!circular_buf_empty(circularBuf)){
            if (circular_buf_getLastOne(circularBuf, (uint16_t *) &oldEn))
                break;    //at start , there are only one value, no reading
            circular_buf_get(circularBuf, (uint16_t *) &newEn);
            calcStep(oldEn, newEn);
        }
    }

    void MotFeed::interruptEn (bool en){
        if (en){
            //PCINT Active
            PCICR = (1 << PCIE2) | (1 << PCIE0);        //abilita PCMSK0 & PCMSK2
        }
        else{
            PCICR = 0;         //disabilita Tutti PCMSKn
            PCMSK2 = 0;        //disabilita tutti
            PCMSK0 = 0;        //disabilita la metà superiore
        }
    }
}    //End namespace ScorebotRead


