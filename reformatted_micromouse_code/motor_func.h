//encoder and turns
//put in if statement so the PID encoder function is more accurate
//and only takes into account encoder ticks when its moving forward 
//having it take into account when turning would mess up the speed calculations
//I dont even use encoders for turning anymore anymore
void left_encoder_event(){
  if (motor_state== GO_ONE_CELL || motor_state == GO_ONE_CELL_REVERSE){
  left_count ++;
  }
//  left_count ++;
}


// encoder event for the interrupt call
//put in if statement so the PID encoder function is more accurate
//and only takes into account encoder ticks when its moving forward 
//having it take into account when turning would mess up the speed calculations
//I dont even use encoders for turning anymore anymore
void right_encoder_event(){
  if (motor_state == GO_ONE_CELL || motor_state == GO_ONE_CELL_REVERSE){
  right_count ++; 
  }
//  right_count ++;
}


void print_encoder_count(){

  Serial.print("left_count");
  Serial.println(left_count);
  Serial.println();
  Serial.print("right_count");
  Serial.println(right_count);
  Serial.println();
}

//Basic Motor Functions
void forward(){
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_2, HIGH);
  digitalWrite(motor_2_logic_1, HIGH);
  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_2_logic_2, LOW);


}


void reverse(){
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, HIGH);//right
  digitalWrite(motor_1_logic_2, LOW);

  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, HIGH);//left
}

//double check this function I switched which logic is left and which is right
void reverse(double left_speed, double right_speed) {


  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  analogWrite(motor_1_logic_1, right_speed);//right
  digitalWrite(motor_1_logic_2, LOW);

  digitalWrite(motor_2_logic_1, LOW);
  analogWrite(motor_2_logic_2, left_speed);//left

}




void halt(){


  digitalWrite(turn_on_en_1, LOW);
  digitalWrite(turn_on_en_2, LOW);

  digitalWrite(motor_1_logic_1, HIGH);
  digitalWrite(motor_1_logic_2, HIGH);
  digitalWrite(motor_2_logic_1, HIGH);
  digitalWrite(motor_2_logic_2, HIGH);


}

void halt_until(unsigned long stop_time ) {
  unsigned long curr = millis();
  while (abs(millis() - curr) < stop_time) {
    halt();
  }
}



void reverse_turn(){
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, LOW);
  //analogWrite(motor_1_logic_2,255);
  digitalWrite(motor_1_logic_2, HIGH);

  digitalWrite(motor_2_logic_1, LOW);
  //analogWrite(motor_2_logic_2,255);
  digitalWrite(motor_2_logic_2, HIGH);
}


void left_turn(){
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_1_logic_2, HIGH);

  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, HIGH);

}


void right_turn(){
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);


  digitalWrite(motor_1_logic_1, HIGH);
  digitalWrite(motor_1_logic_2, LOW);

  digitalWrite(motor_2_logic_1, HIGH);
  digitalWrite(motor_2_logic_2, LOW);
}

void left_turn(int turn_speed) {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, LOW);
  analogWrite(motor_1_logic_2, turn_speed);

  digitalWrite(motor_2_logic_1, LOW);
  analogWrite(motor_2_logic_2, turn_speed);

}


void right_turn(int turn_speed) {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);


  digitalWrite(motor_1_logic_1, turn_speed);
  digitalWrite(motor_1_logic_2, LOW);
  digitalWrite(motor_2_logic_1, turn_speed);
  digitalWrite(motor_2_logic_2, LOW);
}

void forward(int left_speed, int right_speed) {


  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  analogWrite(motor_1_logic_2, right_speed);
  analogWrite(motor_2_logic_1, left_speed);
  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_2_logic_2, LOW);

}

//GYROSCOPE turn functions
void left_turn_until(){
  gyro_angle = 0;
  gyro_sum = 0;
  halt_until(halt_delay);
  while (  abs(gyro_angle) < left_turn_length ) { //150, 175,120,110,130,90,95,96 ,93(for when correct),186,93,90
    gyro_tick();
    left_turn();                  //350,360,380,390
    //left_turn(255);
  }
  left_turn(0);
  halt_until(halt_delay);
}

/////use left_count


void right_turn_until(){ //330,240,220
  gyro_angle = 0;
  gyro_sum = 0;
  halt_until(halt_delay);
  while ( abs(gyro_angle)  <right_turn_length ) { //150,175,120,110,130 ,90,95,96,93(for when correct),186,93,90,85
    gyro_tick();
    right_turn();                  //350,360,380,390
    //right_turn(255);
  }
  right_turn(0);
  halt_until(halt_delay);
}



void reverse_turn_until_r(){ //330,240,220
  gyro_angle = 0;
  gyro_sum = 0;
  right_turn_until();
  delay(100);
  right_turn_until();

}
void reverse_turn_until_l(){
  gyro_angle = 0;
  gyro_sum = 0;

  left_turn_until();
  delay(100);
  left_turn_until();

}

