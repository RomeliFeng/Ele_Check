/*
 * SerialSW.h
 *
 *  Created on: 2016年7月31日
 *      Author: Romeli
 */

#ifndef SERIALSW_H_
#define SERIALSW_H_

typedef enum _SerialCH {
	SerialGPRS = 0, SerialCon, SerialGPS, SerialBT
} SerialCH;

void SerialSW_Init();
void SerialSW_Switch(SerialCH ch);

#endif /* SERIALSW_H_ */
