/*
 * Christopher Marisco
 * Spencer Sawyer
 * 
 * Bot_Builder.ino
 * This file houses the main functions of the automomous robot.
 * 
 */

//View = testing without motor power.
//Test = testing with motor power.

//#include <Encoder.h> Used in odometry.h

#include "Wires.h"
#include "src/lineFollowing/lineFollowing.h"
#include "src/DeadReckoning/DeadReckoner.h"
#include "odometry.h"



LineSensor leftSide(LEFT_LINE_SENSOR), rightSide(RIGHT_LINE_SENSOR);

const int mr_en = RIGHT_MOTOR_ENABLE; //Motor 1 PWM Speed Control Pin, Pin 1 on L239
const int ml_en = LEFT_MOTOR_ENABLE; //Motor 2 PWM Speed Control Pin, Pin 9 on L239

const int mr_da = RIGHT_MOTOR_TOP_WIRE; //Motor 1 Directional Control A, Pin 2 on L239
const int mr_db = RIGHT_MOTOR_BOTTOM_WIRE; //Motor 1 Directional Control B, Pin 7 on L239
const int ml_da = LEFT_MOTOR_TOP_WIRE; //Motor 2 Directional Control A, Pin 15 on L239
const int ml_db = LEFT_MOTOR_BOTTOM_WIRE; //Motor 2 Directional Control B, Pin 10 on L239

long positionLeft  = -999;
long positionRight = -999;

double degree;
double overshoot;

double dist;




Motors motors(mr_en, ml_en, mr_da, mr_db, ml_da, ml_db);
/***Enums used to control states for testing***/
enum origin {
    DRIVE, TURN
    
};

origin o;

void setup() {
  /*****Test_Target*****/
  //targets are used in odometry.h

  X_target = 500.0; //50 cm
  Y_target = 500.0; //50 cm
  dist = 0.0;
  degree = 45.0;
  overshoot = 3.0;
  Serial.begin(9600); 
  Serial.println("Current Position: ");
  

}
void loop() {
  
  //view_Encoders();
  //test_Encoders();
  //view_Odometry();//*/odometers();
  //test_Odometry();
  //test_Y_Distance();
  view_Target();
  turnRightToDegrees(degree); 
  //turnLeftToDegrees(degree);
  test_Y_Distance();
}

void view_Encoders(){

  //Include these statements in setup first:
  /***********************/
  //Serial.begin(115200); //9600 for Arduino IDE.
  //Serial.println("Two Wheels Encoder Test: ");
  /***********************/

  //Encoder's view while driving:
  long newLeft, newRight;
  
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
}

void test_Encoders(){
  view_Encoders();
  motors.drive();
}

void view_Odometry(){
  /***********************/
  /***********************/

  //if (lsamp != last_left || rsamp != last_right) {
    Serial.print("X Position in cm = ");
    Serial.print(X_pos/10);
    Serial.print(", Y Position in cm = ");
    Serial.print(Y_pos/10);
    Serial.print(", Theta = ");
    Serial.print(theta_D);
    Serial.println();

  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both Encoders to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }

  /*
   * Called from odometry.h
   * Used to calculate actual positions X_pos, X_target, etc...
   */
  odometers();

}

//Untested.
//TO-DO.
void test_Odometry(){
  //view_Odometry();
  motors.drive();
}

/*****Tests Turning*****/

void turnRightToDegrees(double degree)
{
  while(theta_D <= degree + overshoot){
    /*view_Odometry();//*/odometers();
    WHEEL_BASE = 250;
    motors.right();
  }
  WHEEL_BASE = 221.5;
  motors.park();
}

void turnLeftToDegrees(double degree)
{
  while(theta_D >= degree + overshoot){
    /*view_Odometry();//*/odometers();
    WHEEL_BASE = 250;
    motors.left();
  }
  WHEEL_BASE = 221.5;
  motors.park();
}


//Untested.
//TO-DO.
void view_Target(){
  /*view_Odometry();//*/odometers();
  locate_target();
  //dist = target_distance;
  

  Serial.print("X Position in cm = ");
  Serial.print(X_pos/10);
  Serial.print(", Y Position in cm = ");
  Serial.print(Y_pos/10);
  Serial.print(", Theta = ");
  Serial.print(theta_D);
  Serial.println();

  Serial.print("Target X in cm = ");
  Serial.print(X_target/10);
  Serial.print(", Target Y in cm = ");
  Serial.print(Y_target/10);
  Serial.print(", Distance in cm = ");
  Serial.print(target_distance/10);
  Serial.print(", Target Bearing = ");
  Serial.print(target_bearing);
  Serial.print(", Heading Error = ");
  Serial.print(heading_error);
  Serial.println();
  
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both Encoders to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
}

void test_Y_Distance(){
  //*view_Odometry();//*/odometers();
  while((Y_pos/10.0) < 50.0){
    odometers();
    motors.drive();
  }
    motors.park();
  
}
