#include <LineSensor.h>
#include <Motors.h>

LineSensor leftSide(45), rightSide(45);

const int mr_en = 25; //Motor 1 PWM Speed Control Pin, Pin 1 on L239
const int ml_en = 24; //Motor 2 PWM Speed Control Pin, Pin 9 on L239

const int mr_da = 28; //Motor 1 Directional Control A, Pin 2 on L239
const int mr_db = 29; //Motor 1 Directional Control B, Pin 7 on L239
const int ml_da = 41; //Motor 2 Directional Control A, Pin 15 on L239
const int ml_db = 40; //Motor 2 Directional Control B, Pin 10 on L239

Motors motors(mr_en, ml_en, mr_da, mr_db, ml_da, ml_db);

void setup() {
  
}

void loop() {
  
  lineFollow();

}

void lineFollow()
{
  auto startTime = millis();
  while((startTime - millis()) < 500)
  {
    //linefollow code here
    while(leftSide.isBright() && (startTime - millis()) < 500)
      motors.left();
    while(rightSide.isBright() && (startTime - millis()) < 500)
      motors.right();
    motors.drive();
  }
  //return after ~500 milliseconds
}
