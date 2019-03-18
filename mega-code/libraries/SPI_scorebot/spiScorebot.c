#include "spiScorebot.h"

/* Internal Varable*/
volatile byte idTransf = 0; //Index of current Transfert
volatile spiRecive reciveSpi[2];
volatile byte dRecive = 0; //indica su quale buffer si sta scrivendo in questo momento
volatile spiSend _sendSpi;
volatile byte newRecive = 0;

void spiSetup() {
	pinMode(MISO, OUTPUT);
	volatile_memset(&reciveSpi, 0, sizeof(spiRecive) * 2);
	idTransf = 0;
	SPCR = (1 << SPIE) | (1 << SPE); 	//attiva spi e abilita interrupt
	SPDR = 0;	 						//predispomgo che al primo invio invio 0
}

volatile spiRecive * getLastRecive() {
	return &reciveSpi[dRecive];
}

byte spiAvailable() {
	if (newRecive != 0) {
		newRecive = 0;
		return 1;
	} else
		return 0;
}

ISR(SPI_STC_vect) {
	if (idTransf == 0) {
		reciveSpi[dRecive].type = SPDR;
		preparaDati(reciveSpi[dRecive].type);
		SPDR = *((char *) &_sendSpi + idTransf);
		idTransf++;
	} else if (idTransf < limitiDati(reciveSpi[dRecive].type)) {
		//salva nuovo dato
		volatile char *mem = ((volatile char *) &reciveSpi[dRecive] + idTransf);
		*mem = SPDR;
		SPDR = *((char *) &_sendSpi + idTransf);
		idTransf++;
	} else {
		//comunicazione all'ultimo byte
		volatile char *mem = ((volatile char *) &reciveSpi[dRecive] + idTransf);
		*mem = SPDR;
		SPDR = *((char *) &_sendSpi + idTransf);
		idTransf = 0;
		dRecive = !dRecive;
		newRecive = 1;
	}
}
/*
 void isrFunxISP() {
 if (idTransf == 0) {
 reciveSpi[dRecive].type = SPDR;
 preparaDati(reciveSpi[dRecive].type);
 SPDR = *((char *) &_sendSpi + idTransf);
 idTransf++;
 } else if (idTransf < limitiDati(reciveSpi[dRecive].type)) {
 //salva nuovo dato
 volatile char *mem = ((volatile char *) &reciveSpi[dRecive] + idTransf);
 *mem = SPDR;
 SPDR = *((char *) &_sendSpi + idTransf);
 idTransf++;
 } else {
 //comunicazione all'ultimo byte
 volatile char *mem = ((volatile char *) &reciveSpi[dRecive] + idTransf);
 *mem = SPDR;
 SPDR = *((char *) &_sendSpi + idTransf);
 idTransf = 0;
 dRecive = !dRecive;
 newRecive = 1;
 }
 }
 */

void preparaDati(char type) {
	unsigned char hello[] = "Hello guy\n";
	switch (type) {
	case setPWM:
		volatile_memcpy(&_sendSpi.pack.feedBack.encoder, hello, 32);
		break;
	case getSetting:
		break;
	case setSetting:
		break;
	case setHome:
		break;
	case goHome:
		break;
	default:
		break;
	}
}

int limitiDati(char type) {
	switch (type) {
	case setPWM:
		return 32;
		break;
	case getSetting:
		return 32;
		break;
	case setSetting:
		return 32;
		break;
	case setHome:
		return 32;
		break;
	case goHome:
		return 32;
		break;
	default:
		return 32;
		break;
	}
}

volatile void * volatile_memcpy(volatile void *d, volatile void *s, size_t n) {
	volatile char *mem = NULL;
	for (size_t i = 0; i < n; i++) {
		mem = d + i;
		*mem = *((volatile char *) (s + i));
	}
	return d;
}

//void *memset(void *s, int c, size_t n);
volatile void * volatile_memset(volatile void *s, int c, size_t n) {
	volatile char *mem = NULL;
	for (size_t i = 0; i < n; i++) {
		mem = s + i;
		*mem = c;
	}
	return s;
}
