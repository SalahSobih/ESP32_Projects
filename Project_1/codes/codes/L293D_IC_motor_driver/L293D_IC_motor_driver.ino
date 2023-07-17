// motors pins 
#define L_motor_1 4
#define R_motor_1 5
#define L_motor_2 6
#define R_motor_2 7

// Zero axis pins
#define zero_X_axis_pins 8
#define zero_Y_axis_pins 9

// control pins
#define control_motor_1 10
#define control_motor_2 11

// esp32 pin
#define esp32_pin 12

int Zero_axis_flag1;
int Zero_axis_flag2;

void setup() {
Serial.begin(9600);
pinMode(L_motor_1,OUTPUT);
pinMode(R_motor_1,OUTPUT);
pinMode(L_motor_2,OUTPUT);
pinMode(R_motor_2,OUTPUT);

pinMode(zero_X_axis_pins,INPUT_PULLUP);
pinMode(zero_Y_axis_pins,INPUT_PULLUP);

pinMode(control_motor_1,INPUT);
pinMode(control_motor_2,INPUT);

pinMode(esp32_pin,INPUT);
Zero_axis_flag1 = 1;
Zero_axis_flag2 = 1;
}

void loop() {
  if (digitalRead(esp32_pin)==1){
  while((Zero_axis_flag1 == 1) || (Zero_axis_flag2 == 1)){ 
 if (digitalRead(zero_X_axis_pins)==1){
  digitalWrite(L_motor_1,HIGH);
  digitalWrite(R_motor_1,LOW);
  } 
  else {
  digitalWrite(L_motor_1,LOW);
  digitalWrite(R_motor_1,LOW); 
  Zero_axis_flag1 = 0;
   }
 if (digitalRead(zero_Y_axis_pins)==1){
  digitalWrite(L_motor_2,HIGH);
  digitalWrite(R_motor_2,LOW);
  } 
  else {
  digitalWrite(L_motor_2,LOW);
  digitalWrite(R_motor_2,LOW); 
  Zero_axis_flag2 = 0;
   }
  }
  }
  }