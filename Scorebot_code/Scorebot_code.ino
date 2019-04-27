#include "Arduino.h"
#include "Project-lib/globalDef.h"
#include "Project-lib/spiScorebot/spiScorebot.h"
#include "Project-lib/adcReader/adcReader.h"
#include "Project-lib/msEnlib/msEnlib.h"

#define SERIAL_PRINT	//attiva/disattiva compilazione del codice per printare in seriale
#define sanityDelay 250	//tempo ms di attesa prima di ri-scansionare se il robot è ok

settingsBoard sets;

L298N *mot[nMot];

//The setup function is called once at startup of the sketch
void setup() {
	// Add your initialization code here
	Serial.begin(57600);
	Serial.println("Start Setup");
	Serial.println("\tSetUp SPI");
	spiSetup();
	Serial.println("\tSetUp ADC");
	setUpADC();
	Serial.println("\tSetUp Scorbot Sensors");
	dsubFeedSetup();
	Serial.println("\tMotor Enable");
	motSetup();
	/* PER ORA UN CORTO CIRCUITO
	 Serial.println("\Relè Mot Enable");
	 pinMode(motEn, OUTPUT);
	 digitalWrite(motEn, 1);
	 */
	Serial.println("\tMemory Load of Settings");
	memoryLoad();
	Serial.println("\tGlobal Interrupt Enable");
	sei();
	Serial.println("End Setup");

	//home();
}

unsigned long timePrint = 0;
SPIPACK * r;

void loop() {
	sanityChek(sanityDelay);
	if (spiAvailable()) {
		r = getLastRecive();
		excutePack(r);

#ifdef SERIAL_PRINT
		printSpiPack(r);
#endif
	}

	updateStepEn();
	motorStateMachine();

#ifdef SERIAL_PRINT
	/*Funzione di Print Seriale NON BLOCCANTE*/
	if (millis() > timePrint + 100) {

		//Serial.println(getAmpMot(cMot1));

		//debugPrintAdc();
		//enDebug();
		//printSteps();
		timePrint = millis();
	}
#endif
}

unsigned long sanityTime = 0;
void sanityChek(int wait) {
	if (millis() > sanityTime + wait) {
		// Scopo della parte è limitare il verso degli encoder per evitare di sbattere, ma serve sapere
		// Con quale segno di speed crescono gli encoder, bisogna modificare la classe L298N, e far bloccare lì
		// i pwm che non vanno. Da fare in seguito
		/*
		for (byte i = 0; i < nMot; i++) {
			if (getEn(i) >= sets.maxEn[i] || getEn(i) <= sets.minEn[i])	//se vero, sono oltre limite (i negativi non posono esserci essendo lo 0 a msRead[al massimo -1/-2 ma è rumore])
					{
				Serial.print("Mot");
				Serial.print(i + 1);
				Serial.println(" Oltre Limite Encoder");
				mot[i]->reversDir();
			}
		}*/
		for (byte i = 0; i < nMot; i++) {
			if (sets.maxCurrMed[i] > getSumMot(i)) //se vero, sono oltre limite
					{
				mot[i]->freeRun();
			}
		}
		sanityTime = millis();
	}
}

/** SPI INTERRUPT SERVICE **/
//Si attiva alla fine dell'invio di 1 byte
ISR(SPI_STC_vect) {
	isrFunxISP();
}

/** ADC INTERRUPT SERVICE **/
//Si attiva ogni completamento di lettura, la salva e progamma la successiva
//procede automaticamente
ISR(ADC_vect) {
	isrFunxAdc();
}

/** PCINT INTERRUPT SERVICE **/
//Al Cambio di uno dei pin degli Encoder, li salva tutti in memoria su un buffer circolare
//per elaborare lo stato in un momento successivo durante il programma
ISR(PCINT0_vect) {
	isrFunxEN();
}
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect));
