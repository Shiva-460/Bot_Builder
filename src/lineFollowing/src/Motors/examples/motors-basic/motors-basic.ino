/*
 * Christopher Marisco
 * February 24, 2019
 * 
 * Example code to test the motors library.
 * 
 */

#include <Motors.h>

/******MOTOR CONTROL PINS******/
//Motors and Arduino interface with the L239D Dual H-Bridge Motor Driver.
//Pin numberings based on the wiring diagram in referenced documentation.

const int mr_en = 25; //Motor 1 PWM Speed Control Pin, Pin 1 on L239
const int ml_en = 24; //Motor 2 PWM Speed Control Pin, Pin 9 on L239

const int mr_da = 28; //Motor 1 Directional Control A, Pin 2 on L239
const int mr_db = 29; //Motor 1 Directional Control B, Pin 7 on L239
const int ml_da = 41; //Motor 2 Directional Control A, Pin 15 on L239
const int ml_db = 40; //Motor 2 Directional Control B, Pin 10 on L239

Motors motors(mr_en, ml_en, mr_da, mr_db, ml_da, ml_db);
void setup() {

}

void loop() {
  motors.drive();
  delay(1000);
  motors.park();
  delay(1000);
  motors.right();
  delay(1000);
  motors.left();
  delay(1000);
  motors.park();
  delay(1000);
}
