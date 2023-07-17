#define recevice_signal_from_arduino_pin 15

void setup() {
  Serial.begin(115200);
  pinMode(recevice_signal_from_arduino_pin,INPUT_PULLUP);
}

void loop() {
  if (digitalRead(recevice_signal_from_arduino_pin) == LOW){
   Serial.println("esp32 signal came");
}
else {Serial.println("Waiting for signal");}
delay(1000);
}