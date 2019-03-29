#include "spiScorebot.h"
/* Local Var*/
SPIPACK spiPack[2];
spiRecive reciveSpi[2];
spiSend _sendSpi;
volatile byte idTransf = 0; //Index of current Transfert
volatile byte dRecive = 0; //indica su quale buffer si sta scrivendo in questo momento
volatile byte newRecive = 0;

/*** HARDWARE ***/
void spiSetup() {
	pinMode(MISO, OUTPUT);
	memset((void *) &reciveSpi, 0, sizeof(spiRecive) * 2);
	idTransf = 0;
	SPCR = (1 << SPIE) | (1 << SPE); 	//attiva spi e abilita interrupt
	SPDR = 0;	 						//predispomgo che al primo invio invio 0
}

/*** ELABORATION ***/
/*
 void isrFunxISP() {
 if (idTransf == 0) {
 reciveSpi[dRecive].type = SPDR;
 preparaDati(reciveSpi[dRecive].type);
 //Serial.println(_sendSpi.pack.feedBack.encoder);	//print di test
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
 }*/


void preparaDati(SPIPACK *p) {
	switch (p->in.type) {
	case setPWM:
		memcpy(p->out.pack.en.passi, captureEn(), sizeof(setPWMSend));
		break;
	case getCurrent:
		memcpy(p->out.pack.curr.current, getAmpMots(), sizeof(getCurrentSend));
		break;
	case getSetting:
		memcpy(p->out.pack.prop.sets, (void *)&sets, sizeof(getSettingSend));
		break;
	case setSetting:
		break;
	case goHome:
		break;
	default:
		break;
	}
}

void isrFunxISP() {
	if (idTransf == 0) {
		spiPack[dRecive].in.type = SPDR;
		preparaDati(&spiPack[dRecive]);
		//Serial.println(_sendSpi.pack.feedBack.encoder);	//print di test
		SPDR = *((char *) &spiPack[dRecive].out.pack + idTransf);
		idTransf++;
	} else if (idTransf < sizeTypePack(&spiPack[dRecive])) {
		//salva nuovo dato
		char *mem = ((char *) &spiPack[dRecive].in.pack + idTransf);
		*mem = SPDR;
		SPDR = *((char *) &spiPack[dRecive].out.pack + idTransf);
		idTransf++;
	} else {
		//comunicazione all'ultimo byte
		char *mem = ((char *) &spiPack[dRecive].in.pack + idTransf);
		*mem = SPDR;
		SPDR = *((char *) &spiPack[dRecive].out.pack + idTransf);
		idTransf = 0;
		dRecive = !dRecive;
		newRecive = 1;
	}
}

/*Simile all'equivalente su rapsberry*/
int sizeTypePack(SPIPACK *s) {
	switch (s->in.type) {
	case setPWM:
		return max(sizeof(setPWMRecive), sizeof(setPWMSend));
		break;
	case getCurrent:
		return sizeof(getCurrentSend);
		break;
	case getSetting:
		return sizeof(getSettingSend);
		break;
	case setSetting:
		return sizeof(setSettingRecive);
		break;
	case goHome:
		return 0;
		break;
	}
	return 0;
}
/*
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
 */
/*** GET VALUE ***/
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
