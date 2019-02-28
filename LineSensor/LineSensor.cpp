/*
 * Author: Spencer Sawyer
 * February 25, 2019
 * 
 * Implementation file for LineSensor.h
 *
 */

#include "Arduino.h"
#include "LineSensor.h"

/*****Constructor*****/

LineSensor::LineSensor(int digiPin){
    inputLine = digiPin;
}
/*****Methods*****/

uint32_t LineSensor::value(){
    pinMode(inputLine, OUTPUT);
    digitalWrite(inputLine, HIGH);
    delayMicroseconds(100);
    auto beginT = micros();
    pinMode(inputLine, INPUT);
    while (digitalRead(inputLine) == HIGH && ((micros() - beginT) < 1000))
      ;
    return micros() - beginT;
}

boolean LineSensor::isBright(){
    return value() < 120;
}

boolean LineSensor::isDark(){
    return !isBright();
}