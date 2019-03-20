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

 #ifndef Motors_h
 #define Motors_h

 #include "Arduino.h"

 class Motors {
  public:
  /*****Constructor*****/
    Motors(int mr_en, int ml_en, int mr_da, int mr_db, int ml_da, int ml_db);

  /*****method signatures*****/
    void drive();
    void reverse();
    void park();
    void right();
    void left();
	void slowRight();
	void slowLeft();
    void drive_mr();
    void drive_ml();
    void reverse_mr();
    void reverse_ml();
    void forward_motors();
    void reverse_motors();
    void mr_fwd();
    void ml_fwd();
    void mr_rev();
    void ml_rev();
    void stop_motors();
    void stop_mr();
    void stop_ml();
    
  private:
  /*****Fields*****/
  int motorR_on_pin, motorL_on_pin, motorR_Direction_A, motorR_Direction_B, motorL_Direction_A, motorL_Direction_B;  
};

#endif
