/*
 * msEnlib.h
 *	Libreria di lettura e elaborazione dei passi encoder
 *	e dei micro switch dello scorebot
 *  Created on: 25 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_MSENLIB_H_
#define PROJECT_LIB_MSENLIB_H_
#include "Arduino.h"
#include <stdlib.h>
#include "../circular_buffer/circular_buffer.h"
#include "../globalDef.h"

#define sizeMem 128 	//numero di celle (di int [2 byte])nel buffer circolare

/*** HARDWARE ***/
// Imposta i pin di uscita e registri
void dsubFeedSetup();
//Ritorna una manschera di bit 1=Premuto (FINE CORSA)
byte msRead();
//Ritorna un Intero dove i byte sono :[0]ChA e [1]ChB
int enRead();

/*** ELABORATION ***/
void updateStepEn();
void calcStep(int oldEn, int newEn);
void isrFunxEN();

/*** SET VALUE ***/
void setEn(byte m, int p);

/*** GET VALUE ***/
int getEn(byte i);
//Fotografa un istante e rimane quello fino alla successiva chiamata della funzione
int *captureEn();

/*** DEBUG & PRINT ***/
void enDebug();
void printSteps();

#ifndef __IN_ECLIPSE__
#include "msEnlib.cpp"
#endif

#endif /* PROJECT_LIB_MSENLIB_H_ */
