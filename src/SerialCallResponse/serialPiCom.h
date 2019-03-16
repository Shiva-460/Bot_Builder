#pragma once
#ifndef serialpicom_h
#define serialpicom_h
struct piData
{
	float coordx, coordy, coordz;
	int syringeBool;

};
piData SerialSendReceive();
#endif