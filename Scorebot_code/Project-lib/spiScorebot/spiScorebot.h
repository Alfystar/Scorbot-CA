#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H
#include "Arduino.h"
#include <stdlib.h>
#include "SPI_Scorebot_PackDefine.h"
#include "../globalDef.h"

/*** HARDWARE ***/
void spiSetup();

/*** ELABORATION ***/
void isrFunxISP();
void preparaDati(char type);
int limitiDati(char type);

/*** GET VALUE ***/
byte spiAvailable();
volatile spiRecive* getLastRecive();

/*** PRINT & DEBUG ***/

#ifndef __IN_ECLIPSE__
#include "spiScorebot.cpp"
#endif

#endif
