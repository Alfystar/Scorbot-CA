int c=0;
#include "spiScorebot/spiScorebot.h"

void setup (void)
{
  Serial.begin(57600);
  spiSetup();
}
 spiRecive *r;

void loop (void)
{
  if(spiAvailable())
  {
      r=getLastRecive();
    Serial.println(r->pack.pwm.text);
  }
  delay(100);
}

ISR(SPI_STC_vect)
{
  isrFunxISP();
}

