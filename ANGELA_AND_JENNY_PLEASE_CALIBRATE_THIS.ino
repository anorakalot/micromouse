//#include "Timer.h"
#include "Time.h"

//FRONT_PROG
//DO NOW

//ACTUALLY DO
//ADD 1 ONE WALL PID FROM MARK 2
//ADD LED ON OFF CATCH ERROR FROM MARK 2 // I DONT THINK IT WORKS



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
int halt_delay = 300;//350,300


unsigned long prev_encoder_tick;
unsigned long curr_timer;
bool error_check;
unsigned long prev_timer = 0;
const long error_check_interval = 8000;//12000


bool first_check = true;

//GLOBAL for pid
int permReading_left;
int permReading_middle;
int permReading_right;
int base_speed = 150; // 200,150,125,150
double kp = 0.50;//0.50,0.25,0.30,0.50,0.60
double kd = 0.40;//0.30,0.50,0.30,0.40
double ki = 0.0001;
double error;
double prev_error;
double d_control;

unsigned long error_buildup;
double i_control;
double reset_error = 0;
double motor_left = 125;
double motor_right = 125;

int left_ir_low_bound = 995;
int left_ir_high_bound = 1009;

//Motor
int motor_1_logic_1 = 3;
int motor_1_logic_2 = 4;

int motor_2_logic_1 = 5;
int motor_2_logic_2 = 10;

int turn_on_en_1 = 22;
int turn_on_en_2 = 23;


//encoder
int RH_ENCODER_A = 20;
int RH_ENCODER_B = 21;

int LH_ENCODER_A = 0;
int LH_ENCODER_B = 1;

unsigned long left_count = 0;
unsigned long right_count = 0;



//IRLED
int left_offset = 20; // last value was 15 , 5 , 30, 10

//LEFT
int sensor_left = A2;
int sensorReading_left;
int sensor_left_power = 2;


//MIDDLE
int sensor_middle = A4 ;
int sensorReading_middle;
int sensor_middle_power = 7;


//RIGHT
int sensor_right = A1;
int sensorReading_right;
int sensor_right_power = 12;

//prev led values
int prev_sensorReading_right;
int prev_sensorReading_middle;
int prev_sensorReading_left;

int reading_for_no_left;
int reading_for_no_right;

int error_left;
int error_middle;
int error_right;


//int val;


//error catching
//enum catch_states {INIT_CATCH,ON_1,OFF_1} catch_states;

//void catch_init(){
//  catch_states = INIT_CATCH;
//}
//Timer t;

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
  prev_sensorReading_right = sensorReading_right;

}
void catch_tick() {
  if (prev_sensorReading_left == sensorReading_left && prev_sensorReading_middle == sensorReading_middle && prev_sensorReading_right == sensorReading_right) {
    int rand_num = random(millis()) % 2;
    if (rand_num == 1) {
      halt_until(700);
      reverse_until();
      halt_until(700);
      left_turn_until();
      halt_until(700);
    }
    else {
      halt_until(700);
      reverse_until();
      halt_until(700);
      right_turn_until();
      halt_until(700);
    }
  }

}


void wait_until_start_hand() {

  while (first_check) {
    //readIR();
    readIR_map();
    //delay(500);

    if (hasfrontwall()) {
      first_check = false;
      delay(500);
      prev_sensorReading_left = sensorReading_left;
      prev_sensorReading_middle = sensorReading_middle;
      prev_sensorReading_right = sensorReading_right;
      prev_encoder_tick = left_count;
      prev_timer = millis();
    }
  }

}

//encoder and turns
void left_encoder_event() {
  left_count ++;
}


// encoder event for the interrupt call
void right_encoder_event() {
  right_count ++;
}



void print_encoder_count() {

  Serial.print("left_count");
  Serial.println(left_count);
  Serial.print("right_count");
  Serial.println(right_count);
}


void forward_until(int left_speed, int right_speed, int stop_time) {

  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
    digitalWrite(turn_on_en_1, HIGH);
    digitalWrite(turn_on_en_2, HIGH);

    analogWrite(motor_1_logic_2, left_speed);
    digitalWrite(motor_1_logic_1, LOW);
    analogWrite(motor_2_logic_2, right_speed);
    digitalWrite(motor_2_logic_1, LOW);
  }
}
void left_turn_until() {
  unsigned long curr = left_count;//382,380,375,378,380,383,390,380,382,365
  while ( left_count - curr < 340  ) { //380 330 ,280,290,300,310,320,330,340,350,360,380,365,360
    left_turn();                  //350,360,380,390
  }
}

