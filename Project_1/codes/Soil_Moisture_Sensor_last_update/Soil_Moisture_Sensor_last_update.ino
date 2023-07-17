#define sensorPin 35 

float sensorValue,moisture; 
char* soil_status; 

void setup() {
 Serial.begin(115200);
}

void loop() {
 sensorValue = analogRead(sensorPin); 
 moisture = map(sensorValue,4095,0,0,100);

 if (moisture < 15) {
  soil_status = "Very Dry";
  Serial.print("moisture = ");
  Serial.print(moisture);
  Serial.print(" %");
  Serial.print("  ======> ");
  Serial.println(soil_status);}
 else if(moisture < 20){
  soil_status = "Dry";
  Serial.print("moisture = ");
  Serial.print(moisture);
  Serial.print(" %");
  Serial.print("  ======> ");
  Serial.println(soil_status);}
 else if(moisture < 25){
  soil_status = "Moderate";
  Serial.print("moisture = ");
  Serial.print(moisture);
  Serial.print(" %");
  Serial.print("  ======> ");
  Serial.println(soil_status);}
else if(moisture < 30){
  soil_status = "Wet";
  Serial.print("moisture = ");
  Serial.print(moisture);
  Serial.print(" %");
  Serial.print("  ======> ");
  Serial.println(soil_status);}
  else if(moisture > 30){
  soil_status = "Very Wet";
  Serial.print("moisture = ");
  Serial.print(moisture);
  Serial.print(" %");
  Serial.print("  ======> ");
  Serial.println(soil_status);}  
 delay(1000); 
}