//only uses this forward until function for certain special times when going forward
void forward_until(int left_speed, int right_speed, unsigned long stop_time) {
  halt_until(halt_delay);
  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
    forward(left_speed,right_speed);
  }
  forward(0,0);
  halt_until(halt_delay);
}

//only uses this forward until function for certain special times when going forward
void reverse_until(int left_speed, int right_speed, unsigned long stop_time) {
  halt_until(halt_delay);
  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
  reverse(left_speed,right_speed);
  }
  reverse(0,0);
  halt_until(halt_delay);
}

//void regulateSensor_45_L(){
//  if (sensorReading_45_left < 0) {
//    sensorReading_45_left = ~sensorReading_45_left + 1;
//  }
//
//}
//
////gets sensor data from r to use for pid control function
////all it does is take the sensors reading and if its less than 0 make it plus one
////EITHER MAP IN THIS FUNC OR IN READIR
//void regulateSensor_45_R(){
//  if (sensorReading_45_right < 0) {
//    sensorReading_45_right = ~sensorReading_45_right + 1;
//  }
//}
//
////gets sensor data from l to use for pid control function
////all it does is take the sensors reading and if its less than 0 make it plus one
////EITHER MAP IN THIS FUNC OR IN READIR
//void regulateSensorL(){
//
//  if (sensorReading_left < 0) {
//    sensorReading_left = ~sensorReading_left + 1;
//  }
//
//}
//
////gets sensor data from r to use for pid control function
////all it does is take the sensors reading and if its less than 0 make it plus one
////EITHER MAP IN THIS FUNC OR IN READIR
//void regulateSensorR(){
//  if (sensorReading_right < 0) {
//    sensorReading_right = ~sensorReading_right + 1;
//  }
//}

//TEST THE ENCODER PID
//in the meantime this will go off good base values
//MAKE THIS LATER INTO TAKE AVERAGE FOR ONE SIDE AND USE THAT PID
//BETTER YET USE PID FOR WHAT THE MIDDLE VALUE FOR A SENSOR SHOULD BE AND THEN USE THAT AS THE ERROR FOR KP KI and KD
void pid_control_one_wall_l(){
  readIR();
  error_l = abs(sensorReading_45_left - middle_point_l);
//
//  if (error_l > 250){
//    error_l = 175;
//  }
  if (error_l > 600){
    error_l = 300;
  }
  p_control_l = error_l * kp_l;
  
  
  d_control_l = abs(error_l - prev_error_l) * kd_l;


  if (sensorReading_45_left > middle_point_l) {

    motor_left = base_speed + ( p_control_l + d_control_l);
    motor_right = base_speed - (p_control_l + d_control_l);
    prev_error_l = error_l;

  }

  else if (sensorReading_45_left < middle_point_l) {
    motor_left = base_speed - (p_control_l + d_control_l);
    motor_right = base_speed + (p_control_l + d_control_l);
    prev_error_l = error_l;
  }


  else {
    //nothing
    return;
  }

}

void pid_control_one_wall_r(){
  readIR();
  error_r = abs(sensorReading_45_right - middle_point_r);
  if (error_r > 600){
    error_r = 300;
  }
  
//  if (error_r > 250){
//    error_r = 175;
//  }

  p_control_r = error_r * kp_r;

  d_control_r = abs(error_r - prev_error_r) * kd_r;


  if (sensorReading_45_right > middle_point_r) {

    motor_left = base_speed - ( p_control_r + d_control_r);
    motor_right = base_speed + (p_control_r + d_control_r);
    prev_error_r = error_r;

  }

  else if (sensorReading_45_right < middle_point_r) {
    motor_left = base_speed + (p_control_r + d_control_r);
    motor_right = base_speed - (p_control_r + d_control_r);
    prev_error_r = error_r;
  }


  else {
    //nothing
    return;
  }

}





