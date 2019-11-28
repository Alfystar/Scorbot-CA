/*
 * msEnlib.cpp
 *
 *  Created on: 25 mar 2019
 *      Author: alfy
 */
#include "msEnlib.h"

/* LOCAL VAR */
int bufMem[sizeMem];
cbuf_handle_t circularBuf;
int passi[nMot];
int passiTemp[nMot];

/*** HARDWARE ***/
void dsubFeedSetup() {
    memset(bufMem, 0, sizeMem * sizeof(int));
    memset(passi, 0, nMot * sizeof(int));
    circularBuf = circular_buf_init((uint16_t *) bufMem, sizeMem);
    int ap;
    //ne metto 2 uguali per Predisporre la lettura
    circular_buf_put(circularBuf, enRead());
    circular_buf_get(circularBuf, (uint16_t *) &ap);
    circular_buf_put(circularBuf, ap);
    //make input pin
    DDRC &= 0b11000000;
    DDRK = 0;
    DDRB = 0x0F;

    //pull up pin
    PORTC = 0b00111111;
    PINK = 0xFF;
    PORTB = 0xF0;

    //PCINT Active
    PCICR = (1 << PCIE2) | (1 << PCIE0);        //abilita PCMSK0 & PCMSK2
    PCMSK2 = 0xFF;        //abilita tutti
    PCMSK0 = 0xF0;        //abilita la metà superiore
}

byte msRead() {
    return (~PINC) & 0b00111111;
}

int enRead() {    // Byte: [0]EnChA : [1]EnChB
    return ((((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2)) << 8)
           | (PINK & 0b00111111);
}

/*** ELABORATION ***/
void updateStepEn() {
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

//VARIABILI PRIVATE DI calcStep
#define im 0 //impossibile
//						0   1  2   3   4  5   6    7   8   9  10 11  12  13  14 15
int8_t enc_states[] = {0, -1, 1, im, 1, 0, im, -1, -1, im, 0, 1, im, 1, -1, 0}; /*[old]BA-BA[new]*/
byte chAold, chBold, chAnew, chBnew, code;

void calcStep(int oldEn, int newEn) {
    /* Monto i bit BA (A LSB)*/
    chAold = oldEn & 0x00FF;
    chBold = (oldEn & 0xFF00) >> 7;    //disallineo di 1 per semplificare l'or binario
    chAnew = newEn & 0x00FF;
    chBnew = (newEn & 0xFF00) >> 7;

    //Calcolo primo encoder
    code = ((chAold & 1) | (chBold & 0b10)) << 2;
    code |= ((chAnew & 1) | (chBnew & 0b10));
    passi[0] += (enc_states[code]);
    //Calcolo Restanti 6
    for (byte i = 1; i < nMot; i++) {
        chAold >>= 1;
        chBold >>= 1;
        code = ((chAold & 1) | (chBold & 0b10)) << 2;
        chAnew >>= 1;
        chBnew >>= 1;
        code |= ((chAnew & 1) | (chBnew & 0b10));
        passi[i] += (enc_states[code]);
    }
}

void isrFunxEN() {
    circular_buf_put(circularBuf, enRead());
    //Serial.println(enRead(), BIN);
}

/*** SET VALUE ***/
void setEn(byte m, int p) {
    passi[m] = p;
}

/*** GET VALUE ***/
int getEn(byte i) {
    return passi[i];
}

//Fotografa un istante e rimane quello fino alla successiva chiamata della funzione
int *captureEn() {
    memcpy(passiTemp, passi, sizeof(int) * nMot);
    return passiTemp;
}

/*** DEBUG & PRINT ***/
byte enChA, enChB, ms;

void enDebug() {
    ms = msRead();
    enChA = PINK & 0b00111111;
    enChB = ((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2);
    Serial.print("MS: ");
    Serial.print(ms, BIN);
    Serial.print("  enChA: ");
    Serial.print(enChA, BIN);
    Serial.print("  enChB: ");
    Serial.println(enChB, BIN);
}

void printSteps() {
    int *passiT = captureEn();
    for (byte i = 0; i < nMot; i++) {
        Serial.print("\tEn ");
        Serial.print(i + 1);
        Serial.print("= ");
        Serial.print(passiT[i]);
    }
    Serial.println();
}
