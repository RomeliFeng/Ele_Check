/*
 * GPRS.h
 *
 *  Created on: 2016年8月2日
 *      Author: Romeli
 */

#ifndef GPRS_H_
#define GPRS_H_

typedef struct{
	uint8_t CSQ;
	uint8_t CREG;
	uint8_t CGREG;
	char COPS[20];
}_GPRSSignal;

void GPRS_Init();
void GPRS_CheckSignal();
void GPRS_SendData(char* str);

extern _GPRSSignal GPRSSignal;

#endif /* GPRS_H_ */
