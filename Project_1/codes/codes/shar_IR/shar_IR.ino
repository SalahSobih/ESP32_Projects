#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "time.h"
#include <SharpIR.h>

//#define ir_pin 34
//#define model 1080
int ir_pin = 34;
long model = 1080.0;

SharpIR My_Sensor(ir_pin, model);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  delay(2000);

  //unsigned long pepe1=millis();  // takes the time before the loop on the library begins

  int dis=My_Sensor.getDistance();  // this returns the distance to the object you're measuring
  dis = (dis*0.88)+3.4;

  Serial.print("Mean distance: ");  // returns it to the serial monitor
  Serial.println(dis);
  
  //unsigned long pepe2=millis()-pepe1;  // the following gives you the time taken to get the measurement
 // Serial.print("Time taken (ms): ");
 // Serial.println(pepe2);  
}
