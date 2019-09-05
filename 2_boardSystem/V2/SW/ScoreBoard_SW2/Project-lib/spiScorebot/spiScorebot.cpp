#include "spiScorebot.h"
/* Local Var*/
SPIPACK spiPack[2];
Pack sP[2];
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
/*
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
*/

void isrFunxISP() {

	if (!startConv) {	//raps ha appena letto 0 e inviato tipo
		sP[!dRecive].setPackType((packType)SPDR); //mi segno tipo di comunicazione
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

void preparaDati(Pack& p) {
	memset(&p.getSPIPACK().forRasp, 0, sizeof(spi2Rasp));
	switch (p.getPackType()) {
	case PWMsend_EnRet:
		p.set
		memcpy(p.Encoder(), captureEn(), sizeof(mEncoder));
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
			Serial.print("\tspeed[cMot");
			Serial.print(i+1);
			Serial.print("]:");
			Serial.println(p->inPack.in.pack.speed.vel[cMot1 + i]);
		}
		/*Send*/
		Serial.println("Sended Encoder Step:");
		for (byte i = 0; i < nMot; i++) {
			Serial.print("\tencoder[cMot");
			Serial.print(i+1);
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
			Serial.print("\tcurrent[cMot");
			Serial.print(i + 1);
			Serial.print("]:");
			Serial.println(p->outPack.out.pack.curr.current[cMot1 + i]);
		}
		break;
	case getSetting:
		Serial.println("Master Ask 'getSetting', Parameter:");
		/*Recive*/
		Serial.print("\tNotting");
		/*Send*/

		Serial.println("Sended actual Settings:");

		Serial.print("#maxEn:\t\t");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.print(p->outPack.out.pack.prop.sets.maxEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#minEn:\t\t");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.print(p->outPack.out.pack.prop.sets.minEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#maxCurrMed:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.print(p->outPack.out.pack.prop.sets.maxCurrMed[cMot1 + i]);
		}
		Serial.println();
		break;
	case setSetting:
		Serial.println("Master Ask 'setSetting', Parameter:");
		/*Recive*/
		Serial.print("#maxEn:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.print(p->inPack.in.pack.prop.sets.maxEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#minEn:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.print(p->inPack.in.pack.prop.sets.minEn[cMot1 + i]);
		}
		Serial.println();

		Serial.print("#maxCurrMed:");
		for (byte i = 0; i < nMot; i++) {

			Serial.print("\t");
			Serial.print(p->inPack.in.pack.prop.sets.maxCurrMed[cMot1 + i]);
		}
		Serial.println();
		/*Send*/
		Serial.print("\tNotting\n");
		break;
	case goHome:
		Serial.println("Master Ask 'goHome', Parameter:\n");
		/*Recive*/
		Serial.print("\tNotting\n");
		/*Send*/
		Serial.print("\tNotting\n");
		break;
	}
}

