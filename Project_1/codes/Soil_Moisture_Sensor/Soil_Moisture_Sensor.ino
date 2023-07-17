#define sensorPin 15 
#define check_pin 13
int sensorValue;  
char* soil_status; 

void setup() {
 Serial.begin(115200);
 pinMode(check_pin, OUTPUT);
}

void loop() {
 sensorValue = analogRead(sensorPin); 
 Serial.println("Analog Value : ");
 Serial.println(sensorValue);
 
 if (sensorValue<limit) {
 digitalWrite(check_pin, HIGH);
 }
 else {
 digitalWrite(check_pin, LOW); 
 }
 
 delay(1000); 
}
