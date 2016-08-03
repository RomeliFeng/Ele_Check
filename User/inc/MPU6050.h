/*
 * MPU6050.h
 *
 *  Created on: 2016年8月2日
 *      Author: Romeli
 */

#ifndef MPU6050_H_
#define MPU6050_H_

struct _MPUData{
	uint16_t ACC_X;
	uint16_t ACC_Y;
	uint16_t ACC_Z;
} MPUData;

void MPU_Init();
void MPU_GetData();
void MPU_WriteByte(uint8_t WAdd,uint8_t Data);

#endif /* MPU6050_H_ */
