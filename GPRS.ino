#include "GPRS.h"
#include "SerialSW.h"
#include "string.h"

_GPRSSignal GPRSSignal;

void GPRS_Init() {
	SerialSW_Switch(SerialGPRS);
	delay(1);
//	Serial1.println("AT+CFUN=0");
//	delay(5);
//	Serial1.println("AT+CFUN=4");
//	delay(5);
//	Serial1.println("AT+CFUN=1");
//	delay(5);
	Serial1.println("AT+CIPMUX=0");			//设置连接为单连接
	delay(5);
	Serial1.println("AT+CIPMODE=0");		//设置连接为非透传模式
	delay(5);
}

void GPRS_CheckSignal() {
	char buffer[255];
	char *ttt, *ttt2;
	uint8_t i = 0;
	SerialSW_Switch(SerialGPRS);
	delay(1);
	//Get CSQ
	while (Serial1.available())
		Serial1.read();
	Serial1.println("AT+CSQ");
	delay(10);
	i = 0;
	while (Serial1.available())
		buffer[i++] = Serial1.read();
	ttt = strchr(buffer, ':') + 1;
	GPRSSignal.CSQ = atoi(ttt);

	//Get GSM Resistor
	while (Serial1.available())
		Serial1.read();
	Serial1.println("AT+CREG?");
	delay(10);
	i = 0;
	while (Serial1.available())
		buffer[i++] = Serial1.read();
	ttt = strchr(buffer, ':') + 1;
	GPRSSignal.CREG = *(ttt + 3) == '1' ? 1 : 0;

	//Get GPRS Resistor
	while (Serial1.available())
		Serial1.read();
	Serial1.println("AT+CGREG?");
	delay(10);
	i = 0;
	while (Serial1.available())
		buffer[i++] = Serial1.read();
	ttt = strchr(buffer, ':') + 1;
	GPRSSignal.CGREG = *(ttt + 3) == '1' ? 1 : 0;

	//Get GPRS Resistor
	while (Serial1.available())
		Serial1.read();
	Serial1.println("AT+CGREG?");
	delay(10);
	i = 0;
	while (Serial1.available())
		buffer[i++] = Serial1.read();
	ttt = strchr(buffer, ':') + 1;
	GPRSSignal.CGREG = *(ttt + 3) == '1' ? 1 : 0;

	//Get 运营商
	while (Serial1.available())
		Serial1.read();
	Serial1.println("AT+COPS?");
	delay(10);
	i = 0;
	while (Serial1.available())
		buffer[i++] = Serial1.read();
	ttt = strchr(buffer, 0x22);
	ttt2 = strchr(ttt + 1, 0x22);
	for (int i = 0; i < 20; i++)
		GPRSSignal.COPS[i] = '\0';
	strncpy(GPRSSignal.COPS, ttt + 1, ttt2 - ttt - 1);
	GPRSSignal.COPS[ttt2 - ttt - 1] = '\0';
}

void GPRS_SendData(char* str) {
	SerialSW_Switch(SerialGPRS);
	delay(1);
	Serial1.print("AT+CSTT=");				//设置GPRS接入点
	Serial1.write(0x22);
	Serial1.print("CMNET");
	Serial1.write(0x22);
	Serial1.println("");
	delay(5);
	Serial1.println("AT+CIICR");			//激活移动场景
	delay(800);
	Serial1.println("AT+CIFSR");			//激活移动场景
	delay(5);
	Serial1.print("AT+CIPSTART=");
	Serial1.write(0x22);
	Serial1.print("TCP");
	Serial1.write(0x22);
	Serial1.print(",");
	Serial1.write(0x22);
	Serial1.print("home.vvv.moe");
	Serial1.write(0x22);
	Serial1.println(",9000");
	delay(1800);
	Serial1.println("AT+CIPSEND");
	delay(10);
	while (Serial1.available())
		Serial1.read();
	while (*str != '\0')
		Serial1.write(*str++);
	Serial1.write('\r');
	Serial1.write('\n');
	Serial1.write(0x1a);
	delay(800);
//	Serial1.println("AT+CIPCLOSE");
//	delay(20);
//	Serial1.println("AT+CIPSHUT");
//	delay(20);
}
