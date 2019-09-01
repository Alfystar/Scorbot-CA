/*
 * adcReader.cpp
 *				 Formule di Conversione:
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
 
#include "adcReader.h"
#define history 8 //data la frequenza ~1ms

/* LOCAL VAR */
int ampMot[nMot][history];
volatile byte indexADC = 0; //attuale ultima misura
//start value
volatile byte newReadId = cMot1;
volatile byte oldReadId = cMot1;

/*** HARDWARE ***/
void setUpADC() {
	memset((void *) ampMot, 0, sizeof(int) * nMot * history); //pulisco la memoria
	//ADMUX – ADC Multiplexer Selection Register
	ADMUX = (0 << REFS0) | (1 << REFS1); // 1.1V Interni Arduino

	DIDR0 = 0x7F; //imposto tutti i pin da A0:A6 come pin di input analiogico

	/* ADCSRB – ADC Control and Status Register B */
	ADCSRB &= 0xF8;	// Imposto la modalità di free running, e lascio inalterato il resto
	difPinSelect(cMot1); //imposto il primo pin da leggere per la lettura sporca

	/* ADCSRA – ADC Control and Status Register A */
	//A queste condizioni ho 125Khz di clock all'adc e una conversione ogni 14*1/125KHz= 112us ~ 8,9Khz  (14 perchè letto in differential mode)
	ADCSRA |= (1 << ADEN) | (1 << ADATE); //Attiva ADC, Seleziona l'autoTrigger scelto in ADCSRB
	ADCSRA | 0x7; //prescaler a 1/128 Clock
	ADCSRA |= (1 << ADSC);	//avvia 1° conversione
	/** Prima lettura è sporca **/
	while (ADCSRA & (1 << ADIF))
		; //wait first reading
	ADCSRA |= (1 << ADIE); //attiva l'interrupt
}

//todo: funzione di selezione del vref Aref/1.1V/2.56V


/*** ELABORATION ***/
void isrFunxAdc() {
	// Must read low first
	int g = ((int) ADCL | ((int) ADCH << 8));
	//if (g > 980)
	//	g = 0;
	ampMot[oldReadId][indexADC] = g;
	oldReadId = newReadId;
	if (oldReadId == 0)
		indexADC = (indexADC + 1) % history;
	newReadId = (newReadId + 1) % nMot;
	difPinSelect(newReadId);
}
/* Tabella Codice/significato dei mux
 MUX5:0  +    -   G
 010000 ADC0 ADC1 1×   Corrente mot 1
 010001 ADC1 ADC1 1×   XXXXXX----NON IN USO
 010010 ADC2 ADC1 1×   Corrente mot 2
 010011 ADC3 ADC1 1×   Corrente mot 3
 010100 ADC4 ADC1 1×   Corrente mot 4
 010101 ADC5 ADC1 1×   Corrente mot 5
 010110 ADC6 ADC1 1×   Corrente mot 6
 010111 ADC7 ADC1 1×
 */
 //todo input differenziale o diretto
int difPinSelect(int p) {
	byte val = ADMUX & 0xE0; //Cancello il precedente vale selezionato, mantenendo le impostazioni
	switch (p) {
	case cMot1:
		val |= 0x10;
		break;
	case cMot2:
		val |= 0x12;
		break;
	case cMot3:
		val |= 0x13;
		break;
	case cMot4:
		val |= 0x14;
		break;
	case cMot5:
		val |= 0x15;
		break;
	case cMot6:
		val |= 0x16;
		break;
	default:
		return -1;
		break;
	}
	ADMUX = val;
	return 0;
}

/*** GET VALUE ***/
int getAmpMot(byte m) {
	return ampMot[m][indexADC];
}

//puntatore di ritorno FERMO per circa 1ms
int *getAmpMots() {
	return &ampMot[0][((indexADC - 1) + history) % history];
}

int sumCurr;
int getSumMot(byte i) {
	sumCurr = 0;
	for (byte j = 0; j < history; j++)
		sumCurr += ampMot[i][j];
	return sumCurr;
}

/*** DEBUG & PRINT ***/
void debugPrintAdc() {
	Serial.print("Mot 1 diff=");
	Serial.print(getAmpMot(cMot1));
	Serial.print("  Mot 2 diff=");
	Serial.print(getAmpMot(cMot2));
	Serial.print("  Mot 3 diff=");
	Serial.print(getAmpMot(cMot3));
	Serial.print("  Mot 4 diff=");
	Serial.print(getAmpMot(cMot4));
	Serial.print("  Mot 5 diff=");
	Serial.print(getAmpMot(cMot5));
	Serial.print("  Mot 6 diff=");
	Serial.println(getAmpMot(cMot6));
}

