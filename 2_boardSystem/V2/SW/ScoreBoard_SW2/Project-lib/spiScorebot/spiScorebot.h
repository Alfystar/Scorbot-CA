#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H
#include "Arduino.h"
#include <stdlib.h>
#include "../globalDef.h"
#include "../msEnlib/msEnlib.h"
#include "../adcReader/adcReader.h"
#include "SpiPack.h"


namespace SpiLib_Ard
{
using namespace spiPack;
class SpiDevice{
public:
	static SpiDevice& getIstance();

	/*** ELABORATION ***/
	void isrFunxISP();
	void dataLoad();

	/*** GET VALUE ***/
	byte spiAvailable();
	Pack& getLastRecive();

private:
	Pack sP[2];
	byte idTransf;
	byte startConv;
	byte dRecice;
	byte newRecive;
	static SpiDevice& instance;

	SpiDevice();
};

}

/*** HARDWARE ***/
void spiSetup();

/*** ELABORATION ***/
void isrFunxISP();
void preparaDati(Pack& p);
int sizeTypePack(Pack& p);

/*** GET VALUE ***/
Pack* getLastRecive();
byte spiAvailable();

/*** DEBUG & PRINT ***/
void printSpiPack(Pack& p);

#ifndef __IN_ECLIPSE__
#include "spiScorebot.cpp"
#endif

#endif