//use left_count
void right_turn_until() {
  unsigned long curr = left_count;//335
  while ( left_count - curr < 330 ) { //320,340, 370,300,290,280,270,260,280,300,325,330
    right_turn();               //325,335
  }
}


void reverse_until() {
  unsigned long curr_l = left_count;
  //use left_count instead of right_count
  while ( left_count - curr_l < 100) { //800,830, 860,870,790,800,810,840,860,870
    reverse();
  }
}


void reverse_turn_until() {
  unsigned long curr_l = left_count;
  //use left_count instead of right_count
  unsigned long curr_r = left_count;
  //
  if (sensorReading_left < sensorReading_right) {//880
    while ( left_count - curr_l < 930 ) { //800,830, 860,870,790,800,810,840,860,870
      left_turn();                  //870,910u
    }

  }

  else { //use left_count instead of right_count
    while ( left_count - curr_r < 800) { //800,830, 860,870,790
      right_turn();
    }

  }

}

void go_one_cell() {
  unsigned long curr = left_count;
  while (left_count - curr < 935) { // 450,600, 800,950,900,960,955,945,950,945,930,925,940
    readIR_map();
    print_encoder_count();
    pid_control();


    forward(motor_left, motor_right);
  }
  ///*
  //    prev_encoder_tick = left_count;
  //    if (hasleftwall() != true || hasrightwall() != true) {
  //      motor_left = base_speed;
  //      motor_right = base_speed - 10;
  //      //forward(motor_left,motor_right);
  //      //continue;
  //    }
  //*/
  /*
    if (abs(sensorReading_left - sensorReading_right) > 300){
      motor_left = base_speed;
      motor_right= base_speed-10;
      forward(motor_left,motor_right);
      continue;
    }
  */
  //pid_control();
}

//maybe delete this
void go_one_cell_no_wall() {
  unsigned long curr = left_count;
  while (left_count - curr < 950) { // 450,600, 800,950,900,960,955,945
    //pid_control();
    //forward(150,150);
    forward(motor_left, motor_right);
  }
}

void halt_until(int stop_time ) {
  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
    halt();
  }
}

//CALIBRATION
void calibrate_pid() {
  /*
    permReading_left = analogRead(sensor_left);
    permReading_middle= analogRead(sensor_middle);
    permReading_right= analogRead(sensor_right);
    //map left and right
    permReading_left = map(permReading_left,993,1009,0,200);
    permR
    eading_right = map(permReading_right,180,820,0,200);
  */
  ///*
  permReading_left = 0;
  permReading_middle = 0;
  permReading_right = 0;
  //*/

  //trying to get readings to be the same

  //permReading_left -= left_offset;

  readIR_map();
  unsigned long left_readings = 0;
  unsigned long right_readings = 0;

  for (int x = 0; x < 100; ++x) {
    left_readings += sensorReading_left;
  }
  for (int x = 0; x < 100; ++x) {
    right_readings += sensorReading_right;
  }

  reading_for_no_left = left_readings / 100;
  reading_for_no_right = right_readings / 100;



}



//CHOICES
bool hasfrontwall() {       //200,360
  if (sensorReading_middle > 408 ) { //300 , 350,370,400,275,330,360,500
    return true;
  }
  return false;
}

bool hasleftwall() {     //220,450,430,450,430,420 ,320                               //350 maybe a bit too high
  if (sensorReading_left > 523 ) { //100 ,500,300,250,275,400,350,310,320,343,410,420,550,500,600,500,420
    return true;
  }
  return false;
}


bool hasrightwall() {     //220,340,330.300,420,320,330
  if (sensorReading_right >367 ) { //350 ,500,300,250,275 ,280,320,344,350
    return true;
  }
  return false;
}

