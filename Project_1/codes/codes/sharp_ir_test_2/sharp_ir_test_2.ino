#define analog_pin 34    // analog pin

unsigned int avgValue;  
float temp_dis,final_dist;
int my_distance;

int buf[10],temp;

float Get_Distance(){
  for(int i=0;i<10;i++)       //Get 10 sample value from analog pin
  { 
    buf[i]=analogRead(analog_pin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
    temp_dis = (avgValue*(-0.01874))+52.087;
    final_dist = (temp_dis*(0.0649));
    final_dist= final_dist + 26.8145;
    return final_dist;
  }

void setup() {
  Serial.begin(115200);  

}

void loop() {
my_distance = Get_Distance();
Serial.print("distance is: ");
Serial.print(my_distance);
Serial.println(" cm");
delay(1000);
}
