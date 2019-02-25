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
Motors::Motors(int m1_en, int m2_en, int m1_da, int m1_db, int m2_da, int m2_db){
  pinMode(m1_en, OUTPUT);
  pinMode(m2_en, OUTPUT);
  pinMode(m1_da, OUTPUT);
  pinMode(m1_db, OUTPUT);
  pinMode(m2_da, OUTPUT);
  pinMode(m2_db, OUTPUT);
  motor1_on_pin = m1_en;
  motor2_on_pin = m2_en;
  motor1_Direction_A = m1_da;
  motor1_Direction_B = m1_db;
  motor2_Direction_A = m2_da;
  motor2_Direction_B = m2_db;
}

void Motors::drive(){
  drive_m1();
  drive_m2();
}

void Motors::right(){
  drive_m1();
  reverse_m2();
}

void Motors::left(){
  drive_m2();
  reverse_m1();
}

void Motors::reverse(){
  reverse_m1();
  reverse_m2();
}

void Motors::drive_m1(){
  m1_fwd();
  digitalWrite(motor1_on_pin, HIGH);
}

void Motors::drive_m2(){
  m2_fwd();
  digitalWrite(motor2_on_pin, HIGH);  
}

void Motors::reverse_m1(){
  m1_rev();
  digitalWrite(motor1_on_pin, HIGH);
}

void Motors::reverse_m2(){
  m2_rev();
  digitalWrite(motor2_on_pin, HIGH);
}

void Motors::park(){
  digitalWrite(motor1_on_pin, LOW);
  digitalWrite(motor2_on_pin, LOW);
  stop_motors();
}

void Motors::forward_motors(){
  m1_fwd();
  m2_fwd(); 
}

void Motors::reverse_motors(){
  m1_rev();
  m2_rev();  
}

void Motors::m1_fwd(){
  digitalWrite(motor1_Direction_A, HIGH);
  digitalWrite(motor1_Direction_B, digitalRead(motor1_Direction_A) ^ 1);
}

void Motors::m2_fwd(){
  digitalWrite(motor2_Direction_A, HIGH);
  digitalWrite(motor2_Direction_B, digitalRead(motor2_Direction_A) ^ 1);
}

void Motors::m1_rev(){
  digitalWrite(motor1_Direction_A, LOW);
  digitalWrite(motor1_Direction_B, digitalRead(motor1_Direction_A) ^ 1);
}

void Motors::m2_rev(){
  digitalWrite(motor2_Direction_A, LOW);
  digitalWrite(motor2_Direction_B, digitalRead(motor2_Direction_A) ^ 1);
}
void Motors::stop_motors(){
  stop_m1();
  stop_m2(); 
}

void Motors::stop_m1(){
  digitalWrite(motor1_Direction_A, LOW);
  digitalWrite(motor1_Direction_B, LOW);
}

void Motors::stop_m2(){
  digitalWrite(motor2_Direction_A, LOW);
  digitalWrite(motor2_Direction_B, LOW);  
}
