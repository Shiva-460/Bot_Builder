#include "lineFollowing.h"


void lineFollow(Motors motors,LineSensor leftSide,LineSensor rightSide)
{
  if(leftSide.isBright())
	{

	  motors.left();
	} 
  else if(rightSide.isBright())
	{

	  motors.right();
	} 
  else 
	{
	
	  motors.drive();
	}
 }
