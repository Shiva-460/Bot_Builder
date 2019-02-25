/*
 * Christopher Marisco
 * February 23, 2019
 * 
 * Motors.h
 * 
 * This file contains the definitions of the functions used in the autonomous_bot program
 * that pertain to engaging the L239D Dual H-Bridge Motors.
 * 
 */

 #ifndef Motors.h
 #define Motors.h

 #include "Arduino.h"

 class Motors {
  public:
  /*****Constructor*****/
    Motors(int m1_en, int m2_en, int m1_da, int m1_db, int m2_da, int m2_db);

  /*****method signatures*****/
    void drive();
    void reverse();
    void park();
    void drive_m1();
    void drive_m2();
    void reverse_m1();
    void reverse_m2();
    void forward_motors();
    void reverse_motors();
    void m1_fwd();
    void m2_fwd();
    void m1_rev();
    void m2_rev();
    void stop_motors();
    void stop_m1();
    void stop_m2();
    
  private:
  /*****Fields*****/
  const int motor1_on_pin, motor2_on_pin, motor1_Direction_A, motor1_Direction_B, motor2_Direction_A, motor2_Direction_B;  
};

#endif
