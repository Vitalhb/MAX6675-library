// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple
#include <arduino.h>
#include <limits.h>

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include <util/delay.h>
#include <stdlib.h>
#include "max6675.h"

MAX6675::MAX6675(int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;

  //define pin modes
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);

  digitalWrite(cs, HIGH);
}

//double MAX6675::readCelsius(void)
int16_t MAX6675::iReadCelsius(void) 
{

  uint16_t v;

  digitalWrite(cs, LOW);
#if USE_FAST_READ
  _delay_us(FAST_READ_DELAY);
#else // Normal clock
  _delay_ms(1);
#endif //USE_FAST_CLK

  v = spiread();
  v <<= 8;
  v |= spiread();

  digitalWrite(cs, HIGH);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return -1;
    //return -100;
  }

  v >>= 3;

  return v;
}

byte MAX6675::spiread(void) { 
  int i;
  byte d = 0;

  for (i=7; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
#if USE_FAST_READ
	 _delay_us(FAST_READ_DELAY);
#else // Normal clock
    _delay_ms(1);
#endif //USE_FAST_CLK
    if (digitalRead(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    digitalWrite(sclk, HIGH);
#if USE_FAST_READ
	 _delay_us(FAST_READ_DELAY);
#else // Normal clock
	 _delay_ms(1);
#endif //USE_FAST_CLK
  }

  return d;
}
