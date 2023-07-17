#include <WiFi.h>
#include "ThingsBoard.h"

// wifi 
const char* ssid = "3AMO0ORY";
const char* password = "OMar@SaLaH&123456#654321$19102019@";

#define TOKEN               "LhaHXVLsPDSNlKhkUUn2"
#define THINGSBOARD_SERVER  "demo.thingsboard.io"

#define DHTPIN 15     
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);
float Temp , Humid;  
String data ;  

WiFiClient wclient;
ThingsBoard tp(wclient);

/*void setup_wifi() {
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
}*/

void setup() {
  Serial.begin(115200);
  delay(100);
  dht.begin();

    WiFi.mode(WIFI_STA);   

  if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
 // setup_wifi(); // Connect to network
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
 Serial.println("Sending data..."); 
 Temp = dht.readTemperature();
 Humid = dht.readHumidity();
 //data = "ُENG : SaLaH";

// sending data to thingsboard
  tp.sendTelemetryFloat("Temperature", Temp);
  tp.sendTelemetryFloat("Humidity", Humid);
  tp.loop();
  Serial.print("Temperature => ");
  Serial.print(Temp);
  Serial.print("\t");
  Serial.print("Humidiry ====> ");
  Serial.println(Humid);
  delay(3000);
}
