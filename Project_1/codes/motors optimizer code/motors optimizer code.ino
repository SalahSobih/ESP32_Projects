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
int motion_control_flag;
int counter_Y_axis;
int select_motor1_motion_type;


// flag for printing once 
bool ptint_one_flag;

void Motor_Motion(String Motor_num,String Motion_type){
if (Motor_num == "Motor_1"){
  if(Motion_type == "Go"){
    digitalWrite(L_motor_1,LOW);
    digitalWrite(R_motor_1,HIGH);
  }
  else if(Motion_type == "Back"){
    digitalWrite(L_motor_1,HIGH);
    digitalWrite(R_motor_1,LOW);
  }
  else if(Motion_type == "Stop"){
    digitalWrite(L_motor_1,LOW);
    digitalWrite(R_motor_1,LOW);
  }
}
else if (Motor_num == "Motor_2"){
  if(Motion_type == "Go"){
    digitalWrite(L_motor_2,LOW);
    digitalWrite(R_motor_2,HIGH);
  }
  else if(Motion_type == "Back"){
    digitalWrite(L_motor_2,HIGH);
    digitalWrite(R_motor_2,LOW);
  }
  else if(Motion_type == "Stop"){
    digitalWrite(L_motor_2,LOW);
    digitalWrite(R_motor_2,LOW);
  } 
}
}

void setup() {
Serial.begin(9600);
pinMode(L_motor_1,OUTPUT);
pinMode(R_motor_1,OUTPUT);
pinMode(L_motor_2,OUTPUT);
pinMode(R_motor_2,OUTPUT);

pinMode(arduino_signal,OUTPUT);

pinMode(zero_X_axis_pins,INPUT_PULLUP);
pinMode(zero_Y_axis_pins,INPUT_PULLUP);

pinMode(control_motor_1,INPUT_PULLUP);
pinMode(control_motor_2,INPUT_PULLUP);

pinMode(esp32_pin,INPUT_PULLUP);

Zero_axis_flag1 = 1;
Zero_axis_flag2 = 1;
print_flag = 1;
motion_control_flag=0;
counter_Y_axis = 0;
Serial.println("Waiting for Signal from esp32");
}

void loop() {
if (digitalRead(esp32_pin)==LOW){
  if(print_flag==1){
      Serial.println("esp32 signal came");
      delay(1000);
      Serial.println("Getting Zero axis.......Please Wait.......");
      print_flag=0;
      }
  if(Zero_axis_flag1==1){
      if (digitalRead(zero_X_axis_pins)==1){
        Motor_Motion("Motor_1","Back");
      }
      else {
        Motor_Motion("Motor_1","Stop");
        Serial.println("success Zero X Axis");
        Zero_axis_flag1 = 0;
        }
        }
  if (Zero_axis_flag2==1){ 
      if (digitalRead(zero_Y_axis_pins)==1){
        Motor_Motion("Motor_2","Back");
      }       
      else {
        Motor_Motion("Motor_2","Stop");    
        Serial.println("success Zero Y Axis");
        Zero_axis_flag2 = 0;
        }
        }
  if ((Zero_axis_flag1 == 0) && (Zero_axis_flag2 == 0) && (motion_control_flag == 0)){
       Serial.println("This is Zero axis");
       delay(1000);
       for (int x=5 ; x>=1 ; x--){
         Serial.print("motion will start after ");
         Serial.print(x);
         Serial.println(" second");
         delay(1000);
       }
        digitalWrite(arduino_signal,LOW);
        motion_control_flag = 1;
        select_motor1_motion_type = 1;
        ptint_one_flag = true;
  }
 if(motion_control_flag == 1){
  if(select_motor1_motion_type == 1){
       if(digitalRead(control_motor_1) == 1){
          Motor_Motion("Motor_1","Go");
          if (ptint_one_flag == true){
          Serial.println("Going To Final Edge In X Axis");
          ptint_one_flag = false;}}
       else{
         ptint_one_flag = true;
          Motor_Motion("Motor_1","Stop");
          Serial.println("Reatched To Final Edge In X Axis");
          motion_control_flag = 2;}
      }
     else if(select_motor1_motion_type == 2) {
    if(digitalRead(zero_X_axis_pins)==1){
          Motor_Motion("Motor_1","Back");
          if (ptint_one_flag == true){
          Serial.println("moving To start Edge In Y Axis");
          ptint_one_flag = false;}}
       else{ 
          ptint_one_flag = true;  
          Motor_Motion("Motor_1","Stop");
          Serial.println("Reached to Start edge in X axis");
          if(digitalRead(control_motor_2)==0){
             Motor_Motion("Motor_2","Go");}
          else{motion_control_flag = 2;}
        }}}

  else if(motion_control_flag == 2){
       if(digitalRead(control_motor_2)==1){
          Motor_Motion("Motor_2","Go");
          if (ptint_one_flag == true){
          Serial.println("Y axis Motor moving");
          ptint_one_flag = false;}}
       else{
          ptint_one_flag = true;  
          counter_Y_axis +=1;
          Motor_Motion("Motor_2","Stop");
          Serial.print("Y axis arm reach to section ");
          Serial.println(counter_Y_axis);
          if(zero_X_axis_pins == 0){
            select_motor1_motion_type == 1;
          }
          else{select_motor1_motion_type == 2;}
          motion_control_flag = 1;}
      }        
  }
  delay(500);
  }