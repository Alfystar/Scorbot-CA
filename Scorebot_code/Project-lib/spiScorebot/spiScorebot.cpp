#include "spiScorebot.h"
/* Local Var*/
SPIPACK spiPack[2];
volatile byte idTransf = 0; //Index of current Transfert
volatile byte startConv = 0; //Index of current Transfert
volatile byte dRecive = 0; //indica su quale buffer si sta scrivendo in questo momento
volatile byte newRecive = 0;

/*** HARDWARE ***/
void spiSetup() {
	pinMode(MISO, OUTPUT);
	memset((void *) spiPack, 0, sizeof(SPIPACK) * 2);
	idTransf = 0;
	startConv = 0;
	SPCR = (1 << SPIE) | (1 << SPE); 	//attiva spi e abilita interrupt
	SPDR = 5;	 						//predispomgo che al primo invio invio 0
}

/*** ELABORATION ***/
char *mem;
void isrFunxISP() {

	if (!startConv) {	//raps ha appena letto 0 e inviato typo
		spiPack[dRecive].inPack.in.type = SPDR; //mi segno tipo di comunicazione
		preparaDati(&spiPack[dRecive]);
		SPDR = spiPack[dRecive].outPack.buffOut[0]; //preparo invio primo dato
		startConv = 1;
		/*
		 Serial.print((byte) *((char *) &spiPack[dRecive].out + idTransf));
		 Serial.print(":start  ");
		 */

	} else {	//salva nuovo dato
		spiPack[dRecive].inPack.buffIn[idTransf] = SPDR; //salvo l'ultimo invio
		idTransf++;
		SPDR = spiPack[dRecive].outPack.buffOut[idTransf]; //preparo invio il mio dato

		/*
		 Serial.print((byte) *((char *) &spiPack[dRecive].out + idTransf));
		 Serial.print(":");
		 Serial.print(idTransf);
		 Serial.print("  ");
		 */
	}
	if (idTransf >= sizeTypePack(&spiPack[dRecive])) { //comunicazione all'ultimo byte
		spiPack[dRecive].inPack.buffIn[idTransf] = SPDR; //salvo l'ultimo invio
		SPDR = 0;		//ripredispongo lo 0 iniziale
		startConv = 0;
		idTransf = 0;
		dRecive = !dRecive;
		newRecive = 1;
		//Serial.println();
	}
}

void preparaDati(SPIPACK *p) {
	memset(&p->outPack.buffOut, 0, sizeof(spiSend));
	switch (p->inPack.in.type) {
	case setPWM:
		//memcpy(p->outPack.out.pack.en.passi, captureEn(), sizeof(setPWMSend));
		p->outPack.buffOut[0]=25;
		p->outPack.out.pack.en.passi[cMot1] = 1;
		p->outPack.out.pack.en.passi[cMot2] = 2;
		p->outPack.out.pack.en.passi[cMot3] = 3;
		p->outPack.out.pack.en.passi[cMot4] = 4;
		p->outPack.out.pack.en.passi[cMot5] = 5;
		p->outPack.out.pack.en.passi[cMot6] = 6;

		break;
	case getCurrent:
		memcpy(p->outPack.out.pack.curr.current, getAmpMots(),
				sizeof(getCurrentSend));
		break;
	case getSetting:
		memcpy(&p->outPack.out.pack.prop.sets, &sets, sizeof(getSettingSend));
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
	switch (s->inPack.in.type) {
	case setPWM:
		return max(sizeof(setPWMRecive) , sizeof(setPWMSend));
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
	switch (p->inPack.in.type) {
	case setPWM:
		/*Recive*/
		Serial.println("Master Ask 'setPWM', Parameter:");
		Serial.print("\tspeed[1]:");
		Serial.println(p->inPack.in.pack.speed.vel[cMot1]);
		Serial.print("\tspeed[2]:");
		Serial.println(p->inPack.in.pack.speed.vel[cMot2]);
		Serial.print("\tspeed[3]:");
		Serial.println(p->inPack.in.pack.speed.vel[cMot3]);
		Serial.print("\tspeed[4]:");
		Serial.println(p->inPack.in.pack.speed.vel[cMot4]);
		Serial.print("\tspeed[5]:");
		Serial.println(p->inPack.in.pack.speed.vel[cMot5]);
		Serial.print("\tspeed[6]:");
		Serial.println(p->inPack.in.pack.speed.vel[cMot6]);
		/*Send*/
		Serial.println("Sended Encoder Step:");
		Serial.print("\tencoder[1]:");
		Serial.println(p->outPack.out.pack.en.passi[cMot1]);
		Serial.print("\tencoder[2]:");
		Serial.println(p->outPack.out.pack.en.passi[cMot2]);
		Serial.print("\tencoder[3]:");
		Serial.println(p->outPack.out.pack.en.passi[cMot3]);
		Serial.print("\tencoder[4]:");
		Serial.println(p->outPack.out.pack.en.passi[cMot4]);
		Serial.print("\tencoder[5]:");
		Serial.println(p->outPack.out.pack.en.passi[cMot5]);
		Serial.print("\tencoder[6]:");
		Serial.println(p->outPack.out.pack.en.passi[cMot6]);
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

