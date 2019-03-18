#pragma once
#ifndef serialpicom_h
#define serialpicom_h
#define SERIAL_TIMEOUT 2000
struct piData
{
	float coordx, coordy, coordz;
	int syringeBool;
	int piPresent;

};
piData SerialSendReceive(piData * toReturn);
#endif