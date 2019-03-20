
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
	initialize_servos(servos);
 
  Serial.begin(38400); //for pi communication
  Serial3.begin(9600); // For arm communication
  //Serial.println("Current Position: ");
  //state = Line_Follow;
  state = look_for_syringe;
  check.syringeBool = 0; //ensure that this value isn't garbage.
  dropoff(); //set arm to the default state

  
  //navData.go_and_get(1000, 1000, 1);
  //DEBUG
  //navData.turnToDegrees(17);
  //Serial.print(navData.theta_D);
  //navData.go_and_get(NavOdometeryFunc::rotateCoordsX( .01 * 1000,.566 * 1000, navData.theta) + navData.X_pos,
  //NavOdometeryFunc::rotateCoordsY( .01 * 1000,.556 * 1000, navData.theta) + navData.Y_pos ,
  //0.70);
  // navData.go_and_get(100,-100, 1);// TESTED WORKS!
  while (SerialSendReceive(&check).piPresent == 0); //if the pi isn't sending data, don't start moving.
}
void(*reset)(void) = 0;
void loop() {

	if (!check.piPresent) reset();
		
	navData.odometers();
	//Serial3.println(state);
	switch (state)
	{
	case Line_Follow:
		lineFollow(motors, leftLineSensor, rightLineSensor);

		//Serial.print(navData.left_mm);
		if (navData.totalMM > DISTANCE_UNTIL_CHECK/*mm*/)
		{
			state = look_for_syringe;
			break;
		}
		else 
		{
			state = Line_Follow;
		}
		break;
	case look_for_syringe:
		motors.park();
		navData.resetOdometry(); //anytime we stop at a known place,
		navData.turnToDegrees(90);// turn outward to check for Syringes
		navData.turnToDegrees(90);
		motors.park();
		delay(STEADYSTATECAMERADELAY);
		check = SerialSendReceive(&check);


		if (check.syringeBool)
		{
			state = drive_to_syringe;
			break;
		}
		else
		{
			
			navData.turnToDegrees(5);
			navData.drive_dist(30);
			motors.park();
			navData.resetOdometry();
			state = Line_Follow;
		}
		
		break;
	case drive_to_syringe:
		navData.go_and_get(NavOdometeryFunc::rotateCoordsX(check.coordx * 1000, check.coordz * 1000, navData.theta) + navData.X_pos,
			NavOdometeryFunc::rotateCoordsY(check.coordx * 1000, check.coordz * 1000, navData.theta) + navData.Y_pos,
			0.70); //blocking function
		state = recheck_for_syringe;

		break;
	case recheck_for_syringe:
		delay(STEADYSTATECAMERADELAY); //always wait for the camera to catch up
		check = SerialSendReceive(&check);
		if (check.syringeBool)
		{
			navData.go_and_get(NavOdometeryFunc::rotateCoordsX(check.coordx * 1000, check.coordz * 1000,
				navData.theta) + navData.X_pos,
				NavOdometeryFunc::rotateCoordsY( check.coordx*1000,check.coordz*1000,
					navData.theta) + navData.Y_pos,
				1.2);//blocking function
			state = pick_up_syringe;
			break;
		}
		else
		{
			state = return_to_origin;
		}
		break;


	case pick_up_syringe:
		IK(servos, 22, -16, 0); //attempt to pick up the syringe
		upward();
		xArm.moveServos(servos, 6, 2000);
		delay(2200);
		xArm.moveServo(6, 480, 300);
		delay(315);
		xArm.moveServo(2,350,200);
		
		delay(215);
		pickup();
		outFirst();
		dropoff();
		state = return_to_origin;
		delay(5000);

		break;
	default:
	case return_to_origin:
		navData.go_and_get(0, 0, 1.4);
		navData.turnToDegrees(0);
		navData.resetOdometry();
		state = Line_Follow;
		break;
	}

}

