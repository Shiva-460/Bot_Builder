#include "lineFollowing.h"


void lineFollow(Motors motors,LineSensor leftSide,LineSensor rightSide)
{
  if(leftSide.isBright())
	{
	  motors.park();
	  motors.left();
	  delay(TURNCONST);
	} 
  else if(rightSide.isBright())
	{
	  motors.park();
	  motors.right();
	  delay(TURNCONST);


	} 
  else 
	{
	
	  motors.drive();
	}
 }
