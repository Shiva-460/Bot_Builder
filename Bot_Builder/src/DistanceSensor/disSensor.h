#ifndef disSensor_H
#define disSensor_H
#include <Arduino.h>
class distanceSensor
{
  public:
  int inputLine;
  distanceSensor(int Analogpin);
  bool tooClose();
  uint16_t distance();
  
  
};
 #endif
