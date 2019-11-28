/*
 * msEnlib.cpp
 *
 *  Created on: 25 mar 2019
 *      Author: alfy
 */
#include "msEnlib.h"

namespace ScorebotRead {
    ScorFeed::ScorFeed() {
        //Memory clean
        memset(this->bufMem, 0, sizeMem * sizeof(mEncoder));
        memset(this->step, 0, sizeof(mEncoder));

        //make input pin
        DDRC &= 0b11000000;
        DDRK = 0;
        DDRB = 0x0F;

        //pull up pin
        PORTC = 0b00111111;
        PINK = 0xFF;
        PORTB = 0xF0;
        this->circularBuf = circular_buf_init((uint16_t *)
                                                      this->bufMem, sizeMem);
        int ap;
        //ne metto 2 uguali per Predisporre la lettura
        circular_buf_put(this->circularBuf, this->enRead());
        circular_buf_get(this->circularBuf, (uint16_t *) &ap);
        circular_buf_put(this->circularBuf, ap);

        //Uso il Timer/Counter5 e il suo Overflow Flag (TOV5) per generare l'interrupt ogni ~4Kh
        //La modalità di default del timer 5 è in 8-bit phase correct pwm mode e prescaler a 64 bit
        //Mantengo utilizzabili i pin D44, D45 & D46 come normali PWM ma a 3921.16 Hz (default a 490.20 Hz)
#ifdef TIMER5OVF_EN
        TCCR5B = (TCCR5B & B11111000) | B00000010; // set timer 5 divisor to 8 for PWM frequency of 3921.16 Hz
        //TCCR5B = (TCCR5B & B11111000) | B00000001; // set timer  divisor to     1 for PWM frequency of 31372.55 Hz
        TCNT5 = 0;
#endif
#ifdef PCINT_EN
        PCMSK2 = 0xFF;        //abilita tutti
        PCMSK0 = 0xF0;        //abilita la metà superiore
#endif
        ScorFeed::interruptEn(true);


    }

//VARIABILI PRIVATE DI calcStep
//Dichiarate qui fisse e comuni a tutte le istanze
//per accelerare l'elaborazione(riducendo gli accessi in memoria)
#define im 0 //impossibile
//						0   1  2   3   4  5   6    7   8   9  10 11  12  13  14 15
    int8_t const enc_states[] = {0, -1, 1, im, 1, 0, im, -1, -1, im, 0, 1, im,
                                 1, -1, 0}; /*[old]BA-BA[new]*/
    byte chAold, chBold, chAnew, chBnew, code;

    void ScorFeed::calcStep(int oldEn, int newEn) {
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
        for (byte i = 1; i < nMot; i++) {
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

    void ScorFeed::isrFunxEN() { //aggiungo solo se diverso e il buffer non vuoto
        circular_buf_put(circularBuf, enRead());
        /*
        enOld=enNow;
        enNow=enRead();
        if (enNow!=enOld)
            circular_buf_put(circularBuf, enNow);
        if(circular_buf_size(circularBuf)>200)
            this->updateStepEn();
            */
    }

    mEncoder &ScorFeed::captureEn() {
        memcpy(this->tempStep, this->step, sizeof(mEncoder));
        return tempStep;
    }

    void ScorFeed::setEn(motCode mot, short st) {
        this->step[mot] = st;
    }

    short ScorFeed::getEn(motCode mot) {
        return this->step[mot];
    }

    byte enChA, enChB, ms;

    void ScorFeed::dSubDebug() {
        ms = this->msRead();
        enChA = PINK & 0b00111111;
        enChB = ((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2);
        Serial.print("MS: ");
        Serial.print(ms, BIN);
        Serial.print("  enChA: ");
        Serial.print(enChA, BIN);
        Serial.print("  enChB: ");
        Serial.println(enChB, BIN);
        this->storedData();
    }

    void ScorFeed::storedData() {
        Serial.print("Circular size: ");
        Serial.println(circular_buf_size(this->circularBuf));
    }

    mEncoder passiT;

    void ScorFeed::printSteps() {
        memcpy(passiT, this->captureEn(), sizeof(mEncoder));
        for (byte i = 0; i < nMot; i++) {
            Serial.print("\tEn ");
            Serial.print(i + 1);
            Serial.print("= ");
            Serial.print(passiT[i]);
            delay(1);
        }
        Serial.println();
    }

    byte ScorFeed::msRead() {
        return (~PINC) & 0b00111111;
    }

    short ScorFeed::enRead() {
        return ((((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2)) << 8)
               | (PINK & 0b00111111);

    }

    void ScorFeed::updateStepEn() {
        int oldEn, newEn;
        while (!circular_buf_empty(circularBuf)) {
            if (circular_buf_getLastOne(circularBuf, (uint16_t *) &oldEn))
                break;    //at start , there are only one value, no reading
            circular_buf_get(circularBuf, (uint16_t *) &newEn);
            /*
             Serial.print("old=");
             Serial.print(oldEn,BIN);
             Serial.print(" new=");
             Serial.println(newEn,BIN);
             */
            calcStep(oldEn, newEn);
        }
        //Serial.println("END");
    }

    void ScorFeed::interruptEn(bool en) {
        //Serial.println("Enable ADC interrupt");
        if (en) {
#ifdef TIMER5OVF_EN
            sbi(TIMSK5, TOIE5);    //Timer/Counter, Overflow Interrupt Enable (timer5_ovf_vect)
#endif
#ifdef PCINT_EN
            //PCINT Active

            PCICR = (1 << PCIE2) | (1 << PCIE0);        //abilita PCMSK0 & PCMSK2
#endif
        } else {
#ifdef TIMER5OVF_EN
            cbi(TIMSK5, TOIE5);    //Timer/Counter, Overflow Interrupt Disable(timer5_ovf_vect)
#endif
#ifdef PCINT_EN
            PCICR = 0;        //disabilita Tutti PCMSKn
            PCMSK2 = 0;        //disabilita tutti
            PCMSK0 = 0;        //disabilita la metà superiore
#endif
        }
    }
}    //End namespace ScorebotRead


