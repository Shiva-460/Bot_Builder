#include "lineFollowing.h"


void lineFollow(Motors motors,LineSensor leftSide,LineSensor rightSide)
{
  //{
    //linefollow code here
   // if(leftSide.isBright() )
     // motors.left();
    //if(rightSide.isBright())
      //motors.right();
    //motors.drive();
  //}
  //return after ~500 
  
  if(leftSide.isBright()){
    //Serial.print("Left\n");
    //delay(1000);
    motors.left();
  } else if(rightSide.isBright()){
    //Serial.print("Right\n");
    //delay(1000);
    motors.right();
  } else {
    //Serial.print("Drive\n");
 
    //delay(1000);
    motors.drive();
  }
  /*Serial.print('\n');
  Serial.print(rightSide.value());
    Serial.print('\n');

    Serial.print(leftSide.value());
      Serial.print('\n');
*/}
