#ifndef IK_h
#define IK_h
#include <LobotServoController.h>

// Constant definitions
#define l_1 1
#define l_2 10
#define l_3 10
#define l_p 16.5

void IK(LobotServo servos[], float pos_x, float pos_y, float pos_z);
void initialize_servos(LobotServo servos[]);
#endif
