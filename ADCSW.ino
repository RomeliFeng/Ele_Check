#include "ADCSW.h"

#define ADCSW_CONA P3_2
#define ADCSW_CONB P6_6
#define ADCSW_CONC P1_6

void ADCSW_Init() {
	pinMode(ADCSW_CONA, OUTPUT);
	pinMode(ADCSW_CONB, OUTPUT);
	pinMode(ADCSW_CONC, OUTPUT);
	digitalWrite(ADCSW_CONA, LOW);
	digitalWrite(ADCSW_CONB, LOW);
	digitalWrite(ADCSW_CONC, LOW);
}

void ADCSW_Switch(ADCCH ch) {
	switch (ch) {
	case ADC1:
		digitalWrite(ADCSW_CONA, HIGH);
		digitalWrite(ADCSW_CONB, LOW);
		digitalWrite(ADCSW_CONC, LOW);
		break;
	case ADC2:
		digitalWrite(ADCSW_CONA, LOW);
		digitalWrite(ADCSW_CONB, HIGH);
		digitalWrite(ADCSW_CONC, LOW);
		break;
	case ADC3:
		digitalWrite(ADCSW_CONA, HIGH);
		digitalWrite(ADCSW_CONB, HIGH);
		digitalWrite(ADCSW_CONC, LOW);
		break;
	case ADC4:
		digitalWrite(ADCSW_CONA, LOW);
		digitalWrite(ADCSW_CONB, LOW);
		digitalWrite(ADCSW_CONC, HIGH);
		break;
	case ADC5:
		digitalWrite(ADCSW_CONA, HIGH);
		digitalWrite(ADCSW_CONB, LOW);
		digitalWrite(ADCSW_CONC, HIGH);
		break;
	case ADC6:
		digitalWrite(ADCSW_CONA, LOW);
		digitalWrite(ADCSW_CONB, HIGH);
		digitalWrite(ADCSW_CONC, HIGH);
		break;
	}
}
