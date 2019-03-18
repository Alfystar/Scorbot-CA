
#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H

#include "SPI_Scorebot_PackDefine.h"

unsigned char hello[] = "Hello guy\n";

volatile byte idTransf = 0; //Index of current Transfert
volatile spiRecive reciveSpi[2];
volatile byte dirtyRecive = 0; //indica su quale buffer si sta scrivendo in questo momento
volatile spiSend _sendSpi;
volatile byte newRecive=0;


void spiSetup();
spiRecive* getLastRecive();
byte spiAvailable();
void isrFunxISP();
void preparaDati(char type);
int limitiDati(char type) ;

#include "spiScorebot.c"

#endif
