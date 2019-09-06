#include "spiScorebot.h"

namespace SpiLib_Ard
{
//Static variable initialize
Spidevice* SpiDevice::instance=nullptr;
SpiDevice& SpiDevice::getIstance(){
	if(SpiDevice::instance==nullptr)
		SpiDevice::instance = new SpiDevice();
	return SpiDevice::instance;
}

SpiDevice::SpiDevice(){
	pinMode(MISO, OUTPUT);
	this->sP[0].clearPack();
	this->sP[1].clearPack();
	this->idTransf = 0;
	this->startConv = 0;
	SPCR = (1 << SPIE) | (1 << SPE); 	//attiva spi e abilita interrupt
	SPDR = 5;	 						//predispomgo che al primo invio invio 0
}

/*** ELABORATION ***/
void SpiDevice::isrFunxISP(){
	if (!this->startConv) {	//raps ha appena letto 0 e inviato tipo
		this->sP[!this->dRecice].setPackType((packType)SPDR); //mi segno tipo di comunicazione
		preparaDati(this->sP[!this->dRecive]);
		this->idTransf = 0;
		this->startConv = true;
		SPDR = this->sP[!this->dRecive].getSPIPACK().forRasp.buf[this->idTransf];//preparo invio primo dato

#ifdef ISPDEBUG
		Serial.print("type=");
		Serial.print((byte) spiPackp[!this->dRecive].type);
		Serial.print("-");
		Serial.print("S");
		Serial.print(":");
		Serial.print((byte) spiPackp[!this->dRecive].outPack.buffOut[this->idTransf]);
		Serial.print("_");
		Serial.print(this->idTransf);
		Serial.print("  ");
#endif
	} else {	//salva nuovo dato
		this->sP[!this->dRecive].getSPIPACK().forArd.buf[this->idTransf] = SPDR; //salvo l'ultimo invio
		idTransf++;
		SPDR = this->sP[!this->dRecive].getSPIPACK().forRasp.buf[this->idTransf]; //preparo invio il mio dato
#ifdef ISPDEBUG
		Serial.print((byte) spiPackp[!this->dRecive].inPack.buffIn[this->idTransf - 1]);
		Serial.print(":");
		Serial.print((byte) spiPackp[!this->dRecive].outPack.buffOut[this->idTransf]);
		Serial.print("_");
		Serial.print(this->idTransf);
		Serial.print("  ");
#endif
	}

	if (this->sP[!this->dRecive].sizePack() == -1) {
		SPDR = 0;		//ripredispongo lo 0 iniziale
		this->startConv = false;
#ifdef ISPDEBUG
		Serial.println(" -1 !! END  !");
#endif

		return;
	}
	if (this->idTransf >= this->sP[!this->dRecive].sizePack()) { //comunicazione all'ultimo byte
		SPDR = 0;		//ripredispongo lo 0 iniziale
		this->startConv = false;
		this->dRecive = !this->dRecive;
		this->newRecive = true;
#ifdef ISPDEBUG
		Serial.println(" END;");
#endif

	}
}

void SpiDevice::dataLoad(){

	memset(&this->sP[!this->dRecive].getSPIPACK().forRasp, 0, sizeof(spi2Rasp));
	Pack& p=this->sP[!this->dRecive];
	switch (p.getPackType()) {
	case invalid:
		break;
	case PWMsend_EnRet:
		psetEncoder(*captureEn());
		break;
	case PWMsend_CurRet:
		p.setCurrent(*getAmpMots());
		break;
	case PWMsend_AllRet:
		p.setEncoder(*captureEn());
		p.setCurrent(*getAmpMots());
		break;
	case SettingGet:
		p.setSetting(sets, pack4Rasp);
		break;
	case SettingSet:
		break;
	case goHome:
		break;
	default:
		break;
	}
}

/*** GET VALUE ***/
byte SpiDevice::spiAvailable(){
	if (this->newRecive != 0) {
		this->newRecive = 0;
		return 1;
	} else
		return 0;
}

Pack& SpiDevice::getLastRecive(){
	return &this->sP[this->dRecive];
}
}

/* Local VAR*/
SPIPACK spiPackp[2];
Pack sP[2];
volatile byte idTransf = 0; //Index of current Transfert
volatile byte startConv = 0; //Index of current Transfert
volatile byte dRecive = 0; //indica su quale buffer si sta scrivendo in questo momento
volatile byte newRecive = 0;

/*** HARDWARE ***/
void spiSetup() {
	pinMode(MISO, OUTPUT);
	sP[0].clearPack();
	sP[1].clearPack();
	memset((void *) spiPackp, 0, sizeof(SPIPACK) * 2);
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
		preparaDati(sP[!dRecive]);
		idTransf = 0;
		startConv = true;
		SPDR = sP[!dRecive].getSPIPACK().forRasp.buf[idTransf];//preparo invio primo dato

#ifdef ISPDEBUG
		Serial.print("type=");
		Serial.print((byte) spiPackp[!dRecive].type);
		Serial.print("-");
		Serial.print("S");
		Serial.print(":");
		Serial.print((byte) spiPackp[!dRecive].outPack.buffOut[idTransf]);
		Serial.print("_");
		Serial.print(idTransf);
		Serial.print("  ");
#endif
	} else {	//salva nuovo dato
		sP[!dRecive].getSPIPACK().forArd.buf[idTransf] = SPDR; //salvo l'ultimo invio
		idTransf++;
		SPDR = sP[!dRecive].getSPIPACK().forRasp.buf[idTransf]; //preparo invio il mio dato
#ifdef ISPDEBUG
		Serial.print((byte) spiPackp[!dRecive].inPack.buffIn[idTransf - 1]);
		Serial.print(":");
		Serial.print((byte) spiPackp[!dRecive].outPack.buffOut[idTransf]);
		Serial.print("_");
		Serial.print(idTransf);
		Serial.print("  ");
#endif
	}

	if (sP[!dRecive].sizePack() == -1) {
		SPDR = 0;		//ripredispongo lo 0 iniziale
		startConv = false;
#ifdef ISPDEBUG
		Serial.println(" -1 !! END  !");
#endif

		return;
	}
	if (idTransf >= sP[!dRecive].sizePack()) { //comunicazione all'ultimo byte
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
	case invalid:
		break;
	case PWMsend_EnRet:
		p.setEncoder(*captureEn());
		break;
	case PWMsend_CurRet:
		p.setCurrent(*getAmpMots());
		break;
	case PWMsend_AllRet:
		p.setEncoder(*captureEn());
		p.setCurrent(*getAmpMots());
		break;
	case SettingGet:
		p.setSetting(sets, pack4Rasp);
		break;
	case SettingSet:
		break;
	case goHome:
		break;
	default:
		break;
	}
}

/*Simile all'equivalente su rapsberry*/
int sizeTypePack(Pack *p) {
	return p->sizePack();
	return -1;
}

/*** GET VALUE ***/
Pack * getLastRecive() {
	return &sP[dRecive];
}

byte spiAvailable() {
	if (newRecive != 0) {
		newRecive = 0;
		return 1;
	} else
		return 0;
}

/*** DEBUG & PRINT ***/
void printSpiPack(Pack& p) {
	p.printPack();
}

