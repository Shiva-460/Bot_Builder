#include "serialPiCom.h"
#include <arduino.h>
void clearBuffer()
{ 
    auto start = millis();
  while(millis()-start<60) while(Serial.available() > 0) Serial.read();
  //clear out the buffer and give it enough time to have something placed into it.

  //Serial1.print("cleared buffer\n");
}

piData SerialSendReceive(piData * toReturn)
{
  
  toReturn->syringeBool = 0; //make sure this value isn't garbage even if the pi doesn't send a properly formed packet.
  toReturn->piPresent = 0; //if the pi isn't even present (not sending data) then we should know.
 Serial.print("S");  
 auto start = millis();
 while ((!(Serial.available() > 0)) && millis() < start + SERIAL_TIMEOUT); //while serial is not available,
                                                                           // and the timeout hasn't been reached wait.
  if (Serial.available() > 0) 
  {
    if(Serial.peek() == ':') 
    {
		toReturn->piPresent = 1;
      Serial.read();
      while(Serial.available()<1); 
      toReturn->syringeBool = Serial.parseInt();
      while(Serial.available()<3);
      toReturn->coordx = Serial.parseFloat();
      while(Serial.available()<3);
      toReturn->coordy = Serial.parseFloat();
      while(Serial.available()<3); 
      toReturn->coordz = Serial.parseFloat();
	  delay(1);	  
      clearBuffer(); //unsure if the line is empty? Clear it out!

    }
    else 
    {
      
      clearBuffer();
    }
  }
  return *toReturn;
 
}
