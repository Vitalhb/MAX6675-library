#pragma once

// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple
// Modified by VitalHB - 2018

#define USE_FAST_READ 1
#define FAST_READ_DELAY 10 //us

class MAX6675
{
public:
	MAX6675(int8_t SCLK, int8_t CS, int8_t MISO);

	// returns integer temperature in Celsius * 4 (0.25C resolution).
	// returns -1 when thermocouple is not connected.
	int16_t iReadCelsius(void);

	double readCelsius(void)  __attribute__((always_inline))
	{
		return iReadCelsius() * 0.25;
	}

	double readFahrenheit(void)  __attribute__((always_inline))
	{
		return iReadCelsius() * (0.25 * 9.0 / 5.0) + 32;
	}

	// For compatibility with older versions:
	double readFarenheit(void)  __attribute__((always_inline))
	{
		return readFahrenheit();
	}

private:
	int8_t sclk, miso, cs;
	uint8_t spiread(void);
};
