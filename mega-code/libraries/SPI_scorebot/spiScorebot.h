#ifndef SPISCOREBOT_H
#define SPISCOREBOT_H
#include <stdlib.h>
#include "Arduino.h"

#include "SPI_Scorebot_PackDefine.h"

#define MISO 53
#define MOSI 52
#define SS 51
#define SCK 50

/*Prototype*/
void spiSetup();
volatile spiRecive* getLastRecive();
byte spiAvailable();
void isrFunxISP();
void preparaDati(char type);
int limitiDati(char type);

/* Volatile remade STDLIB*/
volatile void * volatile_memcpy(volatile void *d, volatile void *s, size_t n);
volatile void * volatile_memset(volatile void *s, int c, size_t n);

#endif
