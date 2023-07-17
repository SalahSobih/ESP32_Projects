#include <WiFi.h>
#include "ThingsBoard.h"

const char* ssid = "Omar s";
const char* password = "oMaR&19102019$";

#define TOKEN               "OrsJjkYR2TeMX8ELzE3f"
#define THINGSBOARD_SERVER  "demo.thingsboard.io"

// for soil moisture
#define sensorPin 35
float sensorValue,moisture;
char* soil_status;
char* soil_Cracks;

// for ir sharp sensor
#define analog_pin 34    // analog pin
unsigned int avgValue;  
float temp_dis,final_dist;
int my_distance;
int buf[10],temp;

// function to get distance from ir sharp
float Get_Distance(){
  for(int i=0;i<10;i++)       //Get 10 sample value from analog pin
  { 
    buf[i]=analogRead(analog_pin);
    delay(100);
  }
  for(int i=0;i<9;i++)      //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++) //take the average value of 6 center sample
    avgValue+=buf[i];

    temp_dis = (avgValue*(-0.01874))+52.087;
    final_dist = (temp_dis*(0.0649));
    final_dist= final_dist + 26.8145;
    return final_dist;
  }

WiFiClient wclient;
ThingsBoard tp(wclient);

void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // Connect to network
  while (WiFi.status() != WL_CONNECTED) {
    // Wait for connection
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Starting...");
  delay(1000);
  Serial.println("Signal Sent To Arduino");
  setup_wifi();             // Connect to network
  tp.connect(THINGSBOARD_SERVER, TOKEN);
}

void loop() {
if (!tp.connected()) {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
   if (!tp.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }
  
my_distance = Get_Distance();
if (my_distance <= 10){soil_Cracks = "No Cracks";}
else if (my_distance >= 10){soil_Cracks = "Has Cracks";}
sensorValue = analogRead(sensorPin); 
moisture = map(sensorValue,4095,0,0,100);
 if (moisture < 15)    { soil_status = "Very Dry";}
 else if(moisture < 20){ soil_status = "Dry";}
 else if(moisture < 25){ soil_status = "Moderate";}
 else if(moisture < 30){ soil_status = "Wet";} 
 else if(moisture > 30){ soil_status = "Very Wet";} 

  
  Serial.println("Sending data..."); 
  tp.sendTelemetryFloat("Distance", my_distance);
  tp.sendTelemetryFloat("Soil Mosture", moisture);  
  tp.sendTelemetryString("Soil Moisture status", soil_status);
  tp.sendTelemetryString("Soil Cracks status", soil_Cracks);
  tp.loop();

// printing data section
  Serial.print("Distance = ");
  Serial.print(my_distance);
  Serial.print(" CM");
  Serial.print("  ======> ");
  Serial.print(soil_Cracks);
  Serial.print("\t");
  Serial.print("Soil Mosture = ");
  Serial.print(moisture);
  Serial.print(" %");
  Serial.print("  ======> ");
  Serial.println(soil_status);
  delay(2000);
}