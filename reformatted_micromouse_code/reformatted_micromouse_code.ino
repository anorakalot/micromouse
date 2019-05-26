
//#include <basic_io_avr.h>
//#include <FreeRTOS_AVR.h>

//#include <basic_io_arm.h>
//#include <FreeRTOS_ARM.h>
/*
 * TO DO UCLA COMP
 * DO ONE WALL PID
 * DO SELF CORRECTION WITH FRONT WALL
 * CALIBRATE ALL THE VALUES
 * DO NO WALL PID
 */


/*
 * TO DO LIST
 * MAKE THIS IN STATE MACHINES // DO ONLY MOTOR /FLOODFILL IN STATE MACHINES AND GYRO
 * DO PID OFF ONE WALL // use different middle ir's
 * DO PID OFF ENCODERS/GYRO for no walls
 * PORBABLY MAKE MOTOR_LEFT AND MOTOR_RIGHT SPEED VARIABLES
 * THEN DO SPEED + or -  the p i d control variables
 * PROBABLY JUST DO BASE_SPEED + or - for MOTOR_LEFT AND MOTOR_RIGHT
 * DO SELF CORRECTION WHENEVER IT REACHES A FRONT WALL 
 * DO SELF CORRECTION WITH SIDE WALLS AS WELL
 * SO GYRO WITH ACCELEROMETER SENSOR FUSION
 * GET FLOODFILL WORKING
 * TRY TO GET FREERTOS WORKING 
 */
 /*
  * DONE LIST
  *DO GYRO ANGLES and CALL DURING TURN_UNTIL FUNCTIONS DONE 
  *GO BACK TO LOOP DONE
  */
//#include "Timer.h"
////#include <NewPing.h>
//#include "Time.h"

//floodfill libraries
#include <stack>

#include <cmath>
 

#include <Wire.h>
#include <LSM6.h>

//#include <Wire.h>
//#include <L3G.h>
#include "global_values.h"
#include "gyro_func.h"
//#include "Timer.h"
//need time
//#include "Time.h"
#include "ir_func.h"
#include "motor_func.h"






//sets up all the functions and variables
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


  gyro_init(); 
  gyro_tick();//sets up gyro read function
  motor_init();//sets up motor tick state  
  wait_until_start_hand();
  
  

  //ir_start_func(); // DONT USE THIS THE ERRORS IN READ IR SEEM BETTER

//gyro setup
//REMEMBER TO SETUP gyro 
//PROBABLY THE REASON WHY THE gyro ISN'T WORKING
//setup_gyro();






}
 



void loop() {
//main sequence 
//  readIR();
//  
//  motor_tick();//does go_one_cell
//  
//  readIR();
////possible calibration function here
//  motor_tick(); // does random_move
//  readIR();

//  error_catch();

//ALL BELOW IS JUST FOR TESTING BEFORE COMPETITION

//testIR();//tests single led (this is before soldering
//Serial.println("HELLO");
//forward(base_speed,base_speed);
go_one_cell();
//
halt_until(halt_delay);
//delay(1000);
//

//gyro_testing
//gyro_tick();

//forward(0,255);
//
//  readIR();
//  delay(1000);
//halt_until(1000);
//print_encoder_count();
//left_turn();
////gyro_tick();
//
//
//halt_until(halt_delay);
//left_turn_until(); //
//right_turn_until(); //  
//reverse_turn_until(); // 

//halt_until(halt_delay);
//delay(2000);

//reverse(200,200);
//halt_until(halt_delay);
//delay(2000);



//right_turn();
//reverse();
//readIR();
//delay(10);
//Serial.println("hello");
//delay(1000);
//read_angle();
//t.update();
//delay(1000);
//readIR();
//Serial.println("HELLOOOO");
//return;
}



//EXAMPLE CODE FOR FREERTOS IF THAT EVER STARTS TO WORK
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


