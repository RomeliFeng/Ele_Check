/*
 * Battery.h
 *
 *  Created on: 2016年8月1日
 *      Author: Romeli
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#define ADCConvert 3.3/4096
#define Bat1Factor 0.500
#define Bat2Factor 0.2533
#define Bat3Factor 0.506
#define Bat4Factor 0.506
#define Bat5Factor 0.515
#define Bat6Factor 0.485
#define BatDiff 0.01

typedef struct {
	float Voltage;
} _BatteryInfo;

struct _Battery {
	_BatteryInfo Bat1;
	_BatteryInfo Bat2;
	_BatteryInfo Bat3;
	_BatteryInfo Bat4;
	_BatteryInfo Bat5;
	_BatteryInfo Bat6;
	_BatteryInfo ALL;
} Battery;

void Battery_Init();
void Battery_GetVoltage();

#endif /* BATTERY_H_ */
