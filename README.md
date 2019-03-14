# Bot_Builder
Simple repository to maintain autonomous bot control





//default position of xarm

void default(){

xArm.moveServos(6, 1000, 1, 735, 2, 877, 3, 132, 4, 857, 5, 687, 6,892);

}


//the action to drop off syringe to basket
void dropoff{
  
  xArm.moveServos(6, 1000, 1, 735, 2, 877, 3, 132, 4, 857, 5, 687, 6, 892);
 
 delay(1000);
 
 xArm.moveServos(6, 1000, 1, 735, 2, 877, 3, 34, 4, 838, 5, 617, 6, 892);
 
 delay(1000); 
 
 xArm.moveServos(6, 1000, 1, 450, 2, 877, 3, 34, 4, 838, 5, 617, 6, 892);
 
 delay(1000); 
  


}
