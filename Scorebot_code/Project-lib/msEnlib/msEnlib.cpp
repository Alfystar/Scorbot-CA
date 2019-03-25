/*
 * msEnlib.cpp
 *
 *  Created on: 25 mar 2019
 *      Author: alfy
 */
#include "msEnlib.h"

int bufMem[sizeMem];
cbuf_handle_t circularBuf;

byte enChA, enChB, ms;

void dsubFeedSetup() {
	memset(bufMem, 0, sizeMem);
	circularBuf = circular_buf_init((uint16_t *) bufMem, sizeMem);
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
	return PINC & 0b00111111;
}

int enRead() {	// Byte: [0]EnChA : [1]EnChB
	return (((PINK & 0b11000000) >> 6) | ((PINB & 0xF0) >> 2) << 8)
			| (PINK & 0b00111111);
}

void enDebug() {
	Serial.print("MS: ");
	Serial.print(ms, BIN);
	Serial.print("  enChA: ");
	Serial.print(enChA, BIN);
	Serial.print("  enChB: ");
	Serial.println(enChB, BIN);
}

void isrFunxEN() {
	circular_buf_put(circularBuf, enRead());
	Serial.println(enRead(), BIN);
}

