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
		spiPack[!dRecive].type = SPDR; //mi segno tipo di comunicazione
		preparaDati(&spiPack[!dRecive]);
		idTransf = 0;
		startConv = true;
		SPDR = spiPack[!dRecive].outPack.buffOut[idTransf]; //preparo invio primo dato

#ifdef ISPDEBUG
		Serial.print("type=");
		Serial.print((byte) spiPack[!dRecive].type);
		Serial.print("-");
		Serial.print("S");
		Serial.print(":");
		Serial.print((byte) spiPack[!dRecive].outPack.buffOut[idTransf]);
		Serial.print("_");
		Serial.print(idTransf);
		Serial.print("  ");
#endif
	} else {	//salva nuovo dato
		spiPack[!dRecive].inPack.buffIn[idTransf] = SPDR; //salvo l'ultimo invio
		idTransf++;
		SPDR = spiPack[!dRecive].outPack.buffOut[idTransf]; //preparo invio il mio dato
#ifdef ISPDEBUG
				Serial.print((byte) spiPack[!dRecive].inPack.buffIn[idTransf - 1]);
				Serial.print(":");
				Serial.print((byte) spiPack[!dRecive].outPack.buffOut[idTransf]);
				Serial.print("_");
				Serial.print(idTransf);
				Serial.print("  ");
#endif
	}

	if (sizeTypePack(&spiPack[!dRecive]) == -1) {
		SPDR = 0;		//ripredispongo lo 0 iniziale
		startConv = false;
#ifdef ISPDEBUG
		Serial.println(" -1 !! END  !");
#endif

		return;
	}
	if (idTransf >= sizeTypePack(&spiPack[!dRecive])) { //comunicazione all'ultimo byte
		SPDR = 0;		//ripredispongo lo 0 iniziale
		startConv = false;
		dRecive = !dRecive;
		newRecive = true;
#ifdef ISPDEBUG
		Serial.println(" END;");
#endif

	}

}

void preparaDati(SPIPACK *p) {
	memset(&p->outPack.buffOut, 0, sizeof(spiSend));
	switch (p->type) {
	case setPWM:
		memcpy(p->outPack.out.pack.en.passi, captureEn(), sizeof(setPWMSend));
		/*
		 p->outPack.out.pack.en.passi[cMot1] = 1;
		 p->outPack.out.pack.en.passi[cMot2] = 2;
		 p->outPack.out.pack.en.passi[cMot3] = 3;
		 p->outPack.out.pack.en.passi[cMot4] = 4;
		 p->outPack.out.pack.en.passi[cMot5] = 5;
		 p->outPack.out.pack.en.passi[cMot6] = 6;
		 */
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
	switch (s->type) {
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
	return -1;
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
	switch (p->type) {
	case setPWM:
		Serial.println("Master Ask 'setPWM', Parameter:");
		/*Recive*/
		for (byte i = 0; i < nMot; i++) {
			Serial.print("\tspeed[");
			Serial.print(i);
			Serial.print("]:");
			Serial.println(p->inPack.in.pack.speed.vel[cMot1 + i]);
		}
		/*Send*/
		Serial.println("Sended Encoder Step:");
		for (byte i = 0; i < nMot; i++) {
			Serial.print("\tencoder[");
			Serial.print(i);
			Serial.print("]:");
			Serial.println(p->outPack.out.pack.en.passi[cMot1 + i]);
		}
		break;
	case getCurrent:
		Serial.println("Master Ask 'getCurrent', Parameter:");
		/*Recive*/
		Serial.print("\tNotting");
		/*Send*/
		Serial.println("Sended Current Value:");
		for (byte i = 0; i < nMot; i++) {
			Serial.print("\tcurrent[");
			Serial.print(i);
			Serial.print("]:");
			Serial.println(p->outPack.out.pack.curr.current[cMot1 + i]);
		}
		break;
	case getSetting:
		Serial.println("Master Ask 'getSetting', Parameter:");
		/*Recive*/
		Serial.print("\tNotting");
		/*Send*/
		/*
		 int maxEn[nMot]; 		//valore massimo di passi prima di considerarsi fuori range di sicurezza (numeri pos)
		 int minEn[nMot]; 		//valore minimo di passi prima di considerarsi fuori range di sicurezza (numeri neg)
		 int maxCurrMed[nMot];	//valore massimo di corrente Efficace (con una media di 1 ms ~ ultime 8 letture), numero * 8 per semplificare i conti)
		 *
		 */
		Serial.println("Sended actual Settings:");

		Serial.print("#maxEn:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.println(p->outPack.out.pack.prop.sets.maxEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#minEn:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.println(p->outPack.out.pack.prop.sets.minEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#maxCurrMed:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.println(p->outPack.out.pack.prop.sets.maxCurrMed[cMot1 + i]);
		}
		Serial.println();
		break;
	case setSetting:
		Serial.println("Master Ask 'goHome', Parameter:");
		/*Recive*/
		Serial.print("#maxEn:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.println(p->inPack.in.pack.prop.sets.maxEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#minEn:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.println(p->inPack.in.pack.prop.sets.minEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#maxCurrMed:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.println(p->inPack.in.pack.prop.sets.maxCurrMed[cMot1 + i]);
		}
		Serial.println();
		/*Send*/
		Serial.print("\tNotting");
		break;
	case goHome:
		Serial.println("Master Ask 'goHome', Parameter:");
		/*Recive*/
		Serial.print("\tNotting");
		/*Send*/
		Serial.print("\tNotting");
		break;
	}
}

