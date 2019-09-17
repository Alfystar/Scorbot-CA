#include "Arduino.h"
#include "Project-lib/globalDef.h"

//#define SERIAL_PRINT 1    //attiva/disattiva compilazione del codice per printare in seriale
#define SPI_PRINT 1			//attiva/disattiva compilazione del print del pacchetto spi

#define sanityDelay 250    	//tempo ms di attesa prima di ri-scansionare se il robot è ok
#define newPrintDelay 1000	//delay tra un debug print e l'altro

settingsBoard globSets;
SpiDevice *spi;
AdcDevice *adc;
ScorFeed *sFeed;
using namespace Motor;
DCdriverLimit *mot[nMot];

#ifdef SERIAL_PRINT
unsigned long timePrint;	//time to next debug print
#endif
//The setup function is called once at startup of the sketch
void setup() {
    // Add your initialization code here
    Serial.begin(57600);
    Serial.println("\n##### Start Setup #####");
    delay(250);

    memoryLoad();
    Serial.println("\tLoad Settings from Memory");

    motSetup();
    Serial.println("\tMotor Setup");

    sFeed = new ScorFeed();
    Serial.println("\tSetUp Scorbot Sensors");

    adc = new AdcDevice(globSets.diff, globSets.adcVref);
    Serial.println("\tSetUp ADC");

    spi = new SpiDevice();
    Serial.println("\tSetUp SPI");

    sei();
    Serial.println("\tGlobal Interrupt Enable");

    Serial.println("End Setup");

#ifdef SERIAL_PRINT
    delay(500);
	Pack::printSetting(globSets);
	Serial.println("End Setup");
	timePrint=millis();
	delay(1000);
#endif
    //home();
}

Pack *r;

void loop() {
	//Serial.println("LOOP");
    sanityChek(sanityDelay);
    if (spi->spiAvailable()) {
        r = &spi->getLastRecive();
        excutePack(*r);
#ifdef SPI_PRINT
        r->printPack();
#endif
    }
    sFeed->updateStepEn();
    motorStateMachine();
#ifdef SERIAL_PRINT

    if (millis() > timePrint + newPrintDelay) {
        adc->debugPrintAdc();
        sFeed->dSubDebug();
        sFeed->printSteps();
    	Pack::printSetting(globSets);
        Serial.println();
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
            if (((globSets.maxCurrMed[i]*3)/2) < adc->getCurrentSum((motCode) i)) {	// WARNING
            	digitalWrite(MotEn,0);
#ifdef SERIAL_PRINT
                Serial.print("nMot[");
                Serial.print(i + 1);
                Serial.print("] High-overcurrent: ");
                Serial.print(globSets.maxCurrMed[i]);
                Serial.print(" > ");
                Serial.println(adc->getCurrentSum((motCode) i));
#endif
            }
            if ((globSets.maxCurrMed[i]/4) < adc->getCurrentSum((motCode) i)) {	// Current problem came back
            	digitalWrite(MotEn,1);
            }

        }
    }
}


//## SPI INTERRUPT SERVICE ##//
//Si attiva alla ricezione di ogni byte (8 bit)
//(e si ha tempo per eseguire la funzione solo fino al successivo!!)
ISR(SPI_STC_vect) {
        spi->isrFunxISP();
//    	Serial.print("spi");
}

//## ADC INTERRUPT SERVICE ##//
//Si attiva ad ogni fine conversione, e immediatamente si avvia la successiva
//(con i valori presenti nel registro alla ricezione dell'interrupt)
//la routine salva il valore convertito e imposta i registri per la lettura successiva
ISR(ADC_vect) {
		//Serial.print("adc");
        adc->isrFunxAdc();
}

//## Timer/Counter5 Overflow Flag (TOV5)
//Ogni ~4Khz aggiorno la lettura degli encoder così da non
//perdermi mai un passo (freq massima misurata 2khz)

ISR(TIMER5_OVF_vect){
	sFeed->isrFunxEN();
    //Serial.println(sFeed->enRead(), BIN);

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
