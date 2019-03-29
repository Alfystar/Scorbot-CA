#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H
#include "Arduino.h"
#include <stdlib.h>
#include "SPI_Scorebot_PackDefine.h"
#include "../globalDef.h"
#include "../msEnlib/msEnlib.h"
#include "../adcReader/adcReader.h"

/*** HARDWARE ***/
void spiSetup();

/*** ELABORATION ***/
void isrFunxISP();
void preparaDati(SPIPACK *p);
//int limitiDati(char type);
int sizeTypePack(SPIPACK *s);

/*** GET VALUE ***/
byte spiAvailable();
volatile spiRecive* getLastRecive();

/*** PRINT & DEBUG ***/

#ifndef __IN_ECLIPSE__
#include "spiScorebot.cpp"
#endif

#endif
