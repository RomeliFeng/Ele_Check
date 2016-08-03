#include "MPU6050.h"
#include "Wire.h"

#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	ACCEL_XOUT		0x3B
#define	ACCEL_YOUT		0x3D
#define	ACCEL_ZOUT		0x3F

#define MPU_Add 0x69

void MPU_Init() {
	MPU_WriteByte(PWR_MGMT_1, 0x00);			//reset
	MPU_WriteByte(SMPLRT_DIV, 0x07);			//陀螺仪采样率，典型值：0x07(125Hz)
	MPU_WriteByte(CONFIG, 0x06);				//低通滤波频率，典型值：0x06(5Hz)
	MPU_WriteByte(GYRO_CONFIG, 0x18);		//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	MPU_WriteByte(ACCEL_CONFIG, 0x01);	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
}

void MPU_GetData() {
	Wire.beginTransmission(MPU_Add);
	Wire.write(ACCEL_XOUT);
	Wire.endTransmission();
	Wire.requestFrom(MPU_Add, 6);
	MPUData.ACC_X = (uint16_t) Wire.read() << 8;
	MPUData.ACC_X |= (uint16_t) Wire.read();
	MPUData.ACC_Y = (uint16_t) Wire.read() << 8;
	MPUData.ACC_Y |= (uint16_t) Wire.read();
	MPUData.ACC_Z = (uint16_t) Wire.read() << 8;
	MPUData.ACC_Z |= (uint16_t) Wire.read();

	MPUData.ACC_X /= 64;
	MPUData.ACC_Y /= 64;
	MPUData.ACC_Z /= 64;
}

void MPU_WriteByte(uint8_t WAdd, uint8_t Data) {
	Wire.beginTransmission(MPU_Add);
	Wire.write(WAdd);
	Wire.write(Data);
	Wire.endTransmission();
}
