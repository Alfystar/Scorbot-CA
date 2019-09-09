#include "Arduino.h"
#include "Project-lib/globalDef.h"

#define SERIAL_PRINT	//attiva/disattiva compilazione del codice per printare in seriale
#define sanityDelay 250	//tempo ms di attesa prima di ri-scansionare se il robot è ok

settingsBoard sets;
SpiDevice *spi;
AdcDevice *adc;

ScorFeed *sFeed;

using namespace Motor;
DCdriver *mot[nMot];

//The setup function is called once at startup of the sketch
void setup() {
	// Add your initialization code here
	Serial.begin(57600);
	Serial.println("Start Setup");
	Serial.println("\tSetUp SPI");
    spi = new SpiDevice();
	Serial.println("\tSetUp ADC");
	adc = new AdcDevice();
	Serial.println("\tSetUp Scorbot Sensors");
    sFeed = new ScorFeed();
	Serial.println("\tMotor Enable");
	motSetup();
	Serial.println("\tMemory Load of Settings");
	memoryLoad();
	Serial.println("\tGlobal Interrupt Enable");
	sei();
	Serial.println("End Setup");

    //home();
}
#ifdef SERIAL_PRINT
unsigned long timePrint = 0;
#endif
Pack * r;

void loop() {
	sanityChek(sanityDelay);
	if (spi->spiAvailable()) {
		r = &spi->getLastRecive();
		excutePack(*r);
#ifdef SERIAL_PRINT
		r->printPack();
#endif
	}
    sFeed->updateStepEn();
	motorStateMachine();
#ifdef SERIAL_PRINT
	/*Funzione di Print Seriale NON BLOCCANTE*/
	if (millis() > timePrint + 100) {

        //Serial.println(getAmpMot(Mot1));
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
            if (sets.maxCurrMed[i] < adc->getCurrentSum((motCode) i)) {
				mot[i]->freeRun();
				Serial.print("nMot[");
				Serial.print(i + 1);
				Serial.print("] overcurrent: ");
				Serial.print(sets.maxCurrMed[i]);
				Serial.print(" > ");
                Serial.println(adc->getCurrentSum((motCode) i));
			}
		}
		sanityTime = millis();
	}
}

//## SPI INTERRUPT SERVICE ##//
//Si attiva alla fine dell'invio di 1 byte
ISR(SPI_STC_vect) {
	spi->isrFunxISP();
}

//## ADC INTERRUPT SERVICE ##//
//Si attiva ogni completamento di lettura, la salva e progamma la successiva
//procede automaticamente
ISR(ADC_vect) {
	adc->isrFunxAdc();
}

//## PCINT INTERRUPT SERVICE ##//
//Al Cambio di uno dei pin degli Encoder, li salva tutti in memoria su un buffer circolare
//per elaborare lo stato in un momento successivo durante il programma
ISR(PCINT0_vect) {
        sFeed->isrFunxEN();
}
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect));
