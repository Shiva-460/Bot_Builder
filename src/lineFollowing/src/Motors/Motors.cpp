/*
 * Christopher Marisco
 * February 23, 2019
 * 
 * Motors.cpp
 * Implementation source file of Motors.h
 * Used primarily for custom arduino library.
 */

#include "Arduino.h"
#include "Motors.h"

/*****Constructor*****/
Motors::Motors(int mr_en, int ml_en, int mr_da, int mr_db, int ml_da, int ml_db){
  pinMode(mr_en, OUTPUT);
  pinMode(ml_en, OUTPUT);
  pinMode(mr_da, OUTPUT);
  pinMode(mr_db, OUTPUT);
  pinMode(ml_da, OUTPUT);
  pinMode(ml_db, OUTPUT);
  motorR_on_pin = mr_en;
  motorL_on_pin = ml_en;
  motorR_Direction_A = mr_da;
  motorR_Direction_B = mr_db;
  motorL_Direction_A = ml_da;
  motorL_Direction_B = ml_db;
}

void Motors::drive(){
  drive_mr();
  drive_ml();
}

void Motors::right(){
  //drive_mr();
  drive_ml();
  //reverse_ml();
  reverse_mr();
}

void Motors::left(){
  //drive_ml();
  drive_mr();
  //reverse_mr();
  reverse_ml();
}
void Motors::slowRight() {
	//drive_mr();
	drive_ml();
	//reverse_ml();
	//reverse_mr();
}

void Motors::slowLeft() {
	//drive_ml();
	drive_mr();
	//reverse_mr();
	//reverse_ml();
}

void Motors::reverse(){
  reverse_mr();
  reverse_ml();
}

void Motors::drive_mr(){
  mr_fwd();
  if(!digitalRead(motorR_on_pin))
  {
  analogWrite(motorR_on_pin, 64);
  delay(20);
  analogWrite(motorR_on_pin, 128);
  delay(20);
  analogWrite(motorR_on_pin, 192);
  delay(2);
  analogWrite(motorR_on_pin, 255);
  delay(2);
  }
  digitalWrite(motorR_on_pin, HIGH);
}

void Motors::drive_ml(){
  ml_fwd();
  if(!digitalRead(motorL_on_pin))
  {
  analogWrite(motorL_on_pin, 64);
  delay(20);
  analogWrite(motorL_on_pin, 128);
  delay(20);
  analogWrite(motorL_on_pin, 192);
  delay(2);
  analogWrite(motorL_on_pin, 255);
  delay(2);
  digitalWrite(motorL_on_pin, HIGH);  
  }
  digitalWrite(motorL_on_pin, HIGH); 
}

void Motors::reverse_mr(){
  mr_rev();
    if(!digitalRead(motorR_on_pin))
  {
  analogWrite(motorR_on_pin, 64);
  delay(20);
  analogWrite(motorR_on_pin, 128);
  delay(20);
  analogWrite(motorR_on_pin, 192);
  delay(2);
  analogWrite(motorR_on_pin, 255);
  delay(2);
  }
  digitalWrite(motorR_on_pin, HIGH);
}

void Motors::reverse_ml(){
  ml_rev();
 if(!digitalRead(motorL_on_pin))
  {
  analogWrite(motorL_on_pin, 64);
  delay(20);
  analogWrite(motorL_on_pin, 128);
  delay(20);
  analogWrite(motorL_on_pin, 192);
  delay(2);
  analogWrite(motorL_on_pin, 255);
  delay(2);
  digitalWrite(motorL_on_pin, HIGH);  
  }
  digitalWrite(motorL_on_pin, HIGH); 
}

void Motors::park(){
  digitalWrite(motorR_on_pin, LOW);
  digitalWrite(motorL_on_pin, LOW);
  stop_motors();
}

void Motors::forward_motors(){
  mr_fwd();
  ml_fwd(); 
}

void Motors::reverse_motors(){
  mr_rev();
  ml_rev();  
}

void Motors::mr_fwd(){
  digitalWrite(motorR_Direction_A, HIGH);
  digitalWrite(motorR_Direction_B, digitalRead(motorR_Direction_A) ^ 1);
}

void Motors::ml_fwd(){
  digitalWrite(motorL_Direction_A, HIGH);
  digitalWrite(motorL_Direction_B, digitalRead(motorL_Direction_A) ^ 1);
}

void Motors::mr_rev(){
  digitalWrite(motorR_Direction_A, LOW);
  digitalWrite(motorR_Direction_B, digitalRead(motorR_Direction_A) ^ 1);
}

void Motors::ml_rev(){
  digitalWrite(motorL_Direction_A, LOW);
  digitalWrite(motorL_Direction_B, digitalRead(motorL_Direction_A) ^ 1);
}
void Motors::stop_motors(){
  stop_mr();
  stop_ml(); 
}

void Motors::stop_mr(){
  digitalWrite(motorR_Direction_A, LOW);
  digitalWrite(motorR_Direction_B, LOW);
}

void Motors::stop_ml(){
  digitalWrite(motorL_Direction_A, LOW);
  digitalWrite(motorL_Direction_B, LOW);  
}
