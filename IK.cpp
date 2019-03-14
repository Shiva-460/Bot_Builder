#include "IK.h"
void IK(LobotServo servos[], float pos_x, float pos_y, float pos_z){
	servos[0].Position = 100;
  // Calculate the shifted "real" x-y position
  float a = sqrt(sq(pos_x)+sq(pos_z));
  float b = (pos_y);

  // Calculate the angle to rotate the base
  float phi = atan(pos_z / pos_x);
  // Calculate common repeatedly used values
  float a_squared = sq(a);
  float b_squared = sq(b);
  float b_on_a = b / a;
  
  // Calculate the values that the "wrist" should be at, x and y
  float x = ((a + b_on_a * b) - sqrt(sq(a + b_on_a * b) - (1 + sq(b_on_a))*(a_squared + b_squared - sq(l_p)))) / (1 + sq(b_on_a));
  float y = b_on_a * x;
  //float x = l_p * cos(PI*2/3/*+2*b/sqrt(a_squared+b_squared)*/) + a;
  //float y = l_p * sin(PI*2/3/*+2*b/sqrt(a_squared+b_squared)*/) + b;

  // Calculate the length of B, the actual distance from the origin to the "wrist"
  //float B = sqrt(a_squared + b_squared) - l_p;
  float B = sqrt(sq(x)+sq(y));
  // Calculate the base angles of the main triangle
  float beta;
  //if ((sq(l_3)+sq(l_2)-sq(B)) > 0)
    beta = acos((sq(l_3)+sq(l_2)-sq(B))/(2*l_3*l_2));
  //else
  //  beta = PI / 2 + acos((sq(l_3)+sq(l_2)-sq(B))/(2*l_3*l_2));
  //float theta = atan(b_on_a);
  float theta = atan(y/x);
  float alpha = acos((sq(B)+sq(l_2)-sq(l_3))/(2*l_2*B));
  float gamma = PI - alpha - beta;

  float x_1 = l_2*cos(alpha+theta);
  float y_1 = l_2*sin(alpha+theta);

  float x_2 = (l_2 * (sin(alpha+theta) + 1/(tan(alpha+theta))*cos(alpha+theta))) / (b_on_a + 1/tan(alpha+theta));
  float y_2 = b_on_a * x_2;

  float y_3 = (y-y_1)/(x-x_1)*(a-x)+y;
  float D = sqrt(sq(a-x)+sq(y_3-y));
  float P = b - y_3;
  float p = acos((sq(l_p)+sq(D)-sq(P))/(2*l_p*D));

  
  float A = sqrt(sq(l_2*cos(alpha+theta)-x_2)+sq(l_2*sin(alpha+theta)-y_2));
  float beta_prime = asin((B-sqrt(sq(x_2)+sq(y_2))) / A * sin(gamma));
  if (beta_prime < 0)
    beta_prime = 0;

  
  //float omega = PI/ 2 - gamma ;//PI / 2 + alpha + beta;

  // Update the servo values by shifting the values and scaling them from radians to (0, 1000)
  servos[4].Position = (int)((alpha + theta) * 800 / PI) + 100; // Shoulder
  servos[3].Position = 900 - (int)((beta_prime) * 900 / PI); // Elbow
  servos[2].Position = (int)((p) * 500 / PI) + 500; // Wrist

  // Wiggle around
  //servos[1]
  //servos[2].Position = (int)(1000*1/3);
  if (y_3 < b){
    servos[2].Position = (int)(450 + p * 900 / PI);
  }
  else{
    servos[2].Position = (int)(450 - p * 900 / PI);
  }
  if (phi > 0)
    servos[5].Position = 500 * phi / PI;
  else
    servos[5].Position = 500 - 500 * phi / PI;
  // Print out values for debugging
  /*
  Serial.print("beta_prime: "); Serial.println(beta_prime);
  Serial.print("alpha: "); Serial.println(alpha);
  Serial.print("theta: "); Serial.println(theta);
  Serial.print("b_on_a: "); Serial.println(b_on_a);
  Serial.print("p: "); Serial.println(p);
  Serial.print("in p: "); Serial.println((sq(l_p)+sq(D)-sq(P))/(2*l_p*D));
  Serial.print("D: "); Serial.println(D);
  Serial.print("in D: "); Serial.println(x);
  Serial.print("y_1: "); Serial.println(y_1);
  Serial.print("y_3: "); Serial.println(y_3);
    Serial.print("y: "); Serial.println(y);
  Serial.print("x: "); Serial.println(x);

  Serial.print("Discriminant: "); Serial.println(sq(a + b_on_a * b) - (1 + sq(b_on_a))*(a_squared + b_squared - l_p));
  */
  //Serial.println((sq(l_3)+sq(l_2)-sq(B))/(2*l_3*l_2));
  
  //Serial.print(servos[2].Position);
}

void initialize_servos(LobotServo servos[]){
  int i;
  for (i = 0; i < 6/*sizeof(servos) / sizeof(LobotServo)*/; i++){
      servos[i].ID = i+1;
      servos[i].Position = 450;
  }
}