//possibly change so in main loop this only runs if hasfrontwall returns true
void random_move() {
  int random_move;
  readIR_map();
  //has to turn cases

  if (hasleftwall() && hasrightwall() && !hasfrontwall()) {
    //go_one_cell();
    return;
  }
  //if (abs(sensorReading_left - sensorReading_right) < 300){
  //  return;
  //}

  if (hasleftwall() && hasrightwall() && hasfrontwall()) {
    halt_until(halt_delay);
    forward_until(125, 125, 100);
    halt_until(halt_delay);
    reverse_turn_until();
    halt_until(halt_delay);


    //
    return;
  }

  else if (hasleftwall() && !hasrightwall() && hasfrontwall()) {

    halt_until(halt_delay);
    forward_until(125, 125, 100);
    halt_until(halt_delay);
    right_turn_until();
    halt_until(halt_delay);

    return;
  }
  //this isnt running //hopefully it runs now //STILL NOT RUNNING //It WORKS NOW
  else if (hasrightwall()  && !hasleftwall() && hasfrontwall()) { //|| (hasfronwall() &&(hasrightwall - hasleftwall > 200) ){//
    halt_until(halt_delay);
    forward_until(125, 125, 100);
    halt_until(halt_delay);
    left_turn_until();
    halt_until(halt_delay);

    return;
  }

  //random choice cases

  //

  else if (!hasleftwall() && !hasfrontwall() && hasrightwall()) {
    random_move = random(millis()) % 2;
    if (random_move == 1) {
      halt_until(halt_delay);
      left_turn_until();
      halt_until(halt_delay);
      return;
    }
    else {
      //goes straight
      halt_until(halt_delay);
      return;

    }
  }


  else if (hasleftwall() && !hasfrontwall() && !hasrightwall() ) {
    random_move = random(millis()) % 2;
    if (random_move == 1) {
      halt_until(halt_delay);
      right_turn_until();
      halt_until(halt_delay);
      return;
    }
    else {
      //goes straight
      halt_until(halt_delay);
      return;
    }
  }

  else if (!hasleftwall() && hasfrontwall() && !hasrightwall())  {
    random_move = random(millis()) % 2;
    if (random_move == 1) {
      halt_until(halt_delay);
      forward_until(125, 125, 100);
      halt_until(halt_delay);
      right_turn_until();
      halt_until(halt_delay);

      return;
    }
    else {
      halt_until(halt_delay);
      forward_until(125, 125, 100);
      halt_until(halt_delay);
      left_turn_until();
      halt_until(halt_delay);
      return;
    }
  }

  else if (!hasfrontwall && !hasleftwall && !hasrightwall) {
    random_move = random(millis()) % 3;
    if (random_move == 1) {
      halt_until(halt_delay);
      right_turn_until();
      halt_until(halt_delay);
      return;
    }
    if (random_move == 2) {
      halt_until(halt_delay);
      return;
    }
    else {
      halt_until(halt_delay);
      left_turn_until();
      halt_until(halt_delay);
      return;

    }
  }


  //in case of errors
  else {
    random_move = random(millis()) % 3;
    if (random_move == 1) {
      halt_until(700);
      right_turn_until();
      halt_until(700);
      return;
    }
    else if (random_move == 2) {
      halt_until(700);
      left_turn_until();
      halt_until(700);
      return;

    }
    else {
      return;
    }

    //go_one_cell();
    return;

  }
  return;

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
//
  readIR_map();
  delay(1000);
//  go_one_cell();
//  halt_until(halt_delay);//760

left_turn_until();
halt_until(500);

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
}



//IR
void readIR() {
  //
  //  digitalWrite(sensor_left_power, LOW);
  //  digitalWrite(sensor_middle_power, LOW);
  //  digitalWrite(sensor_right_power, LOW);
  //
  //  error_left = analogRead(sensor_left);
  //  error_middle = analogRead(sensor_middle);
  //  error_right = analogRead(sensor_right);
  //
  //  digitalWrite(sensor_left_power, HIGH);
  //  digitalWrite(sensor_middle_power, HIGH);
  //  digitalWrite(sensor_right_power, HIGH);
  //
  //  Serial.println("ERRORS");
  //  Serial.println(error_left);
  //  Serial.println(error_middle);
  //  Serial.println(error_right);

  sensorReading_left = analogRead(sensor_left);
  sensorReading_middle = analogRead(sensor_middle);
  sensorReading_right = analogRead(sensor_right);

  //  sensorReading_left -= error_left;
  //  sensorReading_middle -= error_middle;
  //  sensorReading_right -= error_right;

  Serial.print("Sensor Reading: ");
  Serial.println(sensorReading_left);
  Serial.println(sensorReading_middle);
  Serial.println(sensorReading_right);
  Serial.println();
}


