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
#define arduino_signal 13

int Zero_axis_flag1;
int Zero_axis_flag2;

int test_control;

int print_flag;

// motion falgs
int motion_control_flag=0;
int counter_Y_axis=0;

void setup() {
Serial.begin(9600);
pinMode(L_motor_1,OUTPUT);
pinMode(R_motor_1,OUTPUT);
pinMode(L_motor_2,OUTPUT);
pinMode(R_motor_2,OUTPUT);

pinMode(arduino_signal,OUTPUT);

pinMode(zero_X_axis_pins,INPUT_PULLUP);
pinMode(zero_Y_axis_pins,INPUT_PULLUP);

pinMode(control_motor_1,INPUT);
pinMode(control_motor_2,INPUT);

pinMode(esp32_pin,INPUT_PULLUP);
Zero_axis_flag1 = 1;
Zero_axis_flag2 = 1;
print_flag = 1;
Serial.println("Waiting for Signal from esp32");
}

void loop() {
if (digitalRead(esp32_pin)==LOW){
  if(print_flag==1){
      Serial.println("esp32 signal came");
      print_flag=0;
      }
  if(Zero_axis_flag1 == 1){
      if (digitalRead(zero_X_axis_pins)==1){
        digitalWrite(L_motor_1,HIGH);
        digitalWrite(R_motor_1,LOW);
      }
      else {
        digitalWrite(L_motor_1,LOW);
        digitalWrite(R_motor_1,LOW); 
        Serial.println("success Zero X Axis");
        Zero_axis_flag1 = 0;
        }
        }
  if (Zero_axis_flag2 == 1){ 
      if (digitalRead(zero_Y_axis_pins)==1){
        digitalWrite(L_motor_2,HIGH);
        digitalWrite(R_motor_2,LOW);
      }       
      else {
        digitalWrite(L_motor_2,LOW);
        digitalWrite(R_motor_2,LOW);      
        Serial.println("success Zero Y Axis");
        Zero_axis_flag2 = 0;
        }
        }
  if ((Zero_axis_flag1 == 0) && (Zero_axis_flag2 == 0)){
        digitalWrite(arduino_signal,LOW);
        motion_control_flag = 1;      
  }
  if(motion_control_flag == 1){
       if(digitalRead(control_motor_1)==0){
          digitalWrite(L_motor_1,LOW);
          digitalWrite(R_motor_1,HIGH);}
        else{
          digitalWrite(L_motor_1,LOW);
          digitalWrite(R_motor_1,LOW);
          motion_control_flag = 2;}
      }
      else if(motion_control_flag == 2){
        if(digitalRead(control_motor_2)==0){
          counter_Y_axis +=1;
          digitalWrite(L_motor_2,LOW);
          digitalWrite(R_motor_2,HIGH);
          Serial.print("counter_Y_axis = ");
          Serial.println(counter_Y_axis);}
        else{
          digitalWrite(L_motor_1,LOW);
          digitalWrite(R_motor_1,LOW);
          motion_control_flag = 3;}
      }
      else if(motion_control_flag==3){
        if(digitalRead(zero_X_axis_pins)==1){
          digitalWrite(L_motor_1,HIGH);
          digitalWrite(R_motor_1,LOW);}
        else{
          digitalWrite(L_motor_1,LOW);
          digitalWrite(R_motor_1,LOW);
            if(digitalRead(control_motor_2)==1){
            digitalWrite(L_motor_2,LOW);
            digitalWrite(R_motor_2,HIGH);}
          else{motion_control_flag = 2;}
        }
      }        
  }
  delay(500);
  }
  