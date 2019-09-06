/*
 * adcReader.h
 *
 * Questo script permette di avviare la lettura dei sensori di corrente dei motori.
 * La lettura prosegue in interrupt, e aggiorna in automatico l'array.
 * Sul pin A1 si immette la tensione da sottrarre, e leggendo i valori nell'array
 * si ottiene il risultato del comparatore con tutti i bit di precisioni scelti.
 * E necessario quindi tarare il voltaggio in ingresso sul pin A1, affinchè renda il
 * più vicini possibili tutti i sensori a 0 senza diventare negativi però, in tal caso
 * la sottrazione fa si che il risultato riparta da 1023 rendendo vana la lettura.
 *
 * Sensitività in uscita: 0.140 V/A, dichiarata dall'VNH5019
 * Vref scelto tra Aref/1.1V/2.56V
 * ______________________________________________________________________
 * |			 Vref * ADC	 	|  |			Iread * 1024 * Vcs		|
 * |	Iread = --------------	|&&|	ADC = -----------------------	|
 * |			1024 * Vcs   	|  |				Vref				|
 * |____________________________|__|____________________________________|
 *  Created on: 22 mar 2019
 *      Author: alfy
 */

#ifndef PROJECT_LIB_ADCREADER_ADCREADER_H_
#define PROJECT_LIB_ADCREADER_ADCREADER_H_

#include "Arduino.h"
#include "stdlib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../globalDef.h"

/*** HARDWARE ***/
void setUpADC();

/*** ELABORATION ***/
//Seleziona combinazione in ingresso per leggere motore e togliere Offset
void isrFunxAdc();
int difPinSelect(int p);

/*** GET VALUE ***/
short getAmpMot(byte m);
mCurrent *getAmpMots();		//puntatore di ritorno FERMO per circa 1ms
short getSumMot(byte i);

/*** DEBUG & PRINT ***/
void debugPrintAdc();
void debugPrintAdcOff();

#ifndef __IN_ECLIPSE__
#include "adcReader.cpp"
#endif

#endif /* PROJECT_LIB_ADCREADER_ADCREADER_H_ */