void readIR_map() {

  //error Reading
  //
//    digitalWrite(sensor_left_power, LOW);
//    digitalWrite(sensor_middle_power, LOW);
//    digitalWrite(sensor_right_power, LOW);
//  
//    error_left = analogRead(sensor_left);
//    error_middle = analogRead(sensor_middle);
//    error_right = analogRead(sensor_right);
//  
//  
//    //PROBABLY NOT USE THIS//error_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 180, 820);
//    //PROBABLY NOT USE THIS//error_left -= left_offset;
//  
//    digitalWrite(sensor_left_power, HIGH);
//  
//    digitalWrite(sensor_middle_power, HIGH);
//  
//    digitalWrite(sensor_right_power, HIGH);
//  



  sensorReading_left = analogRead(sensor_left);
  sensorReading_middle = analogRead(sensor_middle);
  sensorReading_right = analogRead(sensor_right);
  //
//    sensorReading_left -= error_left;
//    sensorReading_middle -= error_middle;
//    sensorReading_right -= error_right;




  //991,992                                                                               //820
  sensorReading_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 352, 860 );
  //sensorReading_left -= left_offset;


  sensorReading_left = abs(sensorReading_left);
  sensorReading_right = abs(sensorReading_right);
  sensorReading_middle = abs(sensorReading_middle);



  Serial.print("Sensor Reading: ");
  Serial.print( "LEFT : ");
  Serial.println(sensorReading_left);
  Serial.print( "MIDDLE : ");
  Serial.println(sensorReading_middle);
  Serial.print( "RIGHT : ");
  Serial.println(sensorReading_right);
  Serial.println();


}



//PID / ERROR_CATCHING

void error_catch() {
  curr_timer = millis();

  if (curr_timer - prev_timer >= error_check_interval) {
    prev_timer = curr_timer;
    // if (error_check == true) {
    if (prev_sensorReading_left == sensorReading_left && prev_sensorReading_middle == sensorReading_middle && prev_sensorReading_right == sensorReading_right) {
      int rand_num = random(millis()) % 2;
      if (rand_num == 1) {
        halt_until(700);
        reverse_until();
        halt_until(700);
        left_turn_until();
        halt_until(700);
      }
      else {
        halt_until(700);
        reverse_until();
        halt_until(700);
        right_turn_until();
        halt_until(700);
      }
    }

    if (  left_count - prev_encoder_tick < 100) {
      int rand_num = random(millis()) % 2;
      if (rand_num == 1) {
        halt_until(700);
        reverse_until();
        halt_until(700);
        left_turn_until();
        halt_until(700);
      }
      else {
        halt_until(700);
        reverse_until();
        halt_until(700);
        right_turn_until();
        halt_until(700);
      }
    }

    prev_sensorReading_left = sensorReading_left;
    prev_sensorReading_middle = sensorReading_middle;
    prev_sensorReading_right = sensorReading_right;
    prev_encoder_tick = left_count;
  }


}
//error_check = false;





void regulateSensorL() {
  /*
    readIR_map();
    if (!hasleftwall || !hasrightwall){
    forward(prev_motor_left,prev_motor_right);
    return;
    }
  */
  //
  //  digitalWrite(sensor_left_power, LOW);
  //  error_left = analogRead(sensor_left);
  //
  //  digitalWrite(sensor_left_power, HIGH);
  //
  sensorReading_left = analogRead(sensor_left);
  //readIR();
  // sensorReading_left -= error_left;

  //readIR_map();
  //readIR();
  //sensorReading_left = map(sensorReading_left,993,1009,0,200);
  //sensorReading_left = map(sensorReading_left,991,1005,0,200);

  sensorReading_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 0, 200);
  //sensorReading_left -= left_offset;

  sensorReading_left = sensorReading_left - permReading_left;
  if (analogRead(sensor_left) - permReading_left < 0) {
    sensorReading_left = ~sensorReading_left + 1;
  }

}

void regulateSensorR() {
  /*
    readIR_map();
    if (!hasleftwall || !hasrightwall){
    forward(prev_motor_left,prev_motor_right);
    return;
    }
  */
  //sensorReading_right = analogRead(sensor_right);
  //readIR();
  //readIR_map();

  //  digitalWrite(sensor_right_power, LOW);
  //  error_right = analogRead(sensor_right);
  //
  //  digitalWrite(sensor_right_power, HIGH);
  //
  sensorReading_right = analogRead(sensor_right);
  //sensorReading_right -= error_right;
  //readIR();


  sensorReading_right = map(sensorReading_right, 180, 820, 0, 200);

  sensorReading_right = sensorReading_right - permReading_right;
  if (analogRead(sensor_right) - permReading_right < 0) {
    sensorReading_right = ~sensorReading_right + 1;
  }
}

void regulateSensorL(int reading) {
  /*
    readIR_map();
    if (!hasleftwall || !hasrightwall){
    forward(prev_motor_left,prev_motor_right);
    return;
    }
  */
  sensorReading_left = map(reading, left_ir_low_bound, left_ir_high_bound, 0, 200);
  sensorReading_left = sensorReading_left - permReading_left;
  if (analogRead(sensor_left) - permReading_left < 0) {
    sensorReading_left = ~sensorReading_left + 1;
  }
}

