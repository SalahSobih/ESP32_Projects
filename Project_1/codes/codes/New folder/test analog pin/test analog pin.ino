#define test_Pin 34 

float pin_Value; 

void setup() {
 Serial.begin(115200);
}

void loop() {
 pin_Value = analogRead(test_Pin); 
 
 Serial.print("Analog Value = ");
 Serial.println(pin_Value);
 
 delay(1000); 
}
