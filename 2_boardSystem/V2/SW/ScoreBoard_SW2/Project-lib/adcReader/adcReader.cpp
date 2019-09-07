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

namespace InternalDevice {

AdcDevice::AdcDevice() {
	AdcDevice(false, in1V1);
}

AdcDevice::AdcDevice(adcRef vRef) {
	AdcDevice(false, vRef);
}

AdcDevice::AdcDevice(bool diff) {
	AdcDevice(diff, in1V1);
}

AdcDevice::AdcDevice(bool diff, adcRef vRef) {
	this->setDiffRead(diff);
	this->setVRefSource(vRef);
	this->historyClear();
	this->setUpADC();
}

void AdcDevice::setUpADC() {
	DIDR0 = 0x7F; //imposto tutti i pin da A0:A6 come pin di input analiogico

	// ADCSRB – ADC Control and Status Register B //
	ADCSRB &= 0xF8;	// Imposto la modalità di free running, e lascio inalterato il resto

	// ADCSRA – ADC Control and Status Register A //
	//A queste condizioni ho 125Khz di clock all'adc e una conversione ogni 14*1/125KHz= 112us ~ 8,9Khz  (14 perchè letto in differential mode)
	ADCSRA |= (1 << ADEN) | (1 << ADATE); //Attiva ADC, Seleziona l'autoTrigger scelto in ADCSRB
	ADCSRA | 0x7; //prescaler a 1/128 Clock

	this->pinSelect(Mot1); //imposto il primo pin da leggere per la lettura sporca
	ADCSRA |= (1 << ADSC);	//avvia 1° conversione
	// Prima lettura è sporca //
	while (ADCSRA & (1 << ADIF))
		; //wait first reading
	ADCSRA |= (1 << ADIE); //attiva l'interrupt
}

void AdcDevice::historyClear() {
	memset((void *) ampMot, 0, sizeof(mCurrent) * history); //pulisco la memoria
}

void AdcDevice::setVRefSource(adcRef vRef) {
	//ADMUX – ADC Multiplexer Selection Register
	this->vRef = vRef;
	switch (vRef) {
	case in1V1:
		ADMUX = (0 << REFS0) | (1 << REFS1); // 1.1V Interni Arduino
		break;
	case in2V56:
		//todo
		break;
	case ext:
		//todo
		break;
	}
}

adcRef AdcDevice::getVRefSource() {
	return this->vRef;
}

void AdcDevice::setDiffRead(bool active) {
	this->diffRead = (!!active); //to be sure value is 0 or 1
}

bool AdcDevice::getDiffRead() {
	return this->diffRead;
}

void AdcDevice::isrFunxAdc() {
	// Must read low first
	int g = ((int) ADCL | ((int) ADCH << 8));
	//todo: verificare il corretto accesso in memoria di questo doppio array
	this->ampMot[indexADC][oldReadId] = g;
	oldReadId = newReadId;
	if (oldReadId == 0)
		indexADC = (indexADC + 1) % history;
	newReadId = (motCode)((newReadId + 1) % nMot);
	this->pinSelect(newReadId);
}
/* Tabella Codice/significato dei mux
 MUX5:0  +    -   G
 000000 ADC0 ADC1 1×   Corrente mot 1
 000001 ADC1 ADC1 1×   XXXXXX----NON IN USO
 000010 ADC2 ADC1 1×   Corrente mot 2
 000011 ADC3 ADC1 1×   Corrente mot 3
 000100 ADC4 ADC1 1×   Corrente mot 4
 000101 ADC5 ADC1 1×   Corrente mot 5
 000110 ADC6 ADC1 1×   Corrente mot 6
 000111 ADC7 ADC1 1×
 //###### 4° bit ON ######//
 010000 ADC0 ADC1 1×   Corrente mot 1 - Offset
 010001 ADC1 ADC1 1×   XXXXXX----NON IN USO
 010010 ADC2 ADC1 1×   Corrente mot 2 - Offset
 010011 ADC3 ADC1 1×   Corrente mot 3 - Offset
 010100 ADC4 ADC1 1×   Corrente mot 4 - Offset
 010101 ADC5 ADC1 1×   Corrente mot 5 - Offset
 010110 ADC6 ADC1 1×   Corrente mot 6 - Offset
 010111 ADC7 ADC1 1×
 */
byte AdcDevice::pinSelect(motCode mot) {
	byte val = ADMUX & 0xE0; //mantenengo le impostazioni
	switch (mot) {
	case Mot1:
		val |= 0x0;
		break;
	case Mot2:
		val |= 0x2;
		break;
	case Mot3:
		val |= 0x3;
		break;
	case Mot4:
		val |= 0x4;
		break;
	case Mot5:
		val |= 0x5;
		break;
	case Mot6:
		val |= 0x6;
		break;
	default:
		return -1;
		break;
	}
	//Il 4°bit attiva la lettura Diffenrenziale
	val |= (this->diffRead) << 4;
	ADMUX = val;
	return 0;
}
//puntatore di ritorno FERMO per circa 1ms
mCurrent& AdcDevice::getLastCicle() {
	return this->ampMot[((indexADC - 1) + history) % history];
}

short AdcDevice::getCurrentSum(motCode mot) {
	this->sumCur = 0;
	//todo check access on array
	for (byte j = 0; j < history; j++)
		this->sumCur += this->ampMot[j][mot];
	return this->sumCur;
}

void AdcDevice::debugPrintAdc() {
	mCurrent& m = this->getLastCicle();
	Serial.print("Mot 1=");
	Serial.print(m[Mot1]);
	Serial.print("  Mot 2=");
	Serial.print(m[Mot2]);
	Serial.print("  Mot 3=");
	Serial.print(m[Mot3]);
	Serial.print("  Mot 4=");
	Serial.print(m[Mot4]);
	Serial.print("  Mot 5=");
	Serial.print(m[Mot5]);
	Serial.print("  Mot 6=");
	Serial.println(m[Mot6]);
	if(this->diffRead)
		Serial.println("Lettura differenziale ON");
	else
		Serial.println("Lettura differenziale OFF");

}

} //END namespace InternalDevice

