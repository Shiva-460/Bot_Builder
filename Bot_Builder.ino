#include "Wires.h"
#include "src/lineFollowing/lineFollowing.h"
const int mr_en = RIGHT_MOTOR_ENABLE; //Motor 1 PWM Speed Control Pin, Pin 1 on L239
const int ml_en = LEFT_MOTOR_ENABLE; //Motor 2 PWM Speed Control Pin, Pin 9 on L239

const int mr_da = RIGHT_MOTOR_TOP_WIRE; //Motor 1 Directional Control A, Pin 2 on L239
const int mr_db = RIGHT_MOTOR_BOTTOM_WIRE; //Motor 1 Directional Control B, Pin 7 on L239
const int ml_da = LEFT_MOTOR_TOP_WIRE; //Motor 2 Directional Control A, Pin 15 on L239
const int ml_db = LEFT_MOTOR_BOTTOM_WIRE; //Motor 2 Directional Control B, Pin 10 on L239
Motors motors(mr_en, ml_en, mr_da, mr_db, ml_da, ml_db);
LineSensor leftSide(LEFT_LINE_SENSOR), rightSide(RIGHT_LINE_SENSOR);

void setup() {
}

void loop() {
lineFollow(motors,leftSide, rightSide);
}