void pid_control_two_45_walls(){
  //gets reading for pid
  readIR();

  //all it does is if reading is negative set it to be opposite plus one
//  regulateSensor_45_L();
//  regulateSensor_45_R();

  
  reset_error ++;
  //resets reset error which is used for i part of pid  which takes in error from previous cycles
  if (reset_error > 10000){
    reset_error = 0;
    error_buildup = 0;
  }
  
  //error value
  error = abs(sensorReading_45_left - sensorReading_45_right);
  if (error > 600){
    error = 300;
  }
  
  Serial.println("ERROR VALUE: ");
  Serial.println(error);
//  I THINK THIS IS TO PREVENT DRASTIC CHANGES IN MOTOR 
//  ALTHOUGH SINCE MY IR'S ARE MUCH BETTER NOW I THINK I SHOULD PROBABLY EITHER CHANGE OR GET RID OF THIS
//  if (error > 300){//250
//    error = 150;//175
//  }
//  
  //p control
  p_control = error * kp;


  //i control
  error_buildup += error;
  i_control = error_buildup * ki;


  //d control

  d_control = abs(error - prev_error) * kd;



  //too close left
  if (sensorReading_45_left > sensorReading_45_right) {


    motor_left = base_speed + (p_control + d_control + i_control); //
    motor_right = base_speed - (p_control + d_control + i_control); //

//    motor_left = base_speed_l + (p_control +d_control); //+ i_control); //
//    motor_right = base_speed_r - (p_control + d_control); //+ i_control); //
    
    
    //    motor_left += (p_control + d_control);
    //    motor_right -= (p_control + d_control);

    //
    prev_error = error;
    return;
  }

  //too close right
  else if (sensorReading_45_right > sensorReading_45_left) {





    motor_left = base_speed - (p_control  + d_control + i_control); //
    motor_right = base_speed +  (p_control  + d_control + i_control); //
//    

//    motor_left = base_speed_l - (p_control + d_control); //+ i_control); //
//    motor_right = base_speed_r + (p_control + d_control); //+ i_control); //
    
    
    //    motor_left -= (p_control + d_control);
    //    motor_right += (p_control + d_control);
    prev_error = error;
    return;
  }
  //equal to each other
  else {
    //nothing
    //motor_left and motor_right stay the same
    prev_error = error;
    return;
  }

}


void pid_control_two_90_walls(){
  //gets reading for pid
  readIR();


  
  reset_error ++;
  //resets reset error which is used for i part of pid  which takes in error from previous cycles
  if (reset_error > 10000){
    reset_error = 0;
    error_buildup = 0;
  }
  
  //error value
  error = abs(sensorReading_left - sensorReading_right);
  if (error < 600){
    error = 300;
  }

//  I THINK THIS IS TO PREVENT DRASTIC CHANGES IN MOTOR 
//  ALTHOUGH SINCE MY IR'S ARE MUCH BETTER NOW I THINK I SHOULD PROBABLY EITHER CHANGE OR GET RID OF THIS
//  if (error > 300){//250
//    error = 150;//175
//  }
//  
  //p control
  p_control = error * kp;


  //i control
  error_buildup += error;
  i_control = error_buildup * ki;


  //d control

  d_control = abs(error - prev_error) * kd;



  //too close left
  if (sensorReading_left > sensorReading_right) {


//    motor_left = base_speed + (p_control + d_control + i_control); //
//    motor_right = base_speed - (p_control + d_control + i_control); //

    motor_left = base_speed + (p_control ); //
    motor_right = base_speed - (p_control); //
    
    
    //    motor_left += (p_control + d_control);
    //    motor_right -= (p_control + d_control);

    //
    prev_error = error;
    return;
  }

  //too close right
  else if (sensorReading_right > sensorReading_left) {





//    motor_left = base_speed - (p_control  + d_control + i_control); //
//    motor_right = base_speed +  (p_control  + d_control + i_control); //
//    
    motor_left = base_speed - (p_control ); //
    motor_right = base_speed + (p_control ); //
    
    
    //    motor_left -= (p_control + d_control);
    //    motor_right += (p_control + d_control);
    prev_error = error;
    return;
  }
  //equal to each other
  else {
    //nothing
    //motor_left and motor_right stay the same
    prev_error = error;
    return;
  }

}

//NEED TO TEST THIS
//WILL RUN INTO ERRORS IF COUNT GOES UP DURING TURNS THUS MESSING UP THE CURR_SPEED CALCULATIONS
//TEST TO SEE IF IT WORKS GOING FORWARD ONLY FIRST
//does both motors 
void pid_control_enc(){
  cli();
  curr_left_count = left_count;
  curr_right_count = right_count;
  sei();
  
  //take derivative to get curr speed
  curr_left_speed = curr_left_count - prev_left_count;
  curr_right_speed = curr_right_count - prev_right_count;

  //get error from difference between wanted speed and curr speed
  error_l_enc = abs(curr_left_speed - left_wanted_speed);
  error_r_enc = abs(curr_right_speed - right_wanted_speed);
  
  p_control_enc_l = error_l_enc * kp_enc;
  p_control_enc_r = error_r_enc * kp_enc;

  d_control_enc_l = error_l_enc - prev_error_l_enc;
  d_control_enc_r = error_r_enc - prev_error_r_enc;

  
  if (left_wanted_speed > curr_left_speed){
    motor_left = base_speed  + (p_control_enc_l + d_control_enc_l);
  
  }


  else if (left_wanted_speed < curr_left_speed){
    motor_left = base_speed - (p_control_enc_l + d_control_enc_l);
  }


  if (right_wanted_speed > curr_right_speed){
    motor_right = base_speed  + (p_control_enc_r + d_control_enc_r);
    
  }

  else if (right_wanted_speed < curr_right_speed){
    motor_right = base_speed - (p_control_enc_r + d_control_enc_r);
    
  }

  //for getting curr speed;
  prev_left_count = curr_left_count;
  prev_right_count = curr_right_count;

  //for d_control
  prev_error_l_enc = error_l_enc;
  prev_error_r_enc = error_r_enc;
  
  
}

