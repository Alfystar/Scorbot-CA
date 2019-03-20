#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

enum currentPin {cMot1=0, cMot2, cMot3, cMot4, cMot5, cMot6};


void setup() {

  Serial.begin(57600);

  setUpADC();
  sei();
}

void loop() {
  Serial.print("Mot 1 diff=");
  Serial.println(getAmpMot(cMot1));
  delay(500);
}

