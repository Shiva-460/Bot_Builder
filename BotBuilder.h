#pragma once
#ifndef botBuilder_h
#define botBuilder_h


#include "Wires.h"
#include "src/lineFollowing/lineFollowing.h"
#include "src/DeadReckoning/DeadReckoner.h"
#include "src/BotNavigation/odometry.h"
#include "IK.h"
#include "src/SerialCallResponse/serialPiCom.h"


LineSensor leftSide(LEFT_LINE_SENSOR), rightSide(RIGHT_LINE_SENSOR);
long positionLeft = -999;
long positionRight = -999;

Motors motors(RIGHT_MOTOR_ENABLE, LEFT_MOTOR_ENABLE, RIGHT_MOTOR_TOP_WIRE, RIGHT_MOTOR_BOTTOM_WIRE, LEFT_MOTOR_TOP_WIRE, LEFT_MOTOR_BOTTOM_WIRE);

// Defines the states of the main loop
enum states { follow_line, look_for_syringe, drive_to_syringe, pick_up_syringe, drive_to_origin };
states state;

LobotServoController xArm(Serial2);

// Stores the servos of the arm as an array, from servo 1 to servo 6
LobotServo servos[6];// = {500, 500, 500, 500, 500, 500};
piData check;
Encoder leftEncoder(LEFT_MOTOR_BCD_YELLOW_A, LEFT_MOTOR_BCD_WHITE_B);
Encoder rightEncoder(RIGHT_MOTOR_BCD_YELLOW_A, RIGHT_MOTOR_BCD_WHITE_B);
NavOdometery navData(&leftEncoder, &rightEncoder,&motors);

#endif // !botBuilder_h