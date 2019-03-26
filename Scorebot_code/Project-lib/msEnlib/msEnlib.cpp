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

	//ne metto 2 uguali per Predisporre la lettura
	circular_buf_put(circularBuf, enRead());
	circular_buf_put(circularBuf, enRead());
	//make input pin
	DDRC &= 0b11000000;
	DDRK = 0;
	DDRB = 0x0F;

	//pull up pin
	PORTC = 0b00111111;
	PINK = 0xFF;
	PORTB = 0xF0;

	//PCINT Active
	PCICR = (1 << PCIE2) | (1 << PCIE0);		//abilita PCMSK0 & PCMSK2
	PCMSK2 = 0xFF;		//abilita tutti
	PCMSK0 = 0xF0;		//abilita la metà superiore
}

byte msRead() {
	return ~PINC & 0b00111111;
}

int enRead() {	// Byte: [0]EnChA : [1]EnChB
	return (((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2) << 8)
			| (PINK & 0b00111111);
}

/*** ELABORATION ***/
void updateStepEn() {
	int oldEn, newEn;
	while (!circular_buf_empty(circularBuf)) {
		if (circular_buf_getLastOne(circularBuf, (uint16_t *) &oldEn))
			break;	//at start , there are only one value, no reading
		circular_buf_get(circularBuf, (uint16_t *) &newEn);
		calcStep(oldEn, newEn);
	}
}

//VARIABILI PRIVATE DI calcStep
int8_t enc_states[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };
byte chAold, chBold, chAnew, chBnew, code;
void calcStep(int oldEn, int newEn) {
	/* Monto i bit BA (A LSB)*/
	chAold = oldEn & 0x00FF;
	chBold = (oldEn & 0xFF00) >> 7;	//disallineo di 1 per semplificare l'or binario
	chAnew = newEn & 0x00FF;
	chBnew = (newEn & 0xFF00) >> 7;
	for (byte i = 0; i < nMot; i++) {
		chAold >>= i;
		chBold >>= i;
		code = ((chAold & 1) | (chBold & 0b10)) << 2;
		chAnew >>= i;
		chBnew >>= i;
		code |= ((chAnew & 1) | (chBnew & 0b10));
		passi[i] += (enc_states[code]);
	}
}

void isrFunxEN() {
	circular_buf_put(circularBuf, enRead());
	//Serial.println(enRead(), BIN);
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

void printEnAll() {
	int * passi = captureEn();
	for (byte i = 0; i++; i < nMot) {
		Serial.print("\tEn ");
		Serial.print(i);
		Serial.print("=");
		Serial.print(passi[i]);
	}
	Serial.println();
}
