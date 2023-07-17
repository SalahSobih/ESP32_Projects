#define signal_pin_for_arduino 4

void setup() {
  Serial.begin(115200);
  pinMode(signal_pin_for_arduino,OUTPUT);
  digitalWrite(signal_pin_for_arduino,HIGH);

}

void loop() {
  delay(10000);
digitalWrite(signal_pin_for_arduino,LOW);
Serial.println("segnal sent");
}
