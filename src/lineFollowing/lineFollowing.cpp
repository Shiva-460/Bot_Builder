#include "LineSensor/LineSensor.h"
#include "Motors/Motors.h"

void lineFollow(Motors motors,LineSensor leftSide,LineSensor rightSide)
{
  //auto startTime = millis();
  //while((startTime - millis()) < 500)
  {
    //linefollow code here
    if(leftSide.isBright() )
      motors.left();
    if(rightSide.isBright())
      motors.right();
    motors.drive();
  }
  //return after ~500 milliseconds
}
