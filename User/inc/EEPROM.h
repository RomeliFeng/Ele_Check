/*
 * EEPROM.h
 *
 *  Created on: 2016年8月3日
 *      Author: Romeli
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#define CurrentBatteryPower_Add 0x0000
#define UsedBatteryPower_Add 0x0010

typedef enum {
	CurrentBatteryPower, UsedBatteryPower
} EEPROMType;

union _lfTo8byte {
	double lf;
	uint8_t bytes[8];
}lfTo8byte;
struct _EEPROMData {
	double CurrentBatteryPower;
	double UsedBatteryPower;
} EEPROMData;

void EEPROM_WriteBytes(EEPROMType type);
void EEPROM_Read(EEPROMType type);

#endif /* EEPROM_H_ */
