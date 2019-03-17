
/*
 * Christopher Marisco
 * Spencer Sawyer
 * 
 * 
 * 
 */

//View = testing without motor power.
//Test = testing with motor power.

#include "botbuilder.h"

void setup() {
	
 
  Serial.begin(38400); //for pi communication
  Serial2.begin(9600); // For arm communication
  Serial.println("Current Position: ");
  state = Line_Follow;
  check.syringeBool = 0; //ensure that this value isn't garbage.
  dropoff(); //set arm to the default state
}
void loop() {
	switch (state)
	{
	case Line_Follow:
		lineFollow(motors, leftLineSensor, rightLineSensor);
		if ((navData.left_mm + navData.right_mm) / 2 > DISTANCE_UNTIL_CHECK/*mm*/)
		{
			state = look_for_syringe;
		}
		else 
		{
			state = Line_Follow;
		}
		break;
	case look_for_syringe:
		motors.park();
		navData.resetOdometry(); //anytime we stop at a known place, (e.g. the line) we should reset our odometry. Otherwise we'll never linefollow again.
		navData.turnRightToDegrees(90);// turn outward to check for Syringes

		delay(STEADYSTATECAMERADELAY);
		check = SerialSendReceive();
		if (check.syringeBool==1)
		{
			state = drive_to_syringe;
		}
		else
		{
			navData.turnRightToDegrees(0);
			state = Line_Follow;
		}
		
		break;
	case drive_to_syringe:
		navData.go_and_get(NavOdometeryFunc::rotateCoordsX(check.coordz, check.coordx, navData.theta) - navData.X_pos,
			NavOdometeryFunc::rotateCoordsY(check.coordz, check.coordx, navData.theta) - navData.Y_pos,
			0.70); //blocking function
		state = recheck_for_syringe;

		break;
	case recheck_for_syringe:
		delay(STEADYSTATECAMERADELAY); //always wait for the camera to catch up
		check = SerialSendReceive();
		if (check.syringeBool)
		{
			navData.go_and_get(NavOdometeryFunc::rotateCoordsX(check.coordz, check.coordx, navData.theta) - navData.X_pos,
				NavOdometeryFunc::rotateCoordsY(check.coordz, check.coordx, navData.theta) - navData.Y_pos,
				0.9);//blocking function
			state = final_rotate_toward_syringe;
		}
		else
		{
			state = return_to_origin;
		}
		break;
	case final_rotate_toward_syringe:
		delay(STEADYSTATECAMERADELAY); //always wait for the camera to catch up
		check = SerialSendReceive();
		if (check.syringeBool)
		{
			navData.go_and_get(NavOdometeryFunc::rotateCoordsX(check.coordz, check.coordx, navData.theta) - navData.X_pos,
				NavOdometeryFunc::rotateCoordsY(check.coordz, check.coordx, navData.theta) - navData.Y_pos,
				0.0);//rotate toward but do not go forward anymore, We're assuming we're close enough here. THis might need to be a feedback loop however.
			state = pick_up_syringe;
		}
		else
		{
			navData.rev_dist(20);
			state = final_rotate_toward_syringe_backup;
		}
		break;
	case final_rotate_toward_syringe_backup: //esentially a "try again" to find the syringe
		delay(STEADYSTATECAMERADELAY); //always wait for the camera to catch up
		check = SerialSendReceive();
		if (check.syringeBool)
		{
			navData.go_and_get(NavOdometeryFunc::rotateCoordsX(check.coordz, check.coordx, navData.theta) - navData.X_pos,
				NavOdometeryFunc::rotateCoordsY(check.coordz, check.coordx, navData.theta) - navData.Y_pos,
				0.0);//rotate toward but do not go forward anymore, We're assuming we're close enough here. THis might need to be a feedback loop however.
			state = pick_up_syringe;
		}
		else //this time though, we'll just return to the origin if it's not there.
		{
			state = return_to_origin;
		}
		break;

	case pick_up_syringe:
		IK(servos, 30, -14, 0); //attempt to pick up the syringe
		xArm.moveServos(servos,6,1000); 

		break;
	case return_to_origin:
		navData.go_and_get(0, 0, 1);
		navData.turnToDegrees(0);
		break;
	}

}

