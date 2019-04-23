/*
 * TO DO LIST
 * MAKE THIS IN STATE MACHINES
 * DO PID OFF ONE WALL
 * DO PID OFF ENCODERS
 * DO GYRO ANGLES
 * test motor functions work properly
 */


#include <Wire.h>
#include <L3G.h>
#include "global_values.h"
#include "gyro_func.h"
//#include "Timer.h"
//need time
#include "Time.h"
#include "ir_func.h"
#include "motor_func.h"






//sets up all the new functions
void setup() {
  Serial.begin(9600);
  
  ///*
  //interrups set up for turns 
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_A), left_encoder_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_B), left_encoder_event, CHANGE);

  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_A), right_encoder_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_B), right_encoder_event, CHANGE);

  


  //if need to check ir readings from serial monitor
  //Serial.begin(9600);

  //sensor pins
  
  pinMode(sensor_left, INPUT);
  pinMode(sensor_middle, INPUT);
  pinMode(sensor_right, INPUT);  
  pinMode(sensor_45_left, INPUT);
  pinMode(sensor_45_right, INPUT);


  pinMode(sensor_left_power, OUTPUT);
  pinMode(sensor_middle_power, OUTPUT);
  pinMode(sensor_right_power, OUTPUT);
  pinMode(sensor_45_left_power,OUTPUT);
  pinMode(sensor_45_right_power,OUTPUT);
  
  digitalWrite(sensor_left_power, HIGH);

  digitalWrite(sensor_middle_power, HIGH);

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



//gyro setup
//REMEMBER TO SETUP gyro 
//PROBABLY THE REASON WHY THE gyro ISN'T WORKING
//setup_gyro();

///*
//  calibrate_pid();

  wait_until_start_hand();

  //readIR_map();

  //not needed 
  //prev_sensorReading_left = sensorReading_left;
  //prev_sensorReading_middle = sensorReading_middle;
//*/
}
 

//EXAMPLE CODE
//void motor_init(){
//  motor_state = MOTOR_START;  
//}
//
//void motor_task(){
//  motor_init();
//  for(;;){
//    motor_tick();
//    vTaskDelay(10); 
//  }
//}
//void StartSecPulse_2(unsigned portBASE_TYPE Priority)
//{
//  xTaskCreate(motor_task,(signed portCHAR *)"motor_task",configMINIMAL_STACK_SIZE,NULL,Priority,NULL);
//}
//
//StartSecPulse_2();
//vTaskStartScheduler();

void loop() {
//main sequence 
 
 /* 
  readIR_map();
  go_one_cell();
  halt_until(400);
  readIR_map();
  random_move();
  error_catch();
*/ 

//forward();
//left_tunrn();
//right_turn();
//reverse();
//readIR();
//delay(1000);
//Serial.println("hello");

//read_angle();

}









