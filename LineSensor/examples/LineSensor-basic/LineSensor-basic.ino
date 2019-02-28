/*
 * Author: Spencer Sawyer
 * February 25, 2019
 * 
 * Test code for the LineSenor.
 * 
 */
#include <LineSensor.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  LineSensor leftSide(45), rightSide(45);
  Serial.print("\nleft bright?:");
  Serial.print(leftSide.isBright());
  Serial.print("\nright bright?:");
  Serial.print(rightSide.isBright());
  delay(1000); 
}
