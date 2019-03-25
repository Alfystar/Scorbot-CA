/*
 * msEnlib.h
 *
 *  Created on: 25 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_MSENLIB_H_
#define PROJECT_LIB_MSENLIB_H_
#include "Arduino.h"
#include <stdlib.h>
#include "../circular_buffer/circular_buffer.h"

#define sizeMem 32 	//numero di celle (di int [2 byte])nel buffer circolare

void dsubFeedSetup();
void enDebug();

byte msRead();
int enRead();
void isrFunxEN();

#ifndef __IN_ECLIPSE__
#include "msEnlib.c"
#endif

#endif /* PROJECT_LIB_MSENLIB_H_ */
