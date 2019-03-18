#include "Arduino.h"

#include "Project-lib/spiScorebot/spiScorebot.h"
//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	spiSetup();
}

// The loop function is called in an endless loop
void loop() {

//Add your repeated code here
	if (spiAvailable()) {
		spiRecive* r;
		r = getLastRecive();
		Serial.println(r->pack.pwm.text);
	}
	delay(100);
}

ISR(SPI_STC_vect) {
	isrFunxISP();
}
