#include "serialPiCom.h"
#include <arduino.h>
void clearBuffer()
{ 
  
  while(Serial.available() > 0);
  //Serial1.print("cleared buffer\n");
}

piData SerialSendReceive()
{
  piData toReturn;
  toReturn.syringeBool = 0; //make sure this value isn't garbage even if the pi doesn't send a properly formed packet.
 Serial.print("S");  
  if (Serial.available() > 0) 
  {
    if(Serial.peek() == ':') 
    {
      Serial.read();
      while(Serial.available()<1); 
      toReturn.syringeBool = Serial.parseInt();
      while(Serial.available()<1);
      toReturn.coordx = Serial.parseFloat();
      while(Serial.available()<1);
      toReturn.coordy = Serial.parseFloat();
      while(Serial.available()<1); 
      toReturn.coordz = Serial.parseFloat();
    
    }
    else 
    {
      
      clearBuffer();
    }
  }
}