void regulateSensorR(int reading) {
  /*
    readIR_map();
    if (!hasleftwall || !hasrightwall){
    forward(prev_motor_left,prev_motor_right);
    return;
    }
  */

  sensorReading_right = map(reading, 180, 820, 0, 200);
  sensorReading_right = sensorReading_right - permReading_right;
  if (analogRead(sensor_right) - permReading_right < 0) {
    sensorReading_right = ~sensorReading_right + 1;
  }
}



void pid_control() {
  //if no wall on either side
  //TRY TO FIX IF NO WALL ON EITHER SIDE DO DEFAULT VALUES for motor
  /*
    readIR_map();
    if ((sensorReading_left - sensorReading_right > 200) || (sensorReading_right- sensorReading_left > 200)){
      motor_left = base_speed;
      motor_right= base_speed-10;
      return;
    }
    //end of added
  */
  readIR_map();

  //    if (hasleftwall() != true || hasrightwall() != true) {
  //      if (hasleftwall() != true && hasrightwall() == true) {
  //        regulateSensorL(reading_for_no_left);
  //        regulateSensorR();
  //      }
  //      if (hasleftwall() == true && hasrightwall() != true) {
  //        regulateSensorL();
  //        regulateSensorR(reading_for_no_right);
  //      }
  //      else {
  //        regulateSensorL(reading_for_no_left);
  //        regulateSensorR(reading_for_no_right);
  //      }
  //    }
  //
  //
  //    else {
  //      regulateSensorL();
  //      regulateSensorR();
  //    }
  //



  if (hasleftwall() != true || hasrightwall() != true) {
    motor_left = base_speed;
    motor_right = base_speed - 10;
    //forward(motor_left,motor_right);
    //continue;
    return;
  }
  regulateSensorL();
  regulateSensorR();


  reset_error ++;

  if (reset_error > 1000) {
    reset_error = 0;
    error_buildup = 0;
  }

  //too close left
  if (sensorReading_left > sensorReading_right) {
    //d control
    prev_error = error;
    error = abs(sensorReading_left - sensorReading_right);
    d_control = (error - prev_error) * kd;

    //i control
    //i control
    error_buildup += error;
    i_control = error_buildup * ki;

    //forward(base_speed,base_speed - (( sensorReading_left - sensorReading_right) * kp));
    motor_left = base_speed;
    motor_right = base_speed - (( sensorReading_left - sensorReading_right) * kp + d_control + i_control); //+d_control);
    return;
  }

  //too close right
  if (sensorReading_right > sensorReading_left) {

    //d control
    prev_error = error;
    error = abs(sensorReading_left - sensorReading_right);
    d_control = (error - prev_error) * kd;

    //i control
    error_buildup += error;
    i_control = error_buildup * ki;

    //forward(base_speed - ((sensorReading_right - sensorReading_left) * kp),base_speed);
    motor_left = base_speed - ((sensorReading_right - sensorReading_left) * kp + d_control + i_control); //+ d_control);
    motor_right = base_speed;
    return;
  }
  //( sensorReading_left - sensorReading_right)
  //(sensorReading_right - sensorReading_left)
}


//MOTORS

void reverse() {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, HIGH);
  digitalWrite(motor_1_logic_2, LOW);

  digitalWrite(motor_2_logic_1, HIGH);
  digitalWrite(motor_2_logic_2, LOW);

}


void forward() {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_1_logic_2, HIGH);

  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, HIGH);
}



void halt() {
  digitalWrite(turn_on_en_1, LOW);
  digitalWrite(turn_on_en_2, LOW);

  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_1_logic_2, LOW);
  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, LOW);


}



void reverse_turn() {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, HIGH);
  digitalWrite(motor_1_logic_2, LOW);
  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, HIGH);

}


void left_turn() {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);


  digitalWrite(motor_1_logic_1, HIGH);
  digitalWrite(motor_1_logic_2, LOW);
  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, HIGH);
}


void right_turn() {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);


  digitalWrite(motor_1_logic_2, HIGH);
  digitalWrite(motor_2_logic_1, HIGH);
  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_2_logic_2, LOW);
}


void forward(int left_speed, int right_speed) {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  analogWrite(motor_1_logic_2, left_speed);
  digitalWrite(motor_1_logic_1, LOW);
  analogWrite(motor_2_logic_2, right_speed);
  digitalWrite(motor_2_logic_1, LOW);
}
