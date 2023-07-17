#define esp32_pin 12

void setup(){
  Serial.begin(9600);
pinMode(esp32_pin,INPUT_PULLUP);}

void loop(){
if (digitalRead(esp32_pin) == LOW){
  Serial.println("esp32 signal came");}
else {   Serial.println("no signal came"); }
delay(1000);
}