//chooses which pid to do
void pid_control(){
  //readIR();

  //  has_45_left_wall();
  //  has_45_right_wall();
  //  has_left_wall();
  //  has_right_wall();
  //  has_back_wall();
  //  has_front_wall();
  //has_walls();
  //does this faster by not having the avg being taken each time
  has_walls_pid();
  //testing
  
  //pid_control_two_45_walls();
  //pid_control_one_wall_l();
  //pid_control_one_wall_r();
  //pid_control_enc();
  //pid_control_two_90_walls();


  //pid_control_enc();

  

  //using 45 deg sensors
  if (left_45_wall == true && right_45_wall == true) {
    pid_control_two_45_walls();
  }
  else if (left_45_wall == true &&  right_45_wall == false) {
    pid_control_one_wall_l();
   
  }
  else if (left_45_wall == false && right_45_wall == true) {
    pid_control_one_wall_r();
    
  }

  //go off encoders if no walls
  // if encoders are really good go off of encoders even more
  else if (left_45_wall && right_45_wall == false) {
    //pi_control_enc();
    forward(motor_left,motor_right);
    //pid_control_two_45_walls();

    //pid_control_one_wall_r();

  }
  else {
    pid_control_two_45_walls();
  }

  

//I GOT RID OF 90 degree sensor PID to shorten code 
//if I need it back look at old github versions to get back the code 
//but in the meantime it was just taking up space


  return;
}



void go_one_cell(){
  //timer approach
  // halt_until(halt_delay);
  // //unsigned long curr = millis();
  // unsigned long curr = micros();
  // // while (millis() - curr <910 ) {//903,700,800
  // while(micros() - curr < 901000){
  //
  //   readIR();
  //   // print_encoder_count();
  //    //pid_control_two_walls();
  //    //IF PID IS DONE IN A STATE MACHINE I WONT NEED PID IN THIS FUNCTION
  //    //HAVING IN STATE MACHINES COULD MEAN I COULD HAVE BETTER READ RESULTS
  //    //NEED TO MAKE SURE THIS DOESN'T MESS UP CONTROL GOING FORWARD
  //    pid_control();
  //
  //    //nforward();
  //    forward(motor_left, motor_right);
  ////    read_distance();
  //  }
  //  halt_until(halt_delay);
  //read_distance();


  //off encoders
  halt_until(halt_delay);  //1455
  
  //unsigned long curr = right_count;//1490,1480,1485,1487(really goodd but go to 1486 to mitigate going over),1400,1440,1460(sometimes over)
  //unsigned long curr = left_count;
  cli();
  //unsigned long curr = right_count;
  curr_count_cell = right_count;
  sei();
  while (abs(right_count - curr_count_cell) < go_one_cell_length ) { //945, 1400,1380,1438,1000,400,200,100,1000,1400(a little off),1500,1430,1460,1480 (too much),1470,1410,1420,1405                                                                               400,500,600,650,750,1000,1100,1200  ,1300  , 952 , 930 , 912,908(best so far) , 905 , 890 , 908 ,912,920,930,945,960,1300,1400,1450,1470,1474,1480,1490,1510,1511
  //while(abs(left_count - curr) <1380 ){ //1450,1465,1450    readIR();                   //900,500,600,700,800,900,1000,1070,1100, ,1150,1160, 1200 , 1130,1000 , 900    ,1000 , 945  ,800 ,850 , 880 , 885,895 , 915 ,925(over),920(both) , close 905 ,980 ,960(closest)
    // print_encoder_count();
    //pid_control_two_walls();
    //IF PID IS DONE IN A STATE MACHINE I WONT NEED PID IN THIS FUNCTION
    //HAVING IN STATE MACHINES COULD MEAN I COULD HAVE BETTER READ RESULTS
    //NEED TO MAKE SURE THIS DOESN'T MESS UP CONTROL GOING FORWARD

    pid_control();

    forward(motor_left, motor_right);
    //reverse(motor_left,motor_right);
    print_encoder_count();
    
  }
  //probably uncomment this below
  forward(0,0);
  halt_until(halt_delay);

}



void reverse_until( unsigned long stop_time) {

  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
    pid_control();
    reverse(motor_left, motor_right);

  }
}





//correct mouse if theirs a front wall in front
//should replace bumping into walls in random_move function
//run pid while reversing so it straightens it self out even more
void correct_mouse_far(){
//  readIR();
//  halt_until(halt_delay);
//  while (sensorReading_middle < 58) { //70
//    //    readIR();
//    //    if (sensorReading_middle > 60){
//    //      break;
//    //    }
//    pid_control();
//    forward(motor_left - 20, motor_right - 20);
//    readIR();
//  }
//  forward(0,0);
//  halt_until(halt_delay);
}

