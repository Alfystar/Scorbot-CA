#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H
#include "Arduino.h"
#include <stdlib.h>
#include "SPI_Scorebot_PackDefine.h"

#define MISO 50
#define MOSI 51
#define SS 53
#define SCK 52


void spiSetup();
volatile spiRecive* getLastRecive();
byte spiAvailable();
void isrFunxISP();
void preparaDati(char type);
int limitiDati(char type) ;


/* Volatile remade STDLIB*/
volatile void * volatile_memcpy(volatile void *d, volatile void *s, size_t n);
volatile void * volatile_memset(volatile void *s, int c, size_t n);

#ifndef __IN_ECLIPSE__
#include "spiScorebot.cpp"
#endif

#endif
