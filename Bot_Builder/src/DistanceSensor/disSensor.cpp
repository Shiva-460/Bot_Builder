#include "disSensor.h"
#include <Arduino.h>

 
  distanceSensor::distanceSensor(int Analogpin)
  {
    inputLine = Analogpin;
  }
  bool distanceSensor::tooClose()
  {
	  //TODO:
    //find what distance is too close for quickly changing direction
  }
  uint16_t distanceSensor::distance()
  {
    //return a number between 0 and 100 to indicate how far away an object is from the sensor.
    
    uint16_t result = analogRead(inputLine);
    
    result+=analogRead(inputLine);
    result+=analogRead(inputLine);
    result+=analogRead(inputLine);
    result+=analogRead(inputLine);
    result+=analogRead(inputLine);
    result=result>>6;
    return result;
  }
  
  
