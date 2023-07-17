#include <SharpIR.h>

#define ir A0
#define model 1080

SharpIR SharpIR(ir, model);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(2000);   
  unsigned long startTime=millis();  // takes the time before the loop on the library begins
  int dis=SharpIR.getDistance();  // this returns the distance to the object you're measuring

  Serial.print("Mean distance: ");  // returns it to the serial monitor
  Serial.println(dis);
  
  unsigned long calcTime=millis()-startTime;  // the following gives you the time taken to get the measurement
  Serial.print("Time taken (ms): ");
  Serial.println(calcTime);  
}
