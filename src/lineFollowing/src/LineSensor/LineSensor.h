/*
 * Author: Spencer Sawyer
 * February 25 2019
 * 
 * Line sensor header file.
 * Built for LineSensing Library of TCES 460 Embedded systems.
 * 
 */

 #ifndef LineSensor_H
 #define LineSensor_H

 #include "Arduino.h"

 class LineSensor{
  public:
    int inputLine;
    LineSensor(int);
    uint32_t value();
    boolean isBright();
    boolean isDark();
};
#endif
