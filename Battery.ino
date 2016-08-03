#include "Battery.h"
#include "ADCSW.h"

void Battery_Init() {
	analogReadResolution(12);
}
void Battery_GetVoltage() {
	ADCSW_Switch(ADC1);
	delay(1);
	Battery.Bat1.Voltage = ((float) analogRead(A5) * ADCConvert - BatDiff)
			/ Bat1Factor
	;
	ADCSW_Switch(ADC2);
	delay(1);
	Battery.Bat2.Voltage = ((float) analogRead(A5) * ADCConvert - BatDiff)
			/ Bat2Factor - Battery.Bat1.Voltage - 0.01;
	ADCSW_Switch(ADC3);
	delay(1);
	Battery.Bat3.Voltage = ((float) analogRead(A5) * ADCConvert - BatDiff)
			/ Bat3Factor
	;
	ADCSW_Switch(ADC4);
	delay(1);
	Battery.Bat4.Voltage = ((float) analogRead(A5) * ADCConvert - BatDiff)
			/ Bat4Factor
	;
	ADCSW_Switch(ADC5);
	delay(1);
	Battery.Bat5.Voltage = ((float) analogRead(A5) * ADCConvert - BatDiff)
			/ Bat5Factor
	;
	ADCSW_Switch(ADC6);
	delay(1);
	Battery.Bat6.Voltage = ((float) analogRead(A5) * ADCConvert - BatDiff)
			/ Bat6Factor
	;
	Battery.ALL.Voltage = Battery.Bat1.Voltage + Battery.Bat2.Voltage
			+ Battery.Bat3.Voltage + Battery.Bat4.Voltage + Battery.Bat5.Voltage
			+ Battery.Bat6.Voltage;
}
