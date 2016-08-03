#include "OneWire.h"

OneWire ds(P2_5);

float Temperture = 0;

void DS18B20_GetTempture(void) {
	byte i;
	byte data[12];

	ds.reset();
	ds.skip();
	ds.write(0x44, 1);    // start conversion, with parasite power on at the end

	delay(800);     // maybe 750ms is enough, maybe not
	// we might do a ds.depower() here, but the reset will take care of it.

	ds.reset();
	ds.skip();
	ds.write(0xBE);         // Read Scratchpad

	for (i = 0; i < 9; i++) {           // we need 9 bytes
		data[i] = ds.read();
	}

	int16_t raw = (data[1] << 8) | data[0];

	Temperture = (float) raw / 16.0;
}
