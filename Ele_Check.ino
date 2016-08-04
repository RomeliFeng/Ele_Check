#include <Servo.h>
#include <OneWire.h>
#include "GPS.h"
#include "SerialSW.h"
#include "ADCSW.h"
#include "Wire.h"
#include "MCP3421.h"
#include "Battery.h"
#include "MPU6050.h"
#include "GPRS.h"
#include "EEPROM.h"
#include <stdlib.h>
#include "string.h"
#include "DS18B20.h"

Servo Lock;

char SendData[80];
uint8_t Safe = 1;

void setup() {
	Serial.begin(115200);
	Serial1.begin(115200);
	Wire.begin();
	ADCSW_Init();
	SerialSW_Init();
	Battery_Init();
	MCP_Init();
	MPU_Init();
	GPRS_Init();

	EEPROMData.CurrentBatteryPower = 9.85625;
//	EEPROM_ReadBytes(CurrentBatteryPower_Add, &EEPROMData.CurrentBatteryPower,
//			8);
	EEPROM_ReadBytes(UsedBatteryPower);
}

void loop() {
	char tmpchar[10];

	uint32_t DS_t = millis();
	uint32_t Bat_t = millis();
	uint32_t MPU_t = millis();
	uint32_t EEPROM_t = millis();
	uint32_t GPRS_t = millis();
	uint32_t GPS_t = millis();
	uint32_t MCP_t = millis();
	uint32_t BT_t = millis();
	uint32_t DS_l = 10000, Bat_l = 5000, MPU_l = 2000, EEPROM_l = 600000,
			GPRS_l = 6000, GPS_l = 6000, MCP_l = 1000, BT_l = 2000;
	while (1) {
		if (millis() - DS_t > DS_l) {
			DS18B20_GetTempture();
			DS_t = millis();
		}
		if (millis() - Bat_t > Bat_l) {
			Battery_GetVoltage();
			Bat_t = millis();
		}
		if (millis() - MPU_t > MPU_l) {
			MPU_GetData();
			if ((MPUData.ACC_X + MPUData.ACC_Y) > 2000 && MCP_Now <= 0.1) {
				Safe = 0;
				GPRS_l = 3000;

			} else {
				Safe = 1;
				GPRS_l = 6000;
			}
			MPU_t = millis();
		}
		if (millis() - EEPROM_t > EEPROM_l) {
			EEPROM_WriteBytes(UsedBatteryPower);
			EEPROM_t = millis();
		}
		if (millis() - GPRS_t > GPRS_l) { ///////////////////////////////////////////////////////////////////////
			for (int i = 0; i < 80; i++)
				SendData[i] = 0;
			strcpy(SendData, "BATTERY:000001||888888||");
			strcat(SendData, FtoA(Battery.ALL.Voltage));
			strcat(SendData, "||");
			strcat(SendData,
					GPSData.latitude[0] == '\0' ? "" : GPSData.latitude);
			strcat(SendData, "||");
			strcat(SendData,
					GPSData.longitude[0] == '\0' ? "" : GPSData.longitude);
			strcat(SendData, "||");
			strcat(SendData, FtoA(Temperture));
			strcat(SendData, "||");
			strcat(SendData, FtoA(9.853));
			strcat(SendData, "||");
			strcat(SendData, Safe == 1 ? "1" : "0");
			strcat(SendData, ":END");
			GPRS_CheckSignal();
			GPRS_SendData(SendData);
			GPRS_t = millis();
		}
		if (millis() - GPS_t > GPS_l) {
			GPS_Convert();
			GPS_t = millis();
		}
		if (millis() - MCP_t > MCP_l) {
			MCP_Now = MCP_GetDate();
			EEPROMData.UsedBatteryPower += MCP_Now * (millis() - MCP_t)
					* 0.000001;
			MCP_t = millis();
		}
		if (millis() - BT_t > BT_l) {
			strcpy(SendData, "BATTERY||000001||888888||");
			strcat(SendData, FtoA(Battery.ALL.Voltage));
			strcat(SendData, "||");
			strcat(SendData, FtoA(Battery.Bat1.Voltage));
			strcat(SendData, "||");
			strcat(SendData, FtoA(Battery.Bat2.Voltage));
			strcat(SendData, "||");
			strcat(SendData, FtoA(Battery.Bat3.Voltage));
			strcat(SendData, "||");
			strcat(SendData, FtoA(Battery.Bat4.Voltage));
			strcat(SendData, "||");
			strcat(SendData, FtoA(Battery.Bat5.Voltage));
			strcat(SendData, "||");
			strcat(SendData, FtoA(Battery.Bat6.Voltage));
			strcat(SendData, "||");
			strcat(SendData, FtoA(MCP_Now));
			strcat(SendData, "||");
			itoa(MPUData.ACC_X, tmpchar, 10);
			strcat(SendData, tmpchar);
			strcat(SendData, "||");
			itoa(MPUData.ACC_Y, tmpchar, 10);
			strcat(SendData, tmpchar);
			strcat(SendData, "||");
			strcat(SendData,
					GPSData.latitude[0] == '\0' ? "Null" : GPSData.latitude);
			strcat(SendData, "||");
			strcat(SendData,
					GPSData.longitude[0] == '\0' ? "Null" : GPSData.longitude);
			strcat(SendData, "||");
			strcat(SendData, FtoA(Temperture));
			strcat(SendData, "||");
			strcat(SendData, FtoA(9.853));
			strcat(SendData, "||");
			strcat(SendData, Safe == 1 ? "1" : "0");
			strcat(SendData, ":END");
			SerialSW_Switch(SerialBT);
			delay(1);
			Serial1.println(SendData);
			BT_t = millis();
		}
	}
}

char * FtoA(float F) {
	static char tmp11[8];
	char tmp22[5];
	int FF = F;
	int lF = (F - FF) * 1000;
	itoa(FF, tmp11, 10);
	itoa(lF, tmp22, 10);
	strcat(tmp11, ".");
	if (lF < 100) {
		tmp22[0] = '0';
	}
	strcat(tmp11, tmp22);
	return tmp11;
}
