/* ----------------------------------------------------------------------- */
//By David P. Anderson
#define WHEEL_BASE 9.73
#define LEFT_CLICKS_PER_INCH 79.52
#define RIGHT_CLICKS_PER_INCH 79.48

/* ----------------------------------------------------------------------- */
/* odometer maintains these global variables: */

float theta;                    /* bot heading */
float X_pos;                    /* bot X position in inches */
float Y_pos;                    /* bot Y position in inches */

/* ----------------------------------------------------------------------- */


void odometers()
{
  int lsamp, rsamp, L_ticks, R_ticks, last_left, last_right;
  float left_inches, right_inches, inches;

        while (1) {

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
                left_inches = (float)L_ticks/LEFT_CLICKS_PER_INCH;
                right_inches = (float)R_ticks/RIGHT_CLICKS_PER_INCH;

    /* calculate distance we have traveled since last sampling */
                inches = (left_inches + right_inches) / 2.0;
  
    /* accumulate total rotation around our center */
                theta += (left_inches - right_inches) / WHEEL_BASE;

    /* and clip the rotation to plus or minus 360 degrees */
                theta -= (float)((int)(theta/TWOPI))*TWOPI;

    /* now calculate and accumulate our position in inches */
                Y_pos += inches * cos(theta); 
                X_pos += inches * sin(theta); 

    /* and suspend ourself in the multi-tasking queue for 50 ms */
    /* giving other tasks a chance to run */
                msleep(50);
        }
}
