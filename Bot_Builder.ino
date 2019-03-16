
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
}
void loop() {


}






void dropoff(){

  xArm.moveServos(6, 1000, 1, 735, 2, 877, 3, 132, 4, 857, 5, 687, 6, 892);
  
  delay(1000);
  
  xArm.moveServos(6, 1000, 1, 735, 2, 877, 3, 34, 4, 838, 5, 617, 6, 892);
  
  delay(1000);
  
  xArm.moveServos(6, 1000, 1, 450, 2, 877, 3, 34, 4, 838, 5, 617, 6, 892);
  
  delay(1000);

}
