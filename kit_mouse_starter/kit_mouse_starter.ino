#include "global_values.h"






//sets up all the functions and variables
void setup(){
  Serial.begin(9600);
  

  


  //if need to check ir readings from serial monitor
  //Serial.begin(9600);

  //sensor pins
  
  pinMode(sensor_left, INPUT);
  pinMode(sensor_middle, INPUT);
  //put in sensor Middle_right
  pinMode(sensor_right, INPUT);  
  pinMode(sensor_45_left, INPUT);
  pinMode(sensor_45_right, INPUT);


  pinMode(sensor_left_power, OUTPUT);
  pinMode(sensor_middle_power, OUTPUT);
  //pinMode(sensor_middle_right
  pinMode(sensor_right_power, OUTPUT);
  pinMode(sensor_45_left_power,OUTPUT);
  pinMode(sensor_45_right_power,OUTPUT);
  
  digitalWrite(sensor_left_power, HIGH);

  digitalWrite(sensor_middle_power, HIGH);
  //sensorMiddle right
  digitalWrite(sensor_right_power, HIGH);

  digitalWrite(sensor_45_left_power,HIGH);

  digitalWrite(sensor_45_right_power,HIGH);

  //motor pins
  // pinMode(turn_on_en_input,INPUT);
  pinMode(turn_on_en_1, OUTPUT);
  pinMode(turn_on_en_2, OUTPUT);

  pinMode(motor_1_logic_1, OUTPUT);

  pinMode(motor_1_logic_2, OUTPUT);

  pinMode(motor_2_logic_1, OUTPUT);

  pinMode(motor_2_logic_2, OUTPUT);

  digitalWrite(turn_on_en_1, LOW);
  digitalWrite(turn_on_en_2, LOW);



}
 



void loop(){
  //PUT CODE HERE
}




