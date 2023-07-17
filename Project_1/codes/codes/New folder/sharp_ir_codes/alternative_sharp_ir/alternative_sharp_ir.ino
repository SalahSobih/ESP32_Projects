#include <SharpIR.h>
SharpIR sensor( SharpIR::GP2Y0A41SK0F, 34 );  

void setup()
{
  Serial.begin(115200); //Enable the serial comunication
}

void loop()
{
  delay(2000);
  int distance = sensor.getDistance(); //Calculate the distance in centimeters and store the value in a variable

  Serial.println( distance+10 ); //Print the value to the serial monitor
}
