#include "Arduino.h"
#include "Project-lib/globalDef.h"
//#define SERIAL_PRINT    //attiva/disattiva compilazione del codice per printare in seriale

#define sanityDelay 250    //tempo ms di attesa prima di ri-scansionare se il robot è ok
settingsBoard globSets;
SpiDevice *spi;
AdcDevice *adc;
ScorFeed *sFeed;
using namespace Motor;
DCdriverLimit *mot[nMot];

//The setup function is called once at startup of the sketch
void setup() {
    // Add your initialization code here
    Serial.begin(57600);
    Serial.println("Start Setup");
    Serial.println("\tMemory Load of Settings");
    memoryLoad();
    Serial.println("\tSetUp SPI");
    spi = new SpiDevice();
    Serial.println("\tSetUp ADC");
    adc = new AdcDevice(globSets.diff, globSets.adcVref);
    Serial.println("\tSetUp Scorbot Sensors");
    sFeed = new ScorFeed();
    Serial.println("\tMotor Enable");
    motSetup();
    Serial.println("\tGlobal Interrupt Enable");
    sei();
    Serial.println("End Setup");

    //home();
}

#ifdef SERIAL_PRINT
unsigned long timePrint = 0;
#endif
Pack *r;

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
    if (millis() > timePrint + 100) {
        adc->debugPrintAdc();
        sFeed->dSubDebug();
        sFeed->printSteps();
        timePrint = millis();
    }
#endif
}

unsigned long sanityTime = 0;

void sanityChek(int wait) {
    if (millis() > sanityTime + wait) {
        for (byte i = 0; i < nMot; i++) {
            if (globSets.maxCurrMed[i] < adc->getCurrentSum((motCode) i)) {
                mot[i]->freeRun();
#ifdef SERIAL_PRINT
                Serial.print("nMot[");
                Serial.print(i + 1);
                Serial.print("] overcurrent: ");
                Serial.print(globSets.maxCurrMed[i]);
                Serial.print(" > ");
                Serial.println(adc->getCurrentSum((motCode) i));
#endif
            }
        }
    }
}


//## SPI INTERRUPT SERVICE ##//
//Si attiva alla ricezione di ogni byte (8 bit)
//(e si ha tempo per eseguire la funzione solo fino al successivo!!)
ISR(SPI_STC_vect) {
        spi->isrFunxISP();
}

//## ADC INTERRUPT SERVICE ##//
//Si attiva ad ogni fine conversione, e immediatamente si avvia la successiva
//(con i valori presenti nel registro alla ricezione dell'interrupt)
//la routine salva il valore convertito e imposta i registri per la lettura successiva
ISR(ADC_vect) {
        adc->isrFunxAdc();
}

//## Timer/Counter5 Overflow Flag (TOV5)
//Ogni ~4Khz aggiorno la lettura degli encoder così da non
//perdermi mai un passo (freq massima misurata 2khz)
ISR(TIMER5_OVF_vect){
	sFeed->isrFunxEN();
}

//## PCINT INTERRUPT SERVICE ##//
//Al Cambio di uno dei pin degli Encoder, li salva tutti in memoria su un buffer circolare
//per elaborare lo stato in un momento successivo durante il programma
/*
ISR(PCINT0_vect) {
        sFeed->isrFunxEN();
}
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect)
);
*/