//pretty sure this should work in theory
//need to test pid on reverse 
void correct_mouse_close(){
  
  readIR();
  //if (hasfrontwall(){
  halt_until(halt_delay);
  while (sensorReading_middle >90) {//50,54,48,45,70(might be good too),68,86,90 ,
    pid_control();
    //reverse(motor_left - 20, motor_right - 20);
    reverse(motor_left,motor_right);
    //reverse(base_speed-20,base_speed-20);
    //reverse(base_speed,base_speed);
    readIR();
  }
  reverse(0,0);
  halt_until(halt_delay);

}

void correct_mouse(){
  reverse(motor_left, motor_right);
  delay(200);//1000 is too long
  reverse(0,0);
  halt_until(halt_delay);
  readIR();
  while(sensorReading_middle < correct_mouse_thres){
    //pid_control();
    forward(motor_left,motor_right);  
    pid_control();
    //readIR();
  }
  forward(0,0);
  halt_until(halt_delay);  
}


void go_one_cell_reverse(){
  //off encoders
  halt_until(halt_delay);  //1455
  cli();
  //unsigned long curr = right_count;
  curr_count_cell = right_count;
  sei();
  while (abs(right_count - curr_count_cell) < 1420 ) {                                                                                
    pid_control();
  
    reverse(motor_left,motor_right);
    print_encoder_count();
    
  }
  //probably uncomment this below
  reverse(0,0);
  halt_until(halt_delay);
}




//CHECK IF THIS WORKS
//GONNA COMMENT THIS OUT FOR NOW
void can_correct_func(){
  if (can_correct == 1) {
    //correct_mouse_far();
    //correct_mouse_close();
    correct_mouse();
    can_correct = 0;
  }
}


//error_check = false;
//MIGHT PUT FLOODFILL INTO THIS STATE MACHINE AS WELL

// I PUT A COPY OF THIS INTO GLOBAL VALUES.H SO THE STATES CAN BE ACCESSED GLOBALLY BY THE INTERRUPTS FUNCTIONS ABOVE 
// LEAVING A COPY BELOW 
//enum MOTOR_STATES {MOTOR_INIT, GO_ONE_CELL, CHOOSE_MOVE, TURN_REVERSE_L, TURN_REVERSE_R, TURN_LEFT, TURN_RIGHT } motor_state;
//CORRECT_MOUSE
void motor_init(){
  motor_state = MOTOR_INIT;
}

void motor_tick(){

  switch (motor_state) { //transitions
    case MOTOR_INIT:
      //motor_state = GO_ONE_CELL;
      motor_state = CHOOSE_MOVE;
      break;
    case GO_ONE_CELL:
      //motor_state = RANDOM_MOVE;
      //all walls
      motor_state = CHOOSE_MOVE;
      break;
      
    case GO_ONE_CELL_REVERSE:
      motor_state = CHOOSE_MOVE;
      break;
      
    case CHOOSE_MOVE:
      //structured like a 3 input truth table

//      readIR();
////      has_front_wall();
////      has_left_wall();
////      has_right_wall();

        has_walls();
          

        //front left right
      //000
            if (front_wall == false && left_wall == false && right_wall == false){
              random_choice = random(millis()) % 2;
              if (random_choice == 0){
                motor_state = GO_ONE_CELL;
              }
              else if (random_choice == 1){
                motor_state = TURN_LEFT;
              }
              else if (random_choice == 2){
                motor_state = TURN_RIGHT;
              }
            }
            //001
            else if (front_wall == false && left_wall == false && right_wall == true){
              random_choice = random(millis()) % 2;
              if (random_choice == 0){
                motor_state = GO_ONE_CELL;
              }
              else if (random_choice == 1){
                motor_state = TURN_LEFT;
              }
            }
            //010
            else if (front_wall == false && left_wall == true && right_wall == false){
              random_choice = random(millis()) % 2;
              if (random_choice == 0){
                motor_state = GO_ONE_CELL;
              }
              else if (random_choice == 1){
                motor_state = TURN_RIGHT;
              }
            }
      
            //011
            else if (front_wall == false && left_wall == true && right_wall == true){
              motor_state = GO_ONE_CELL;
            }
            //100
            else if (front_wall == true && left_wall == false && right_wall == false){
              can_correct = 1;
              random_choice = random(millis()) % 2;
              if (random_choice == 0){
                motor_state = TURN_LEFT;
              }
              else if (random_choice == 1){
                motor_state = TURN_RIGHT;
              }
            }
            //101
            else if (front_wall == true && left_wall == false && right_wall == true){
              can_correct = 1;
              motor_state = TURN_LEFT;
            }
            //110
            else if (front_wall == true && left_wall == true && right_wall == false){
              can_correct = 1;
              motor_state = TURN_RIGHT;
            }
      
      
            //111
            else if (front_wall == true && left_wall == true && right_wall == true){
              can_correct = 1;
              readIR();
                if (sensorReading_right > sensorReading_left){
                motor_state = TURN_REVERSE_L;
                }
                else if (sensorReading_right< sensorReading_left){
                motor_state = TURN_REVERSE_R;
                }
      
                else{
                  motor_state = TURN_REVERSE_R;
                }
      
            }
      
            //nothing else
            else{
              motor_state = GO_ONE_CELL;
            }
     
      
      //testing
//      if (front_wall == true) {
//         if (sensorReading_right > sensorReading_left){
//          motor_state = TURN_REVERSE_L;
//          
//          }
//          else if (sensorReading_right< sensorReading_left){
//          motor_state = TURN_REVERSE_R;
//          }
//       }
//      else {
//        motor_state = GO_ONE_CELL;
//      }

      //motor_state = GO_ONE_CELL;
      //motor_state = GO_ONE_CELL_REVERSE;
      //motor_state = REVERSE;
      break;

    case TURN_RIGHT:
      motor_state = GO_ONE_CELL;
      //motor_state = CHOOSE_MOVE;
      break;
    case TURN_LEFT:
      motor_state = GO_ONE_CELL;
      //motor_state = CHOOSE_MOVE;
      break;
    case TURN_REVERSE_L:
      motor_state = GO_ONE_CELL;
      //motor_state = CHOOSE_MOVE;
      break;
    case TURN_REVERSE_R:
      motor_state = GO_ONE_CELL;
      //motor_state = CHOOSE_MOVE;
      break;
    default:
      motor_state = GO_ONE_CELL;
      break;
  }
  switch (motor_state) { //actions
    case MOTOR_INIT:
      break;
    case GO_ONE_CELL:
      go_one_cell();//this calls pid inside of it
      Serial.println("GO_ONE_CELL");
      break;
    case GO_ONE_CELL_REVERSE:
      go_one_cell_reverse();
      break;
    case CHOOSE_MOVE:
      //nothing it just chooses move
      break;
    case TURN_REVERSE_L:
      can_correct_func();
      reverse_turn_until_l();
      Serial.println("REVERSE");
      break;
    case TURN_REVERSE_R:
      can_correct_func();
      reverse_turn_until_r();
      break;
    case TURN_LEFT:
      can_correct_func();
      left_turn_until();
      break;
    case TURN_RIGHT:
      can_correct_func();
      right_turn_until();
      break;
  }


}

