//#include "Timer.h"
//need time 
#include "Time.h"
#include "global_values.h"
#include "ir_func.h"
#include "motor_func.h"


//sets up all the new functions
void setup() {
  //interrups set up for turns 
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_A), left_encoder_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_B), left_encoder_event, CHANGE);

  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_A), right_encoder_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_B), right_encoder_event, CHANGE);

  Serial.begin(9600);

  


  //if need to check ir readings from serial monitor
  //Serial.begin(9600);

  //sensor pins
  Serial.begin(9600);
  pinMode(sensor_left, INPUT);
  pinMode(sensor_middle, INPUT);
  pinMode(sensor_right, INPUT);

  pinMode(sensor_left_power, OUTPUT);
  pinMode(sensor_middle_power, OUTPUT);
  pinMode(sensor_right_power, OUTPUT);
  digitalWrite(sensor_left_power, HIGH);

  digitalWrite(sensor_middle_power, HIGH);

  digitalWrite(sensor_right_power, HIGH);

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



  calibrate_pid();

  wait_until_start_hand();

  readIR_map();

  prev_sensorReading_left = sensorReading_left;
  prev_sensorReading_middle = sensorReading_middle;
}














void loop() {
//main sequence 
  readIR_map();
  go_one_cell();
  halt_until(400);
  readIR_map();
  random_move();
  error_catch();



}









