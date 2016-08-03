#include <SerialSW.h>

#define SerialSW_CONA P2_2
#define SerialSW_CONB P7_4

void SerialSW_Init() {
	pinMode(SerialSW_CONA,OUTPUT);
	pinMode(SerialSW_CONB,OUTPUT);
	digitalWrite(SerialSW_CONA,LOW);
	digitalWrite(SerialSW_CONB,LOW);
}

void SerialSW_Switch(SerialCH ch) {
	switch (ch) {
	case SerialGPRS:
		digitalWrite(SerialSW_CONA,LOW);
		digitalWrite(SerialSW_CONB,LOW);
		break;
	case SerialCon:
		digitalWrite(SerialSW_CONA,HIGH);
		digitalWrite(SerialSW_CONB,LOW);
		break;
	case SerialGPS:
		digitalWrite(SerialSW_CONA,LOW);
		digitalWrite(SerialSW_CONB,HIGH);
		break;
	case SerialBT:
		digitalWrite(SerialSW_CONA,HIGH);
		digitalWrite(SerialSW_CONB,HIGH);
		break;
	}
}
