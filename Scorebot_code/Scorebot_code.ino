#include "Arduino.h"
#include "Project-lib/pinDef.h"
#include "Project-lib/spiScorebot/spiScorebot.h"
#include "Project-lib/adcReader/adcReader.h"
//The setup function is called once at startup of the sketch
void setup() {
	// Add your initialization code here
	Serial.begin(57600);
	sei();
	Serial.println("Start Setup");
	Serial.println("\tSetUp SPI");
	spiSetup();
	Serial.println("\tSetUp ADC");
	setUpADC();
	Serial.println("\Relè Mot Enable");
	pinMode(motEn, OUTPUT);
	digitalWrite(motEn, 1);
	Serial.println("End Setup");
}

// The loop function is called in an endless loop
void loop() {

//Add your repeated code here
	if (spiAvailable()) {
		spiRecive* r;
		r = getLastRecive();
		Serial.println(r->pack.pwm.text);
	}

	debugPrintAdc();
	delay(1000);
}

ISR(SPI_STC_vect) {
	isrFunxISP();
}

ISR(ADC_vect) {
	isrFunxAdc();
}
