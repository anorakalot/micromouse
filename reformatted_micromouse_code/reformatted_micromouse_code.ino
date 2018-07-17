//#include "Timer.h"
#include "Time.h"
#include "global_values.h"
#include "ir_func.h"
#include "motor_func.h"
//FRONT_PROG
//DO NOW

//ACTUALLY DO
//ADD 1 ONE WALL PID FROM MARK 2 // NOT DONE
//ADD LED ON OFF CATCH ERROR FROM MARK 2 // DONE



//FIRST PRIORITIES
//MAKE SO IT DOESNT HAVE ONE WALL OR NO WALL AND IT JUST GOES STRAIGHT with the last good pid motor value OR DO ONE WALL PID// still working on//MAKE IT DO ONE WALL PID
//MAKE ERROR CATCH CATCH MORE ERRORS AND NOT DO RANDOM TURNS( MAYBE do TIMER LIBRARY) //FIRST ROUGH DONE//ADDED IF MOTOR NOT TURNING
//MAKE PID WITH I AND D //did with d may add i //i might be good now watch for overflow // PRETTY SURE THIS IS DONE

//SECONDARY PRIORITIES
//MAKE PID ON AND OFF //LEDS on and off to detect error //LATER
//STATE MACHINES
//ENUM

//general notes
//LET IT HIT THE WALL TO STRAIGHTEN OUT
//CALIBRATION PID DOESNT HELP

void setup() {
  //catch_init();
  //t.every(12000, catch_tick);

  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_A), left_encoder_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_B), left_encoder_event, CHANGE);

  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_A), right_encoder_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_B), right_encoder_event, CHANGE);

  Serial.begin(9600);
  //calibrate


  //irled
  //Serial.begin(9600);

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

  //motors
  // pinMode(turn_on_en_input,INPUT);
  pinMode(turn_on_en_1, OUTPUT);
  pinMode(turn_on_en_2, OUTPUT);

  pinMode(motor_1_logic_1, OUTPUT);

  pinMode(motor_1_logic_2, OUTPUT);

  pinMode(motor_2_logic_1, OUTPUT);

  pinMode(motor_2_logic_2, OUTPUT);

  digitalWrite(turn_on_en_1, LOW);
  digitalWrite(turn_on_en_2, LOW);



  //sensorReading_middle = 0;
  //readIR();

  calibrate_pid();

  wait_until_start_hand();

  readIR_map();

  prev_sensorReading_left = sensorReading_left;
  prev_sensorReading_middle = sensorReading_middle;

}






















void loop() {
  //
  //  readIR();
  //  delay(1000);
  //        readIR_map();
  //        delay(1000);
  //  // pid_control();


  //t.update();
  //delay(2000);
  //forward(base_speed,base_speed - 20);
  ///
  //  readIR_map();
  //  delay(1000);
  // go_one_cell();
  //  halt_until(halt_delay);//760

  //
  //halt_until(500);
  //go_one_cell();
  //halt_until(500);

  //  readIR_map();
  //
  //  random_move();
  //
  //  readIR_map();
  //  error_catch();


  //
  //  readIR();
  //  delay(1000);

  //    motor_left = base_speed;
  //    motor_right = base_speed - 10;
  //    forward(motor_left,motor_right);
  //

  //
  //
  readIR_map();
  go_one_cell();
  halt_until(400);
  readIR_map();
  random_move();
  error_catch();


  //

  //  readIR();
  //  delay(1000);

  //readIR_map();
  ////  //  //delay(1000);
  //  halt_until(700);
  //  left_turn_until();
  //  halt_until(700);

  //  halt_until(700);
  //  right_turn_until();
  //  halt_until(700);

  //  halt_until(700);
  //  left_with_wall();
  //  halt_until(700);
  //
  //  halt_until(700);
  //  right_with_wall();
  //  halt_until(700);

}