//FLOODFILL TESTING
//TOOK OUT FLOODFILL_MOVE_TO_NEXT_SPACE,
//I'll JUST HAVE MOVE TO NEXT IDEAL SPACE IN STACK CHECK
//IT MAKES THE MOST SENSE TO HAVE IT THERE NOW
//IF NEEDED I'll CHANGE IT TO MAKE THE CODE NEATER
enum FLOODFILL_STATES{FLOODFILL_INIT,FLOODFILL_START,FLOODFILL_POS_CHECK,FLOODFILL_STACK_CHECK,FLOODFILL_END} floodfill_state;
void floodfill_init(){
  floodfill_state = FLOODFILL_INIT;
}

//MAIN ISSUE IS MOUSE POS DOES IT HAVE TO BE PRESENT DURING ALL STACK CHECK EVENTS 
//ALSO NEED TO FIGURE OUT HOW TO UPDATE MAZE AS IT GOES THROUGH THE FIRST TIME
//KEY WORD IS PROBABLY FIRST TIME

//stack operations assume the stack works just like a standard c++ stack
void floodfill_tick(){
  switch(floodfill_state){//transitions
    case FLOODFILL_INIT:
      floodfill_state = FLOODFILL_START;
      break;
    case FLOODFILL_START:
      floodfill_state = FLOODFILL_POS_CHECK;
      break;
      
    case FLOODFILL_POS_CHECK:
      if ((mouse_pos.y_pos == goal_coord.y_pos) &&  (mouse_pos.y_pos == goal_coord.y_pos)){
        floodfill_state = FLOODFILL_END;
      }
      else {
        floodfill_state = FLOODFILL_STACK_CHECK;
        //SHOULD PUSH STARTING MOUSE_POS IN FLOODFILL_START INSTEAD SO IT DOESN'T KEEP HAPPENING
        //NEVERMIND THIS NEEDS TO HAPPEN EACH TIME BECAUSE OF HOW IT POPS THE CELL TO CHECK FROM THE CHECKS STACK
        //NEVERMIND TO ABOVE NEVERMIND BECAUSE THE ALGORITHM SAYS DIFFERENTLY
        //NEVERMIND TO ABOVE NEVERMIND BECAUSE DOING IT ON PAPER SAYS DIFFERENTLY
        checks.push(mouse_pos);
        //set minval to -10 so if it stays -10 then we know the cellcheck was correct at first;
        min_val = -10;
      }
      break;
    case FLOODFILL_STACK_CHECK:
//      if (checks.count() != 0){
//         floodfill_state = FLOODFILL_STACK_CHECK;
//         //floodfill_state = FLOODFILL_MOVE_TO_NEXT_SPACE;
//      }
//      else {
//        floodfill_state = FLOODFILL_MOVE_TO_NEXT_SPACE;
//        //floodfill_state = FLOODFILL_POS_CHECK;
//      }

        if (checks.count() != 0){
          floodfill_state = FLOODFILL_STACK_CHECK;
          min_val = -10;
        }
        else{
          floodfill_state = FLOODFILL_POS_CHECK;
        }
      
      break;
      
//    case FLOODFILL_MOVE_TO_NEXT_SPACE:
//  //    floodfill_state = FLOODFILL_POS_CHECK;
//      break;
    
    
    case FLOODFILL_END:
      //keep it in end state 
      //all it is is 
      floodfill_state = FLOODFILL_END;
      break;
    default:
      break;
  }
  switch(floodfill_state){//actions
    case FLOODFILL_INIT:
      break;
     case FLOODFILL_START:
      //sets up goal coord in 2d array
      goal_coord.y_pos = 0;
      goal_coord.x_pos = 9;

      //sets up mouse pos
      mouse_pos.y_pos = 9;
      mouse_pos.x_pos = 0;

      //sets up initial value for all cells in maze
      for (int x = 0; x < maze_x_length; ++x){
        for (int y = 0; y < maze_y_length; ++y){
          maze[y][x].value = abs(goal_coord.y_pos - y) + abs(goal_coord.x_pos - x);
        }
      }

      // can set up initial wall config since all starting cells are the same
      maze[mouse_pos.x_pos][mouse_pos.y_pos].left_wall = 1;
      maze[mouse_pos.x_pos][mouse_pos.y_pos].right_wall = 1;
      maze[mouse_pos.x_pos][mouse_pos.y_pos].front_wall = 0;
      maze[mouse_pos.x_pos][mouse_pos.y_pos].back_wall = 1;

      //because its going up 
      orientation = 1;

      //got rid of checks.push(mouse_pos) here because it does this in floodfill pos_check
      break;
      
    case FLOODFILL_POS_CHECK:
      break;
    case FLOODFILL_STACK_CHECK:
      cell_check = checks.pop(); // pretty sure this gets and removes from top of stack 
      //if pop doesn't do both does things do checks.peek and the line after do checks.pop
      
      //need to checks and update the walls
      has_walls();

      // if facing top
      if (orientation == 1){
        
      }
      
      //if facing right
      else if (orientation == 2){
        
      }
      //if facing down/bottom
      else if (orientation == 3){
        
      }
      //if going left
      //orientation == 0
      else {
        
      }


      
      //left_wall is different thatn maze[][].left_wall
      //left_wall is global left wall var
      //mase[][].left_wall is for if in a specific cell there is a left wall
      
      
      //if left wall is open
      if (left_wall == false){
        //       maze[cell_check.y_pos][cell_check.x_pos].leftwall = 0;
        
        //if cell_check is not 1 greater 
        if (maze[cell_check.y_pos][cell_check.x_pos].value  != maze[cell_check.y_pos][cell_check.x_pos-1].value +1  ){
          if (min_val == -10){
             min_val = maze[cell_check.y_pos][cell_check.x_pos-1].value;
          }
          else{
            if (maze[cell_check.y_pos][cell_check.x_pos-1].value < min_val){
              min_val = maze[cell_check.y_pos][cell_check.x_pos-1].value;
            }
          }
          neighbor_to_push.y_pos = cell_check.y_pos;
          neighbor_to_push.x_pos = cell_check.x_pos - 1;
          checks.push(neighbor_to_push);
        }
        //if is 1 greater nothing
        else{
          // do nothing
        }
      }

      if (left_wall == true){
        maze[cell_check.y_pos][cell_check.x_pos].left_wall = 1;        
      }

      //if front wall is open
      if (front_wall == false){
         maze[cell_check.y_pos][cell_check.x_pos].front_wall = 0;
        //if cell_check is not 1 greater 
        if (maze[cell_check.y_pos][cell_check.x_pos].value  != maze[cell_check.y_pos-1][cell_check.x_pos].value + 1  ){
          if (min_val == -10){
             min_val = maze[cell_check.y_pos - 1][cell_check.x_pos].value;
          }
          else{
            if (maze[cell_check.y_pos - 1][cell_check.x_pos].value < min_val){
              min_val = maze[cell_check.y_pos - 1][cell_check.x_pos].value;
            }
          }
          neighbor_to_push.y_pos = cell_check.y_pos - 1;
          neighbor_to_push.x_pos = cell_check.x_pos;
          checks.push(neighbor_to_push);
        }
        //if cell check is 1 greater
        else{
          //nothing
        }
      }


      if (front_wall == true){
        maze[cell_check.y_pos][cell_check.x_pos].front_wall = 1;        
      }
      

      //if right wall is open
      if (right_wall == false){
         maze[cell_check.y_pos][cell_check.x_pos].right_wall = 0;
        //if cell_check is not 1 greater 
        if (maze[cell_check.y_pos][cell_check.x_pos].value  != maze[cell_check.y_pos][cell_check.x_pos+1].value +1  ){
          if (min_val == -10){
             min_val = maze[cell_check.y_pos][cell_check.x_pos+1].value;
          }
          else{
            if (maze[cell_check.y_pos][cell_check.x_pos+1].value < min_val){
              min_val = maze[cell_check.y_pos][cell_check.x_pos+1].value;
            }
          }
          neighbor_to_push.y_pos = cell_check.y_pos;
          neighbor_to_push.x_pos = cell_check.x_pos + 1;
          checks.push(neighbor_to_push);
        }
        //if cell check is 1 greater
        else{
          //nothing
        }
      }


      if (right_wall == true){
        maze[cell_check.y_pos][cell_check.x_pos].right_wall = 1;        
      }
      
           
      //if back wall is open
      if (back_wall == false){
         maze[cell_check.y_pos][cell_check.x_pos].back_wall = 0;
        //if cell_check is not 1 greater 
        if (maze[cell_check.y_pos][cell_check.x_pos].value  != maze[cell_check.y_pos+1][cell_check.x_pos].value +1  ){
          if (min_val == -10){
             min_val = maze[cell_check.y_pos+1][cell_check.x_pos].value;
          }
          else{
            if (maze[cell_check.y_pos+1][cell_check.x_pos].value < min_val){
              min_val = maze[cell_check.y_pos+1][cell_check.x_pos].value;
            }
          }
          neighbor_to_push.y_pos = cell_check.y_pos + 1;
          neighbor_to_push.x_pos = cell_check.x_pos;
          checks.push(neighbor_to_push);
        }
        //if cell check is 1 greater
        else{
          //nothing
        }
      }


      if (back_wall == true){
        maze[cell_check.y_pos][cell_check.x_pos].back_wall = 1;        
      }
      
      //remember above is for only one orientation (going top) need to do above for all orientations
      

      // if min_val != -10 it means minval was made thus if statement in algorithm 
      // has to run 
      if (min_val != -10){
        //cell_check should work for this //also see if mouse_pos would fit as well but I think it would not 
        // update for multiple passes through stack check
        maze[cell_check.y_pos][cell_check.x_pos].value = min_val + 1;
      }
      

      //REMEMBER TO RESET MOUSE_POS WHEN YOU GO TO NEXT IDEAL CELL
      //ADVANCE TO NEXT IDEAL CELL
      //ALSO REMEMBER TO PUT IN NEW ORIENTATION
      
      
      break;
    case FLOODFILL_END:
      halt();
      break;
  }
  
}







