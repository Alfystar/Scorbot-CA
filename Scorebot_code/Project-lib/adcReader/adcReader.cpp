/*
 * adcReader.cpp
 *
 *  Created on: 22 mar 2019
 *      Author: alfy
 */
#include "adcReader.h"
#define history 8 //data la frequenza ~1ms
/* LOCAL VAR */
int ampMot[nMot][history];
volatile byte indexADC = 0; //todo, variabile che viene messa a 1 quando si termina un ciclo di scansione
//start value
volatile byte newRead = cMot1;
volatile byte oldRead = cMot1;

/*** HARDWARE ***/
void setUpADC() {
	memset((void *) ampMot, 0, sizeof(int) * nMot); //pulisco la memoria
	//ADMUX – ADC Multiplexer Selection Register
	//todo: provare a simpostare valore di comparazione con i 2.56V interni
	ADMUX = (1 << REFS0); // impostato Aref esterno, per avere 5V scheda arduino (1 << REFS0); 	//Vref=5V of board, Lettura in uscita standard
	DIDR0 = 0x7F; //imposto tutti i pin da A0:A6 come pin di input analiogico

	/* ADCSRB – ADC Control and Status Register B */
	ADCSRB &= 0xF8;	// Imposto la modalità di free running, e lascio inalterato il resto
	difPinSelect(cMot1); //imposto il primo pin da leggere per la lettura sporca

	//todo: modificare che l'attivazione del free running avviene dopo aver calcolato gli offset
	/* ADCSRA – ADC Control and Status Register A
	 Accende l'ADC, Avvia la conversione, abilita l'impostazione del trigger scelto in ADCSRB(free running),
	 e in fine imposta il prescaler a 1/128
	 A queste condizioni ho 125Khz di clock all'adc e una conversione
	 ogni 14*1/125KHz= 112us ~ 8,9Khz  (14 perchè letto in differential mode) */
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | 0x7; //avvia la prima conversione
	//prima lettura è sporca
	while (ADCSRA & (1 << ADIF))
		; //wait first reading
	/* Calcolo dell'offset */
	/*
	 int sum = 0;
	 delay(1);
	 for (char i = 0; i < 6; i++) {
	 difPinSelect(cMot1 + i);
	 sum = 0;
	 Serial.println("i new");
	 for (char j = 0; j < 10; j++) {
	 ADCSRA |= (1 << ADSC);
	 ADCSRA = ADCSRA;
	 while (ADCSRA & (1 << ADIF));
	 sum += (int)ADCL | ((int)ADCH << 8);
	 Serial.println(sum);
	 }
	 ampMotOff[i] = sum / 10;
	 }
	 debugPrintAdcOff();
	 */

	ADCSRA |= (1 << ADIE); //attiva l'interrupt

}

/*** ELABORATION ***/
void isrFunxAdc() {
	// Must read low first
	ampMot[oldRead][indexADC] = ((int) ADCL | ((int) ADCH << 8));
	oldRead = newRead;
	newRead = (newRead + 1) % nMot;
	if (oldRead == 0)
		indexADC = (indexADC + 1) % history;
	difPinSelect(newRead);
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
		val |= 0x12;
		break;
	case cMot4:
		val |= 0x14;
		break;
	case cMot5:
		val |= 0x15;
		break;
	case cMot6:
		val |= 0x17;
		break;
	default:
		return -1;
		break;
	}
	ADMUX = val; //imposto il nuovo canale
	return 0;
}

/*** GET VALUE ***/
int getAmpMot(byte m) {
	int g = ampMot[m][((indexADC - 1) + history) % history];
	return g;
}

//puntatore di ritorno FERMO per circa 1ms
int *getAmpMots() {
	return &ampMot[0][((indexADC - 1) + history) % history];
}

int sumCurr = 0;
int getSumMot(byte i) {
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

/*
 void debugPrintAdcOff() {
 Serial.print("Mot 1 off=");
 Serial.print(ampMotOff[cMot1]);
 Serial.print("  Mot 2 off=");
 Serial.print(ampMotOff[cMot2]);
 Serial.print("  Mot 3 off=");
 Serial.print(ampMotOff[cMot3]);
 Serial.print("  Mot 4 off=");
 Serial.print(ampMotOff[cMot4]);
 Serial.print("  Mot 5 off=");
 Serial.print(ampMotOff[cMot5]);
 Serial.print("  Mot 6 off=");
 Serial.println(ampMotOff[cMot6]);
 }
 */
