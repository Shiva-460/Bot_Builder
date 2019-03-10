
/*
 * Christopher Marisco 
 * 3/5/19
 * Odometry Implementation file.
 */

#include <math.h>		/* trig function header */
//wheel base 205 mm roughly. need a better instrument.
//rwheel diameter = 82.14 mm
//lwheel diameter = 80.51 mm

/* ----------------------------------------------------------------------- */

#define WHEEL_BASE 9.73
#define LEFT_CLICKS_PER_INCH 79.52
#define RIGHT_CLICKS_PER_INCH 79.48

#define TWOPI 6.2831853070		/* nice to have float precision */
#define RADS 57.2958			/* radians to degrees conversion */

/* ----------------------------------------------------------------------- */
/* odometers() maintains these global accumulator variables: */

double theta = 0.0;                    /* bot heading */
double X_pos = 0.0;                    /* bot X position in inches */
double Y_pos = 0.0;                    /* bot Y position in inches */
double total_inches = 0.0;             /* total inches traveled */

/* using these local variables */

double left_inches = 0.0;
double right_inches = 0.0;
double inches = 0.0;

/* ----------------------------------------------------------------------- */
unsigned long lsamp = 0, rsamp = 0, L_ticks = 0, R_ticks = 0, last_left = 0, last_right = 0;

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


void odometers()
{

             

        /* sample the left and right encoder counts as close together */
		/* in time as possible */
                lsamp = left_distance;
                rsamp = right_distance; 

		/* determine how many ticks since our last sampling? */
                L_ticks = lsamp - last_left; 	
                R_ticks = rsamp - last_right;

		/* and update last sampling for next time */
                last_left = lsamp; 
                last_right = rsamp; 

		/* convert longs to floats and ticks to inches */
                left_inches = (double)L_ticks/LEFT_CLICKS_PER_INCH;
                right_inches = (double)R_ticks/RIGHT_CLICKS_PER_INCH;

		/* calculate distance we have traveled since last sampling */
                inches = (left_inches + right_inches) / 2.0;
	
		/* accumulate total rotation around our center */
                theta += (left_inches - right_inches) / WHEEL_BASE;

		/* and clip the rotation to plus or minus 360 degrees */
                theta -= (double)((int)(theta/TWOPI))*TWOPI;

		/* now calculate and accumulate our position in inches */
                Y_pos += inches * cos(theta); 
                X_pos += inches * sin(theta); 

        
}

void locate_target() 
{
            double x = 0.0, y = 0.0;

	

        	x = X_target - X_pos;
        	y = Y_target - Y_pos;

        	target_distance = sqrt((x*x)+(y*y));
	
        	/* no divide-by-zero allowed! */
        	if (x > 0.00001) target_bearing = 90.0 - atan(y/x);
        	else if (x < -0.00001) target_bearing = -90.0 - atan(y/x);

        	heading_error = target_bearing - (theta*RADS);
        	if (heading_error > 180.0) heading_error -= 360.0;
		    else if (heading_error < -180.0) heading_error += 360.0;

	
}
