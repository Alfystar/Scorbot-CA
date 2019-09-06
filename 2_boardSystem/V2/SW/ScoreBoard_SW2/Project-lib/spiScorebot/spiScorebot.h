#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H
#include "Arduino.h"
#include <stdlib.h>
#include "../globalDef.h"
#include "../msEnlib/msEnlib.h"
#include "../adcReader/adcReader.h"
#include "SpiPack.h"

using namespace spiPack;

/*** HARDWARE ***/
void spiSetup();

/*** ELABORATION ***/
void isrFunxISP();
void preparaDati(Pack& p);
//int limitiDati(char type);
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
