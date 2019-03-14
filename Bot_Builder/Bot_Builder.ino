/*
 * Christopher Marisco
 * Spencer Sawyer
 * 
 * 
 * 
 */

//View = testing without motor power.
//Test = testing with motor power.

//#include <Encoder.h> Used in odometry.h

#include "Wires.h"
#include "src/lineFollowing/lineFollowing.h"
#include "src/DeadReckoning/DeadReckoner.h"
#include "odometry.h"
#include "IK.h"



//Encoder knobLeft(LEFT_MOTOR_BCD_YELLOW_A, LEFT_MOTOR_BCD_WHITE_B);
//Encoder knobRight(RIGHT_MOTOR_BCD_YELLOW_A, RIGHT_MOTOR_BCD_WHITE_B);

LineSensor leftSide(LEFT_LINE_SENSOR), rightSide(RIGHT_LINE_SENSOR);

const int mr_en = RIGHT_MOTOR_ENABLE; //Motor 1 PWM Speed Control Pin, Pin 1 on L239
const int ml_en = LEFT_MOTOR_ENABLE; //Motor 2 PWM Speed Control Pin, Pin 9 on L239

const int mr_da = RIGHT_MOTOR_TOP_WIRE; //Motor 1 Directional Control A, Pin 2 on L239
const int mr_db = RIGHT_MOTOR_BOTTOM_WIRE; //Motor 1 Directional Control B, Pin 7 on L239
const int ml_da = LEFT_MOTOR_TOP_WIRE; //Motor 2 Directional Control A, Pin 15 on L239
const int ml_db = LEFT_MOTOR_BOTTOM_WIRE; //Motor 2 Directional Control B, Pin 10 on L239

long positionLeft  = -999;
long positionRight = -999;





Motors motors(mr_en, ml_en, mr_da, mr_db, ml_da, ml_db);

enum origin {
    ZERO, NINETY
    
  };
  origin o;

// Defines the states of the main loop
enum states {follow_line, look_for_syringe, drive_to_syringe, pick_up_syringe, drive_to_origin};
states state;

LobotServoController xArm(Serial2);

// Stores the servos of the arm as an array, from servo 1 to servo 6
LobotServo servos[6];// = {500, 500, 500, 500, 500, 500};
void setup() {
  /*****Test_Target*****/
  //targets are used in odometry.h

  X_target = 500.0; //50 cm
  Y_target = 500.0; //50 cm
  origin o = ZERO;
  Serial.begin(9600);
  Serial2.begin(9600); // For arm communication
  Serial.println("Current Position: ");
}
void loop() {
  //view_Encoders();
  //test_Encoders();
  //view_Odometry();
  //test_Odometry();
  //test_Y_Distance();
  test_Turn();
  //delay(2000);

  switch (state) {
    // Default to line following
    case follow_line:
      lineFollow(motors, leftSide, rightSide);
      // Every 25cm turn to the right and look for a syringe
      if (total_mm >= 250){
        state = look_for_syringe;  
      }
      break;
      
    case look_for_syringe:
      // TO-DO reset origin
      turn_right_ninety();
      // Read from camera
      // Check if valid (?)
      // if (syringe == true)
      //    state = drive_to_syringe
      // else
      //    turn_left_ninety
      //    state = follow_line
      break;

    case drive_to_syringe:
      // Drive to within 10cm of the syringe
      // if syringe distance < 10cm
      //   state = drive_to_syringe
      // else
      //   state = pick_up_syringe;
     break;

    case pick_up_syringe:
       // IK(coordinates)
       state = drive_to_origin;
      break;
    default:
      state = follow_line;
      break;
  }
}

void turn_right_ninety(){
  if (o == ZERO && theta_D <= 90.0){
    motors.right();
  } else{
    o = NINETY;
  }
}

void turn_left_ninety(){
  if (o == NINETY && theta_D >= 0.0){
    motors.left();
   //motors.park();
  } else{
    o = ZERO;
  }
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
  view_Odometry();
  motors.drive();
}

/*****Tests Turning*****/

void test_Turn()
{

  /**States for turning**/
  view_Odometry();//*/odometers();

  if (o == ZERO && theta_D <= 90.0){
    
    motors.right();
  } else{
    o = NINETY;
    
  }
  

  if (o == NINETY && theta_D >= 0.0){
    motors.left();
   //motors.park();
  } else{
    o = ZERO;
  }
  //Serial.print(theta_D); Serial.print("\n");
}

//Untested.
//TO-DO.
void view_Targert(){
  /*view_Odometry();//*/odometers();
  locate_target();

  Serial.print("Target X in cm = ");
  Serial.print(X_target/10);
  Serial.print(", Target Y in cm = ");
  Serial.print(Y_target/10);
  Serial.print(", Distance in cm = ");
  Serial.print(target_distance/10);
  Serial.print(", Target Bearing = ");
  Serial.print(target_bearing);
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
  view_Odometry();//*/odometers();
  if((Y_pos/10.0) < 35.0){
    motors.drive();
  }else{
  motors.park();
  }
}
