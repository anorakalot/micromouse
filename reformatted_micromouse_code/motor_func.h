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

//Basic Motor Functions
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

//Encoder turn functions 
void left_turn_until() {//330,240,220
  unsigned long curr = left_count;//382,380,375,378,380,383,390,380,382,365
  while ( left_count - curr < 232) { //380 330 ,280,290,300,310,320,330,340,350,360,380,365,360
    left_turn();                  //350,360,380,390
  }
}
void left_with_wall() {//330,240,340
  unsigned long curr = left_count;//382,380,375,378,380,383,390,380,382,365
  while ( left_count - curr < 356  ) { //380 330 ,280,290,300,310,320,330,340,350,360,380,365,360
    left_turn();                  //350,360,380,390
  }               //318
}

//use left_count
void right_turn_until() {
  unsigned long curr = left_count;//335,243 
  while ( left_count - curr < 265) { //320,340, 370,300,290,280,270,260,280,300,325,330
    right_turn();               //325,335
  }                 //330,264,270,275
}

void right_with_wall() {
  unsigned long curr = left_count;//335
  while ( left_count - curr <310  ) { //320,340, 370,300,290,280,270,260,280,300,325,330
    right_turn();               //325,335
  }                 //330
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
    while ( left_count - curr_l < 860 ) { //800,830, 860,870,790,800,810,840,860,870
      left_turn();                  //870,910u
    }

  }

  else { //use left_count instead of right_count
    while ( left_count - curr_r < 720) { //800,830, 860,870,790
      right_turn();
    }

  }

}

//only uses this forward until function for certain special times when going forward
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

//gets sensor data from l to use for pid control function
//all it does is take the sensors reading and if its less than 0 make it plus one
void regulateSensorL() {
  sensorReading_left = analogRead(sensor_left);
  sensorReading_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 0, 200);

  //permReading_left = 0 for some reason
  sensorReading_left = sensorReading_left - permReading_left;
  
   
   if (sensorReading_left - permReading_left < 0){ 
    sensorReading_left = ~sensorReading_left + 1;
  }
}

//gets sensor data from r to use for pid control function
//all it does is take the sensors reading and if its less than 0 make it plus one
void regulateSensorR() {
  sensorReading_right = analogRead(sensor_right);


  sensorReading_right = map(sensorReading_right, 180, 820, 0, 200);

  sensorReading_right = sensorReading_right - permReading_right;

    
   if (sensorReading_right - permReading_right < 0){ 
    sensorReading_right = ~sensorReading_right + 1;
  }
}




void pid_control() {
  readIR_map();


  //goes off motor values that are good enough for short times goind blind
  //ends the pid control function here
  if (hasleftwall() != true || hasrightwall() != true) {
    motor_left = base_speed;
    motor_right = base_speed - 20;
    return;
  }
  regulateSensorL();
  regulateSensorR();


  reset_error ++;
  //resets reset error which is used for i part of pid  which takes in error from previous cycles
  if (reset_error > 10000) {
    reset_error = 0;
    error_buildup = 0;
  }

  //too close left
  if (sensorReading_left > sensorReading_right) {
    //error value
    error = abs(sensorReading_left - sensorReading_right);

    //p control 
    p_control = error * kp;


    //i control
    error_buildup += error;
    i_control = error_buildup * ki;

    
    //d control
    prev_error = error;
    d_control = (error - prev_error) * kd;

    
    //maybe try instead of making motor left and right base_speed - pid values 
    //try motor_l + pid_values and motor_r - pid values
      
    motor_left = base_speed;
    motor_right = base_speed - (p_control + i_control + d_control); 
    return;
  }

  //too close right
  if (sensorReading_right > sensorReading_left) {

    //error value
    error = abs(sensorReading_left - sensorReading_right);
    

    //p control 
    p_control = error * kp;

    //i control
    error_buildup += error;
    i_control = error_buildup * ki;


    //d control
    prev_error = error;
    d_control = (error - prev_error) * kd;



    //maybe try instead of making motor left and right base_speed - pid values 
    //try motor_l - pid_values and motor_r + pid values
      
    motor_left = base_speed - (p_control + i_control + d_control); 
    motor_right = base_speed;
    return;
  }
}


void go_one_cell() {
  unsigned long curr = left_count;//935
  while (left_count - curr < 945 ) { // 450,600, 800,950,900,960,955,945,950,945,930,925,940
    readIR_map();
    print_encoder_count();
    pid_control();


    forward(motor_left, motor_right);
  }
}

void halt_until(int stop_time ) {
  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
    halt();
  }
}//PID / ERROR_CATCHING


//does move based on sensor data
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
    //right_turn_until();
    right_with_wall();
    halt_until(halt_delay);

    return;
  }
  //this isnt running //hopefully it runs now //STILL NOT RUNNING //It WORKS NOW
  else if (hasrightwall()  && !hasleftwall() && hasfrontwall()) { //|| (hasfronwall() &&(hasrightwall - hasleftwall > 200) ){//
    halt_until(halt_delay);
    forward_until(125, 125, 100);
    halt_until(halt_delay);
    //left_turn_until();
    left_with_wall();
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
      //right_turn_until();
      right_with_wall();
      halt_until(halt_delay);
      return;
    }
    else {
      halt_until(halt_delay);
      forward_until(125, 125, 100);
      halt_until(halt_delay);
      //left_turn_until();
      left_with_wall();
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




//this only happens I think when the sensor readings are the same for multiple cycles 
//which usually indicates the mouse is stuch somehow
//should not need if new mouse is done right
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










