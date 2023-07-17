#define send_signal_to_esp_pin 13

void setup(){
  Serial.begin(9600);
pinMode(send_signal_to_esp_pin,OUTPUT);
digitalWrite(send_signal_to_esp_pin,HIGH);
}

void loop() {
digitalWrite(send_signal_to_esp_pin,LOW);
Serial.println("segnal sent");
  delay(10000);
digitalWrite(send_signal_to_esp_pin,HIGH);
Serial.println("No segnal");
  delay(10000);
}