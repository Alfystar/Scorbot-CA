#include "spiScorebot.h"
/* Local Var*/
SPIPACK spiPack[2];
volatile byte idTransf = 0; //Index of current Transfert
volatile byte dRecive = 0; //indica su quale buffer si sta scrivendo in questo momento
volatile byte newRecive = 0;

/*** HARDWARE ***/
void spiSetup() {
	pinMode(MISO, OUTPUT);
	memset((void *) spiPack, 0, sizeof(SPIPACK) * 2);
	idTransf = 0;
	SPCR = (1 << SPIE) | (1 << SPE); 	//attiva spi e abilita interrupt
	SPDR = 0;	 						//predispomgo che al primo invio invio 0
}

/*** ELABORATION ***/
char *mem;
void isrFunxISP() {
	if (idTransf == 0) {
		spiPack[dRecive].in.type = SPDR;
		preparaDati(&spiPack[dRecive]);
		SPDR = *((char *) &spiPack[dRecive].out.pack + idTransf);
		idTransf++;
	} else if (idTransf < sizeTypePack(&spiPack[dRecive])) {
		//salva nuovo dato
		mem = ((char *) &spiPack[dRecive].in.pack + idTransf);
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

void preparaDati(SPIPACK *p) {
	switch (p->in.type) {
	case setPWM:
		memcpy(p->out.pack.en.passi, captureEn(), sizeof(setPWMSend));
		break;
	case getCurrent:
		memcpy(p->out.pack.curr.current, getAmpMots(), sizeof(getCurrentSend));
		break;
	case getSetting:
		memcpy(&p->out.pack.prop.sets, &sets, sizeof(getSettingSend));
		break;
	case setSetting:
		break;
	case goHome:
		break;
	default:
		break;
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

/*** GET VALUE ***/
SPIPACK * getLastRecive() {
	return &spiPack[dRecive];
}

byte spiAvailable() {
	if (newRecive != 0) {
		newRecive = 0;
		return 1;
	} else
		return 0;
}

/*** DEBUG & PRINT ***/
void printSpiPack(SPIPACK *p) {
	switch (p->in.type) {
	case setPWM:
		/*Recive*/
		Serial.println("Master Ask 'setPWM', Parameter:");
		Serial.print("\tspeed[1]:");
		Serial.println(p->in.pack.speed.vel[cMot1]);
		Serial.print("\tspeed[2]:");
		Serial.println(p->in.pack.speed.vel[cMot2]);
		Serial.print("\tspeed[3]:");
		Serial.println(p->in.pack.speed.vel[cMot3]);
		Serial.print("\tspeed[4]:");
		Serial.println(p->in.pack.speed.vel[cMot4]);
		Serial.print("\tspeed[5]:");
		Serial.println(p->in.pack.speed.vel[cMot5]);
		Serial.print("\tspeed[6]:");
		Serial.println(p->in.pack.speed.vel[cMot6]);
		/*Send*/
		Serial.println("Sended Encoder Step:");
		Serial.print("\tencoder[1]:");
		Serial.println(p->out.pack.en.passi[cMot1]);
		Serial.print("\tencoder[2]:");
		Serial.println(p->out.pack.en.passi[cMot2]);
		Serial.print("\tencoder[3]:");
		Serial.println(p->out.pack.en.passi[cMot3]);
		Serial.print("\tencoder[4]:");
		Serial.println(p->out.pack.en.passi[cMot4]);
		Serial.print("\tencoder[5]:");
		Serial.println(p->out.pack.en.passi[cMot5]);
		Serial.print("\tencoder[6]:");
		Serial.println(p->out.pack.en.passi[cMot6]);
		break;
	case getCurrent:
		break;
	case getSetting:
		break;
	case setSetting:
		break;
	case goHome:
		break;
	}
}

