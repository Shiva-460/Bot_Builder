#pragma once
#ifndef botBuilder_h
#define botBuilder_h


#include "Wires.h"
#include "src/lineFollowing/lineFollowing.h"
#include "src/DeadReckoning/DeadReckoner.h"
#include "src/BotNavigation/odometry.h"
#include "IK.h"
#include "src/SerialCallResponse/serialPiCom.h"


LineSensor leftLineSensor(LEFT_LINE_SENSOR), rightLineSensor(RIGHT_LINE_SENSOR);
long positionLeft = -999;
long positionRight = -999;

Motors motors(RIGHT_MOTOR_ENABLE, LEFT_MOTOR_ENABLE, RIGHT_MOTOR_TOP_WIRE, RIGHT_MOTOR_BOTTOM_WIRE, LEFT_MOTOR_TOP_WIRE, LEFT_MOTOR_BOTTOM_WIRE);

// Defines the states of the main loop
enum states { Line_Follow, look_for_syringe, drive_to_syringe,recheck_for_syringe, final_rotate_toward_syringe, final_rotate_toward_syringe_backup, pick_up_syringe, return_to_origin };
states state;

LobotServoController xArm(Serial2);

// Stores the servos of the arm as an array, from servo 1 to servo 6
LobotServo servos[6];// = {500, 500, 500, 500, 500, 500};
piData check;
Encoder leftEncoder(LEFT_MOTOR_BCD_YELLOW_A, LEFT_MOTOR_BCD_WHITE_B);
Encoder rightEncoder(RIGHT_MOTOR_BCD_YELLOW_A, RIGHT_MOTOR_BCD_WHITE_B);
NavOdometery navData(&leftEncoder, &rightEncoder,&motors);
#define STEADYSTATECAMERADELAY 2000
#define DISTANCE_UNTIL_CHECK 350.0
// define this constant to be used whenever checking the camera.
#endif // !botBuilder_h

void dropoff() {

	xArm.moveServos(6, 1000, 1, 735, 2, 877, 3, 132, 4, 857, 5, 687, 6, 892);

	delay(1000);

	xArm.moveServos(6, 1000, 1, 735, 2, 877, 3, 34, 4, 838, 5, 617, 6, 892);

	delay(1000);

	xArm.moveServos(6, 1000, 1, 450, 2, 877, 3, 34, 4, 838, 5, 617, 6, 892);

	delay(1000);

}