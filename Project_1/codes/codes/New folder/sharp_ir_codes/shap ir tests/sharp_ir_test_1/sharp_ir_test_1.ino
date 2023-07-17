#include <SharpIR.h>

#define IR1 34 // define signal pin
int Distance;
//#define model1 GP2Y0A41SK0F // for GP2Y0A21YK0F  used 1080


SharpIR SharpIR1( SharpIR::GP2Y0A41SK0F, IR1);

void setup() {
 Serial.begin(115200);
 Serial.println("Robojax Sharp IR  ");
}

void loop() {
    // Sharp IR code for Robojax.com 20181201
    delay(2000);   

  unsigned long startTime=millis();  // takes the time before the loop on the library begins

  int temp_dis=SharpIR1.getDistance();  // this returns the distance for sensor 1
  Distance = (temp_dis*3)-1;
  // Sharp IR code for Robojax.com 20181201
  

  Serial.print("Distance: ");
  Serial.print(Distance);
  Serial.println("cm");
  
  
     // Sharp IR code for Robojax.com
     
}
