#include "EEPROM.h"
#include "Wire.h"

#define EEPROME_Add 0x50

void EEPROM_WriteBytes(EEPROMType type) {
	Wire.beginTransmission(EEPROME_Add);
	Wire.write(UsedBatteryPower_Add >> 8);
	Wire.write(UsedBatteryPower_Add & 0x00ff);
	lfTo8byte.lf = EEPROMData.UsedBatteryPower;
	Wire.write(lfTo8byte.bytes, 8);
	Wire.endTransmission();
	delay(10);
}

void EEPROM_ReadBytes(EEPROMType type) {
	Wire.beginTransmission(EEPROME_Add);
	Wire.write(UsedBatteryPower_Add >> 8);
	Wire.write(UsedBatteryPower_Add & 0x00ff);
	Wire.endTransmission();
	lfTo8byte.lf = EEPROMData.UsedBatteryPower;
	Wire.requestFrom(EEPROME_Add, 8);
	Wire.readBytes((char *)lfTo8byte.bytes, 8);
	EEPROMData.UsedBatteryPower = lfTo8byte.lf;
}
