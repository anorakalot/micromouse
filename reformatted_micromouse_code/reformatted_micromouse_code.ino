#include <avr/io.h>
#include <avr/interrupt.h>

#include <StackArray.h>



//floodfill libraries
#include <stack>

#include <cmath>
 

#include <Wire.h>
#include <LSM6.h>

#include "global_values.h"
#include "gyro_func.h"

#include "ir_func.h"
#include "motor_func.h"



// interupt testing
//NEED TO FIND WAY TO SET PCINT to (8,9) (10,11) 
//ONE FROM EACH OF THE INTERUPTS
//Also check if just setting count as volatile and 
//stopping and restarting the intterupts with cli/sei helps already with encoder innacuracy
//ISR (PCINT0_vect){
//  if (motor_state== GO_ONE_CELL){
//  left_count ++;
//    
//  }
//}

//ISR(PCINT1_vect){
//  if (motor_state == GO_ONE_CELL){
//  right_count ++;
//  }
//}



//sets up all the functions and variables
void setup(){

  Serial.begin(9600);
 
  ///*

  //TESTING INTERUPTS
  
  
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
  pinMode(sensor_back, INPUT);
  pinMode(sensor_right, INPUT);  
  pinMode(sensor_45_left, INPUT);
  pinMode(sensor_45_right, INPUT);


  pinMode(sensor_left_power, OUTPUT);
  pinMode(sensor_middle_power, OUTPUT);
  pinMode(sensor_back_power, OUTPUT);
  pinMode(sensor_right_power, OUTPUT);
  pinMode(sensor_45_left_power,OUTPUT);
  pinMode(sensor_45_right_power,OUTPUT);
  
  digitalWrite(sensor_left_power, HIGH);

  digitalWrite(sensor_middle_power, HIGH);
  //sensorMiddle right
  digitalWrite(sensor_right_power, HIGH);

  digitalWrite(sensor_45_left_power,HIGH);

  digitalWrite(sensor_45_right_power,HIGH);
  digitalWrite(sensor_back_power,HIGH);

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

//UNCOMMENT THESE WHEN NEEDING TO RUN MOUSE
  gyro_init(); //sets up gyro
  gyro_tick();//sets up gyro read function
  motor_init();//sets up motor tick state  
  wait_until_start_hand();//waits until hand in front of 
  
  

  //ir_start_func(); // DONT USE THIS THE ERRORS IN READ IR SEEM BETTER

//gyro setup
//REMEMBER TO SETUP gyro 
//PROBABLY THE REASON WHY THE gyro ISN'T WORKING
//setup_gyro();







}
 



void loop(){


//main sequence 
  //readIR();
  motor_tick(); 
  delay(1000);



//testing
  //left_turn_until();
  //go_one_cell();
//  forward(base_speed_l,base_speed_r);//r - 6 still goes left,r- 7 still goes to a side but it goes straighter
//  delay(1000);
//  halt_until(halt_delay);
//  delay(1200);
  //forward();
  //testIR();
   // pid_control();

    // forward(motor_left, motor_right);



//digitalWrite(sensor_back_power,HIGH);
//delay(1000);
//
//digitalWrite(sensor_back_power,LOW);
//delay(1000);
//Serial.println("TESTING_LOOP");
//delay(1000);
//go_one_cell();
//  

  //motor_tick();//does go_one_cell
  //delay(2000);
//  halt_until(halt_delay);
//  readIR();
//  delay(1000);
//possible calibration function here
  //correct_mouse_far();
//  correct_mouse_close();
//  motor_tick(); // does random_move
//
//  random_move();
//  readIR();
//  read_distance();
  //readIR();
//correct_mouse_far();
//correct_mouse_close();
//    pid_control();
//    reverse(motor_left,motor_right);
    //reverse(motor_right,motor_left);
    //forward(motor_left,motor_right);
    //readIR();
    //can_correct_func();

//reverse(100,100);
//reverse(motor_left,motor_right);
//forward_until(255,255,400);
//reverse_until(255,255,400);

//delay(1000);
///reverse_turn_until_l();
//left_turn_until();
//right_turn_until();
//reverse_turn_until_r();
//
//////
//delay(1000);
//go_one_cell();


//gyro_tick();
//readIR()
//delay(1000);

//right_turn();
//left_turn();
//delay(100);
//halt_until(halt_delay);
//reverse_turn();
//delay(100);
//halt_until(halt_delay);
//delay(100);
//go_one_cell();
//forward(base_speed +50,base_speed - 50);
//read_distance();
}