//void testing_func(){
//  readIR();
//
//  //if (hasfrontwall()){
//
//  //82,
//    if (sensorReading_middle <84){
//      while(sensorReading_middle < 84){
//        forward(motor_left,motor_right);
//        pid_control();
//      }
//      halt_until(halt_delay);
//    }
//
//    else if (sensorReading_middle > 84){
//      while(sensorReading_middle > 84){
//        reverse(motor_left,motor_right);
//        pid_control();
//      }
//      halt_until(halt_delay);
//    }
//
//
////  }
//
//  return;
//}

////this only happens I think when the sensor readings are the same for multiple cycles
////which usually indicates the mouse is stuch somehow
////should not need if new mouse is done right
//void error_catch(){
//  curr_timer = millis();
//
//  if (curr_timer - prev_timer >= error_check_interval) {
//    prev_timer = curr_timer;
//    // if (error_check == true) {
//    if (prev_sensorReading_left == sensorReading_left && prev_sensorReading_middle == sensorReading_middle && prev_sensorReading_right == sensorReading_right) {
//      int rand_num = random(millis()) % 2;
//      if (rand_num == 1) {
//        halt_until(700);
//        reverse_until(100);
//        halt_until(700);
//        left_turn_until();
//        halt_until(700);
//      }
//      else {
//        halt_until(700);
//        reverse_until(100);
//        halt_until(700);
//        right_turn_until();
//        halt_until(700);
//      }
//    }
//
//    if (  left_count - prev_encoder_tick < 100) {
//      int rand_num = random(millis()) % 2;
//      if (rand_num == 1) {
//        halt_until(700);
//        reverse_until(100);
//        halt_until(700);
//        left_turn_until();
//        halt_until(700);
//      }
//      else {
//        halt_until(700);
//        reverse_until(100);
//        halt_until(700);
//        right_turn_until();
//        halt_until(700);
//      }
//    }
//
//    prev_sensorReading_left = sensorReading_left;
//    prev_sensorReading_middle = sensorReading_middle;
//    prev_sensorReading_right = sensorReading_right;
//    prev_encoder_tick = left_count;
//  }
//}









