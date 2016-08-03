#include "GPS.h"
#include "atof.h"
#include <string.h>
#include "SerialSW.h"

#define Max_TimeLimit 500

char GPSFrame[255] = "";
_GPSData GPSData;

bool GPS_GetFrame() {
	long TimeLimit = millis();
	SerialSW_Switch(SerialGPS);
	delay(1);
	while (Serial1.available())
		Serial1.read();
	while (true) {
		if (millis() - TimeLimit > Max_TimeLimit)
			return false;
		if (Serial1.available() >= 100)
			break;
	}
	Serial1.readBytes(GPSFrame, 100);
	return true;
}
void GPS_Convert() {
	char *p;
	long time;
	char degreebuff[10];
	float latitude, longitude;
	float latitudeDegrees, longitudeDegrees;
	long minutes;
	int32_t degree;
	degreebuff[9] = '\0';
	int inte;
	int inte2;
	long inte3;
	char tmp[12];
	char tmp2[6];
	char tmp3[6];
	if (!GPS_GetFrame())
		return;
	p = strstr(GPSFrame, "GPGGA");
	// get time
	p = strchr(p, ',') + 1;
	time = atof(p);
	GPSData.hour = time / 10000;
	GPSData.minute = (time % 10000) / 100;
	GPSData.seconds = (time % 100);

	// parse out latitude
	p = strchr(p, ',') + 1;
	if (',' != *p) {
		strncpy(degreebuff, p, 2);
		p += 2;
		degreebuff[2] = '\0';
		degree = atol(degreebuff) * 10000000;
		strncpy(degreebuff, p, 2); // minutes
		p += 3; // skip decimal point
		strncpy(degreebuff + 2, p, 4);
		degreebuff[6] = '\0';
		minutes = 50 * atol(degreebuff) / 3;
		latitude = degree / 100000 + minutes * 0.000006F;
		latitudeDegrees = (latitude - 100 * int(latitude / 100)) / 60.0;
		latitudeDegrees += int(latitude / 100);
		inte = latitudeDegrees;
		inte2 = (latitudeDegrees - inte) * 10000;
		inte3 = (latitudeDegrees - inte) * 10000000 - inte2 * 1000;
		itoa(inte, tmp, 10);
		itoa(inte2, tmp2, 10);
		itoa(inte3, tmp3, 10);
		itoa(inte, tmp, 10);
		itoa(inte2, tmp2, 10);
		itoa(inte3, tmp3, 10);
		strcat(tmp, ".");
		strcat(tmp, tmp2);
		strcat(tmp, tmp3);
		strcpy(GPSData.latitude, tmp);
	}

	p = strchr(p, ',') + 1;
	if (',' != *p) {
		if (p[0] == 'N')
			GPSData.lat = 'N';
		else if (p[0] == 'S')
			GPSData.lat = 'S';
		else if (p[0] == ',')
			GPSData.lat = 0;
		else
			return;
	}

	// parse out longitude
	p = strchr(p, ',') + 1;
	if (',' != *p) {
		strncpy(degreebuff, p, 3);
		p += 3;
		degreebuff[3] = '\0';
		degree = atol(degreebuff) * 10000000;
		strncpy(degreebuff, p, 2); // minutes
		p += 3; // skip decimal point
		strncpy(degreebuff + 2, p, 4);
		degreebuff[6] = '\0';
		minutes = 50 * atol(degreebuff) / 3;
		longitude = degree / 100000 + minutes * 0.000006F;
		longitudeDegrees = (longitude - 100 * int(longitude / 100)) / 60.0;
		longitudeDegrees += int(longitude / 100);
		inte = longitudeDegrees;
		inte2 = (longitudeDegrees - inte) * 10000;
		inte3 = (longitudeDegrees - inte) * 10000000 - inte2 * 1000;
		itoa(inte, tmp, 10);
		itoa(inte2, tmp2, 10);
		itoa(inte3, tmp3, 10);
		strcat(tmp, ".");
		strcat(tmp, tmp2);
		strcat(tmp, tmp3);
		strcpy(GPSData.longitude, tmp);
	}

	p = strchr(p, ',') + 1;
	if (',' != *p) {
		if (p[0] == 'W')
			GPSData.lon = 'W';
		else if (p[0] == 'E')
			GPSData.lon = 'E';
		else if (p[0] == ',')
			GPSData.lon = 0;
		else
			return;
	}

	p = strchr(p, ',') + 1;
	p = strchr(p, ',') + 1;
	if (',' != *p) {
		GPSData.satellites = atoi(p);
	}
}
