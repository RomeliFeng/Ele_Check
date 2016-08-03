/*
 * GPS.h
 *
 *  Created on: 2016年7月20日
 *      Author: Romeli
 */

#ifndef GPS_H_
#define GPS_H_

typedef struct {
	uint8_t hour, minute, seconds;
	char latitude[12], longitude[12];
	char lat, lon;
	uint8_t satellites;
} _GPSData;

extern char GPSFrame[255];
extern _GPSData GPSData;

bool GPS_GetFrame();
void GPS_Convert();

#endif /* GPS_H_ */
