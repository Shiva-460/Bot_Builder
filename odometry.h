
/*
 * Christopher Marisco 
 * 3/5/19
 * Odometry Implementation file.
 */

#include <math.h>		/* trig function header */
#include <Encoder.h>            /* read from encoders */

#include "Wires.h"
//wheel base 205 or 221.5 mm (depends if from mid of wheels or just between wheels)
//rwheel diameter = 82.14 mm
//lwheel diameter = 80.51 mm
//right_clicks_per_mm = 18.74
//left_clicks_per_mm = 18.85

/* ----------------------------------------------------------------------- */

#define WHEEL_BASE 221.5
#define LEFT_CLICKS_PER_MM 19.36
#define RIGHT_CLICKS_PER_MM 19.23

#define TWOPI 6.2831853070		/* nice to have float precision */
#define RADS 57.2958			/* radians to degrees conversion */

/* ----------------------------------------------------------------------- */
/* odometers() maintains these global accumulator variables: */

double theta = 0.0;                    /* bot heading */
double theta_D = 0.0;
double X_pos = 0.0;                    /* bot X position in mm */
double Y_pos = 0.0;                    /* bot Y position in mm */
double total_mm = 0.0;             /* total mm traveled */

/* using these local variables */

double left_mm = 0.0;
double right_mm = 0.0;
double mm = 0.0;

/* ----------------------------------------------------------------------- */
long lsamp = 0, rsamp = 0, L_ticks = 0, R_ticks = 0, last_left = 0, last_right = 0;

/* ----------------------------------------------------------------------- */
/* locate_target() uses these global variables */

double X_target;                 /* X lateral target position */
double Y_target;                 /* Y vertical target position */
double target_bearing = 0.0;           /* bearing in radians from current position */

double target_distance = 0.0;         	/* distance in inches from position */
double heading_error = 0.0;            /* heading error in degrees */

/* ----------------------------------------------------------------------- */
/*  calculate distance and bearing to target.

        inputs are:  X_target, X_pos, and Y_target, Y_pos
        outputs are: target_distance, heading_error
*/

Encoder knobLeft(LEFT_MOTOR_BCD_YELLOW_A, LEFT_MOTOR_BCD_WHITE_B);
Encoder knobRight(RIGHT_MOTOR_BCD_YELLOW_A, RIGHT_MOTOR_BCD_WHITE_B);


void odometers()
{

             

        /* sample the left and right encoder counts as close together */
		/* in time as possible */
                lsamp = knobLeft.read();
                rsamp = knobRight.read(); 

		/* determine how many ticks since our last sampling? */
                L_ticks = lsamp - last_left; 	
                R_ticks = rsamp - last_right;

		/* and update last sampling for next time */
                last_left = lsamp; 
                last_right = rsamp; 

		/* convert longs to floats and ticks to inches */
                left_mm = (double)L_ticks/LEFT_CLICKS_PER_MM;
                right_mm = (double)R_ticks/RIGHT_CLICKS_PER_MM;

		/* calculate distance we have traveled since last sampling */
                mm = (left_mm + right_mm) / 2.0;
	
		/* accumulate total rotation around our center */
                theta += (left_mm - right_mm) / WHEEL_BASE;

		/* and clip the rotation to plus or minus 360 degrees */
                theta -= (double)((int)(theta/TWOPI))*TWOPI;
		theta_D = theta * 180/PI;

		/* now calculate and accumulate our position in inches */
                Y_pos += mm * cos(theta); 
                X_pos += mm * sin(theta); 

        
}

//void locate_target() 
//{
//            double x = 0.0, y = 0.0;
//
//	
//
        	//x = X_target - X_pos;
        	//y = Y_target - Y_pos;

        	//target_distance = sqrt((x*x)+(y*y));
	
        	/* no divide-by-zero allowed! */
        	//if (x > 0.00001) target_bearing = 90.0 - atan(y/x);
        	//else if (x < -0.00001) target_bearing = -90.0 - atan(y/x);

        	//heading_error = target_bearing - (theta*RADS);
        	//if (heading_error > 180.0) heading_error -= 360.0;
		    //else if (heading_error < -180.0) heading_error += 360.0;

	
//}
