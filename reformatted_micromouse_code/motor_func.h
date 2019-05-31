


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
  Serial.println();
  Serial.print("right_count");
  Serial.println(right_count);
  Serial.println();
}

//Basic Motor Functions
void forward() {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_2, HIGH);
  digitalWrite(motor_2_logic_1, HIGH);
  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_2_logic_2, LOW);
  
 
}


void reverse() {
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




void halt() {
  digitalWrite(turn_on_en_1, LOW);
  digitalWrite(turn_on_en_2, LOW);

  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_1_logic_2, LOW);
  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, LOW);
}

void halt_until(unsigned long stop_time ) {
  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
    halt();
  }
}



void reverse_turn() {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_1_logic_2, HIGH);

  digitalWrite(motor_2_logic_1, LOW);
  digitalWrite(motor_2_logic_2, HIGH);
}


void left_turn() {
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


  //digitalWrite(motor_1_logic_1, HIGH);
  analogWrite(motor_1_logic_1,255);
  digitalWrite(motor_1_logic_2, LOW);
  //digitalWrite(motor_2_logic_1, HIGH);
  analogWrite(motor_2_logic_1,255);
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

//double check this function I switched which logic is left and which is right
void forward(double left_speed, double right_speed) {


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
  while (  abs(gyro_angle)  <95 ) { //150, 175,120,110,130,90,95
    gyro_tick();
    left_turn();                  //350,360,380,390
  }
  halt_until(halt_delay);
}

////use left_count


void right_turn_until(){//330,240,220
  gyro_angle = 0;
  gyro_sum = 0;
  halt_until(halt_delay);
  while ( abs(gyro_angle)  <95) { //150,175,120,110,130 ,90,95
    gyro_tick();
    right_turn();                  //350,360,380,390
  }
  halt_until(halt_delay);
}



void reverse_turn_until(){//330,240,220
  gyro_angle = 0;
  gyro_sum = 0;

  readIR();
  halt_until(halt_delay);
  if (sensorReading_left > sensorReading_right){
  
  while ( abs(gyro_angle)  < 260) { //350,330,305,305,180,200,230,250,260,255
    gyro_tick();
    right_turn();                  //350,360,380,390
   }
  }

  else if (sensorReading_right > sensorReading_left){
  
  while ( abs(gyro_angle)  < 260) { //350,330,305,305,180,200,230,250,260,255
    gyro_tick();
    left_turn();                  //350,360,380,390
   }
  }

  halt_until(halt_delay);
}

//only uses this forward until function for certain special times when going forward
void forward_until(int left_speed, int right_speed, unsigned long stop_time) {

  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
  digitalWrite(turn_on_en_1, HIGH);
  digitalWrite(turn_on_en_2, HIGH);

//  digitalWrite(motor_1_logic_2,LOW );
//  analogWrite(motor_1_logic_1,left_speed);
//  analogWrite(motor_2_logic_2, right_speed);
//  digitalWrite(motor_2_logic_1, LOW);

  //for mark 4 and above
  analogWrite(motor_1_logic_2, right_speed);
  analogWrite(motor_2_logic_1, left_speed);
  digitalWrite(motor_1_logic_1, LOW);
  digitalWrite(motor_2_logic_2, LOW);
  }
}
void regulateSensor_45_L() {
  //readIR();
  //sensorReading_left = analogRead(sensor_left);
  //sensorReading_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 0, 200);

  //permReading_left = 0 for some reason
  
  //sensorReading_left = sensorReading_left - permReading_left;
  
   
   //if (sensorReading_left - permReading_left < 0){ 
  if (sensorReading_45_left < 0){
    sensorReading_45_left = ~sensorReading_45_left + 1;
  }
//
//   if (sensorReading_left < 0){
//    sensorReading_left = ~sensorReading_left + 1;
//  }
  
}

//gets sensor data from r to use for pid control function
//all it does is take the sensors reading and if its less than 0 make it plus one
//EITHER MAP IN THIS FUNC OR IN READIR
void regulateSensor_45_R() {
  //sensorReading_right = analogRead(sensor_right);
  //readIR();
  
  //sensorReading_right = map(sensorReading_right, 180, 820, 0, 200);

  //sensorReading_right = sensorReading_right - permReading_right;
  
  
    
   //if (sensorReading_right - permReading_right < 0){ 
//  if (sensorReading_45_right < 0){  
//    sensorReading_45_right = ~sensorReading_45_right + 1;
//  }
  if (sensorReading_right < 0){  
    sensorReading_right = ~sensorReading_right + 1;
  }
}

//gets sensor data from l to use for pid control function
//all it does is take the sensors reading and if its less than 0 make it plus one
//EITHER MAP IN THIS FUNC OR IN READIR
void regulateSensorL() {
  //readIR();
  //sensorReading_left = analogRead(sensor_left);
  //sensorReading_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 0, 200);

  //permReading_left = 0 for some reason
  
  //sensorReading_left = sensorReading_left - permReading_left;
  
   
   //if (sensorReading_left - permReading_left < 0){ 
//  if (sensorReading_45_left < 0){
//    sensorReading_45_left = ~sensorReading_45_left + 1;
//  }

   if (sensorReading_left < 0){
    sensorReading_left = ~sensorReading_left + 1;
  }
  
}

//gets sensor data from r to use for pid control function
//all it does is take the sensors reading and if its less than 0 make it plus one
//EITHER MAP IN THIS FUNC OR IN READIR
void regulateSensorR() {
  //sensorReading_right = analogRead(sensor_right);
  //readIR();
  
  //sensorReading_right = map(sensorReading_right, 180, 820, 0, 200);

  //sensorReading_right = sensorReading_right - permReading_right;
  
  
    
   //if (sensorReading_right - permReading_right < 0){ 
//  if (sensorReading_45_right < 0){  
//    sensorReading_45_right = ~sensorReading_45_right + 1;
//  }
  if (sensorReading_right < 0){  
    sensorReading_right = ~sensorReading_right + 1;
  }
}

//TEST THE ENCODER PID 
//in the meantime this will go off good base values
//MAKE THIS LATER INTO TAKE AVERAGE FOR ONE SIDE AND USE THAT PID
//BETTER YET USE PID FOR WHAT THE MIDDLE VALUE FOR A SENSOR SHOULD BE AND THEN USE THAT AS THE ERROR FOR KP KI and KD
void pid_control_one_wall_l() {
  readIR();
  error_l = abs(sensorReading_45_left - middle_point_l);

  p_control_l = error_l * kp_l;

  d_control_l = abs(error_l - prev_error_l) * kd_l;


  if (sensorReading_45_left > middle_point_l){

    motor_left = base_speed + ( p_control_l + d_control_l);
    motor_right = base_speed - (p_control_l + d_control_l);
    prev_error_l = error_l; 
  
  }

  else if (sensorReading_45_left < middle_point_l){
    motor_left = base_speed - (p_control_l + d_control_l);
    motor_right = base_speed + (p_control_l + d_control_l);
    prev_error_l = error_l;
  }
  

  else{
    //nothing
    return;
  }
  
}

void pid_control_one_wall_r() {
  readIR();
  error_r = abs(sensorReading_45_right - middle_point_r);

  p_control_r = error_r * kp_r;

  d_control_r = abs(error_r - prev_error_r) * kd_r;


  if (sensorReading_45_right > middle_point_r){

    motor_left = base_speed - ( p_control_r + d_control_r);
    motor_right = base_speed + (p_control_r + d_control_r);
    prev_error_r = error_r; 
  
  }

  else if (sensorReading_45_right < middle_point_r){
    motor_left = base_speed + (p_control_r + d_control_r);
    motor_right = base_speed - (p_control_r + d_control_r);
    prev_error_r = error_r;
  }
  

  else{
    //nothing
    return;
  }  
   
}

//TEST THE ENCODER PID 
//in the meantime this will go off good base values
//MAKE THIS LATER INTO ENCODER PID
//DOING IT OFF ONLY ENCODERS SUCKS
void pid_control_no_walls() {
//  curr_left_count = left_count;
//  curr_right_count = right_count;
// 
//  reset_error_enc ++;
//  if (reset_error_enc > 10000){
//    reset_error_enc = 0;
//    error_buildup_enc = 0;
//  }
//  
//  error_enc = abs(curr_left_count - curr_right_count);  
//  p_control_enc = error_enc * kp_enc;
//
//  error_buildup_enc += error_enc;
//  i_control_enc = error_buildup_enc * ki_enc;
//
//  
//
//  d_control_enc = abs(error_enc-prev_error_enc) * kd_enc;
//
// if (curr_left_count > curr_right_count){
//   motor_left = base_speed +  (p_control);// + i_control + d_control);
//   motor_right = base_speed  - (p_control);// + i_control + d_control)); 
//  }
// else if (curr_left_count < curr_right_count){
//   motor_left = base_speed -  (p_control) ;//+ i_control + d_control));
//   motor_right = base_speed +  (p_control) ;//+ i_control + d_control);
//  }

  //it works surprisingly well
//  pid_control_two_walls();

   
}

void pid_control_two_90_walls() {
  readIR();


  regulateSensorL();
  regulateSensorR();


  reset_error ++;
  //resets reset error which is used for i part of pid  which takes in error from previous cycles
  if (reset_error > 10000) {
    reset_error = 0;
    error_buildup = 0;
  }
    //error value
    error = abs(sensorReading_left - sensorReading_right);

    //p control 
    p_control = error * kp;


    //i control
    error_buildup += error;
    i_control = error_buildup * ki;

    
    //d control
    
    d_control = abs(error - prev_error) * kd;

    

  //too close left
  if (sensorReading_left > sensorReading_right) {

    //maybe try instead of making motor left and right base_speed - pid values 
    //try motor_l + pid_values and motor_r - pid values
      
    motor_left = base_speed + (p_control);
    motor_right = base_speed - (p_control);//+ i_control + d_control); 
//    motor_left += (p_control + d_control);
//    motor_right -= (p_control + d_control);

//    
    prev_error = error;
    return;
  }

  //too close right
  else if (sensorReading_right > sensorReading_left) {

    


    //maybe try instead of making motor left and right base_speed - pid values 
    //try motor_l - pid_values and motor_r + pid values
      
    motor_left = base_speed - (p_control); //+ i_control + d_control); 
    motor_right = base_speed +  (p_control);
//    motor_left -= (p_control + d_control);
//    motor_right += (p_control + d_control);
    prev_error = error;
    return;
  }

  //equal to each other
  else{
    //nothing
    //motor_left and motor_right stay the same
    prev_error = error;
    return;
  }
  

}
void pid_control_two_45_walls() {
  readIR();


  regulateSensor_45_L();
  regulateSensor_45_R();


  reset_error ++;
  //resets reset error which is used for i part of pid  which takes in error from previous cycles
  if (reset_error > 10000) {
    reset_error = 0;
    error_buildup = 0;
  }
    //error value
    error = abs(sensorReading_45_left - sensorReading_45_right);

    //p control 
    p_control = error * kp;


    //i control
    error_buildup += error;
    i_control = error_buildup * ki;

    
    //d control
    
    d_control = abs(error - prev_error) * kd;

    

  //too close left
  if (sensorReading_45_left > sensorReading_45_right) {
 
      
    motor_left = base_speed + (p_control + d_control); //+ i_control
    motor_right = base_speed - (p_control + d_control); //+ i_control
//    motor_left += (p_control + d_control);
//    motor_right -= (p_control + d_control);

//    
    prev_error = error;
    return;
  }

  //too close right
  else if (sensorReading_45_right > sensorReading_45_left) {

    


      
    motor_left = base_speed - (p_control  + d_control); //+ i_control 
    motor_right = base_speed +  (p_control  + d_control);//+ i_control
//    motor_left -= (p_control + d_control);
//    motor_right += (p_control + d_control);
    prev_error = error;
    return;
  }
  //equal to each other
  else{
    //nothing
    //motor_left and motor_right stay the same
    prev_error = error;
    return;
  }
  
}

//chooses which pid to do
void pid_control(){
  readIR();

  //testing
  //pid_control_two_45_walls();    
 // pid_control_one_wall_l();
  //pid_control_one_wall_r();
  //pid_control_no_walls();

//using 45 deg sensors
     if (has_45_left_wall() == true && has_45_right_wall() == true){
        pid_control_two_45_walls();
      }
      else if (has_45_left_wall() == true &&  has_45_right_wall() == false){
        pid_control_one_wall_l();
      }
      else if (has_45_left_wall() == false && has_45_right_wall() == true){
       pid_control_one_wall_r();
      
      }

      //it works surpisingly well
      else if (has_45_left_wall() && has_45_right_wall() == false){
       // pid_control_no_walls();
      
       //pid_control_two_45_walls();

       pid_control_one_wall_r();
      
         }
      else{
        pid_control_two_45_walls();
      }

//pid_control_two_45_walls();



//using 90 deg sensors 
//  //pid_control_no_walls();
//     if (has_left_wall() == true && has_right_wall() == true){
//        pid_control_two_90_walls();
//      }
//      else if (has_left_wall() == true &&  has_right_wall() == false){
//        pid_control_one_wall();
//      }
//      else if (has_left_wall() == false && has_right_wall() == true){
//       pid_control_one_wall();
//      
//      }
//      else if (has_left_wall() && has_right_wall() == false){
//        pid_control_no_walls();
//      
//         }
//      else{
//        pid_control_two_90_walls();
//      }
  
  return;
}



void go_one_cell(){
 unsigned long curr = millis();
  while (millis() - curr <903 ) { 
   readIR();                   
   // print_encoder_count();
    //pid_control_two_walls();
    //IF PID IS DONE IN A STATE MACHINE I WONT NEED PID IN THIS FUNCTION 
    //HAVING IN STATE MACHINES COULD MEAN I COULD HAVE BETTER READ RESULTS
    //NEED TO MAKE SURE THIS DOESN'T MESS UP CONTROL GOING FORWARD
    pid_control();
    
    forward(motor_left, motor_right);

   
    
  }
  halt_until(halt_delay);
  
//  //off encoders
//  unsigned long curr = right_count;//
//  while (abs(right_count - curr) <912) {//945,400,500,600,650,750,1000,1100,1200  ,1300  , 952 , 930 , 912,908(best so far) , 905 , 890 , 908 
//    readIR();                   //900,500,600,700,800,900,1000,1070,1100, ,1150,1160, 1200 , 1130,1000 , 900    ,1000 , 945  ,800 ,850 , 880 , 885,895 , 915 ,925(over),920(both) , close 905 ,980 ,960(closest)
//   // print_encoder_count();
//    //pid_control_two_walls();
//    //IF PID IS DONE IN A STATE MACHINE I WONT NEED PID IN THIS FUNCTION 
//    //HAVING IN STATE MACHINES COULD MEAN I COULD HAVE BETTER READ RESULTS
//    //NEED TO MAKE SURE THIS DOESN'T MESS UP CONTROL GOING FORWARD
//    pid_control();
//    
//    forward(motor_left, motor_right);
//    //print_encoder_count();
//  }
 
  //testing
//  print_encoder_count();
//  halt();
//  delay(2000);

}



void reverse_until( unsigned long stop_time) {

  unsigned long curr = millis();
  while (millis() - curr < stop_time) {
    pid_control();
    reverse(motor_left,motor_right);

  }
}

//does random move based on sensor data
//void random_move(){
//  int random_move;
//  //readIR_map();
//  readIR();
//  //has to turn cases
//
//  //wall: left , right open: front
//  if (hasleftwall() && hasrightwall() && !hasfrontwall()) {
//    //go_one_cell();
//    return;
//  }
//
//  //wall: left , right , front open: 
//  if (hasleftwall() && hasrightwall() && hasfrontwall()) {
//    halt_until(halt_delay);
//    reverse_until(100);
//    halt_until(halt_delay);
//    reverse_turn_until();
//    halt_until(halt_delay);
//
//
//    return;
//  }
//  
//  //wall: left , front  open: right
//  else if (hasleftwall() && !hasrightwall() && hasfrontwall()) {
//
//    halt_until(halt_delay);
//    reverse_until(100);
//    halt_until(halt_delay);
//    right_turn_until();
//    //right_with_wall();
//    halt_until(halt_delay);
//
//    return;
//  }
//  //wall: right , front open: left
//  else if (hasrightwall()  && !hasleftwall() && hasfrontwall()) { //|| (hasfronwall() &&(hasrightwall - hasleftwall > 200) ){//
//    halt_until(halt_delay);
//    reverse_until( 100);
//    halt_until(halt_delay);
//    left_turn_until();
//    //left_with_wall();
//    halt_until(halt_delay);
//
//    return;
//  }
//
//  //random choice cases
//
//  //
//  //wall: right open: left, front
//  else if (!hasleftwall() && !hasfrontwall() && hasrightwall()) {
//    random_move = random(millis()) % 2;
//    if (random_move == 1) {
//      halt_until(halt_delay);
//      left_turn_until();
//      halt_until(halt_delay);
//      return;
//    }
//    else {
//      //goes straight
//      halt_until(halt_delay);
//      return;
//
//    }
//  }
//
//  //wall: left , open: front , right
//  else if (hasleftwall() && !hasfrontwall() && !hasrightwall() ) {
//    random_move = random(millis()) % 2;
//    if (random_move == 1) {
//      halt_until(halt_delay);
//      right_turn_until();
//      halt_until(halt_delay);
//      return;
//    }
//    else {
//      //goes straight
//      halt_until(halt_delay);
//      return;
//    }
//  }
//
//  //wall: front  open:left , right
//  else if (!hasleftwall() && hasfrontwall() && !hasrightwall())  {
//    random_move = random(millis()) % 2;
//    if (random_move == 1) {
//      halt_until(halt_delay);
//      reverse_until(100);
//      halt_until(halt_delay);
//      right_turn_until();
//      //right_with_wall();
//      halt_until(halt_delay);
//      return;
//    }
//    else {
//      halt_until(halt_delay);
//      reverse_until(100);
//      halt_until(halt_delay);
//      left_turn_until();
//      //left_with_wall();
//      halt_until(halt_delay);
//      return;
//    }
//  }
//  //wall:  open: front , left, right
//  else if (!hasfrontwall() && !hasleftwall() && !hasrightwall()) {
//    random_move = random(millis()) % 3;
//    if (random_move == 1) {
//      halt_until(halt_delay);
//      right_turn_until();
//      halt_until(halt_delay);
//      return;
//    }
//    else if (random_move == 2) {
//      halt_until(halt_delay);
//      return;
//    }
//    else {
//      halt_until(halt_delay);
//      left_turn_until();
//      halt_until(halt_delay);
//      return;
//
//    }
//  }
//
//
//  //in case of errors
//  else {
//    random_move = random(millis()) % 3;
//    if (random_move == 1) {
//      halt_until(700);
//      right_turn_until();
//      halt_until(700);
//      return;
//    }
//    else if (random_move == 2) {
//      halt_until(700);
//      left_turn_until();
//      halt_until(700);
//      return;
//
//    }
//    else {
//      return;
//    }
//
//    //go_one_cell();
//    return;
//  }
//  
//  return;
//
//}




//correct mouse if theirs a front wall in front
//should replace bumping into walls in random_move function
//run pid while reversing so it straightens it self out even more

void correct_mouse_far(){
  readIR();
  
  if (hasfrontwall()){
     
  //82, 
    if (sensorReading_middle <84){
      while(sensorReading_middle < 84){
        
        forward(motor_left,motor_right);
        pid_control();
        readIR();
        Serial.println("FARRRRR");
      }
      halt_until(halt_delay);
    }
    

  }

  //return;
}

void correct_mouse_close(){
readIR();
  if (hasfrontwall()){
     
    
    if (sensorReading_middle > 84){
      while(sensorReading_middle > 84){
        reverse(motor_left,motor_right);
        pid_control();
        readIR();
        Serial.println("CLOSEEEE");
      }
      
      halt_until(halt_delay);
    }

  }
  //return;
  
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
//void error_catch() {
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



//error_check = false;
//MIGHT PUT FLOODFILL INTO THIS STATE MACHINE AS WELL
enum MOTOR_STATES{MOTOR_INIT,GO_ONE_CELL,CHOOSE_MOVE,TURN_REVERSE,TURN_LEFT,TURN_RIGHT } motor_state;
                                      //CORRECT_MOUSE
void motor_init(){
  motor_state = MOTOR_INIT;
}
void motor_tick(){
  
  switch(motor_state){//transitions
    case MOTOR_INIT:
      motor_state = GO_ONE_CELL;
      break;
    case GO_ONE_CELL:
      //motor_state = RANDOM_MOVE;
      //all walls 
      motor_state = CHOOSE_MOVE;
      
      break;

    case CHOOSE_MOVE:
      //structured like a 3 input truth table
      
      readIR();
      //000
      if (hasfrontwall() == false && hasleftwall() == false && hasrightwall() == false){
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
      else if (hasfrontwall() == false && hasleftwall() == false && hasrightwall() == true){
        random_choice = random(millis()) % 2;
        if (random_choice == 0){
          motor_state = GO_ONE_CELL;
        }
        else if (random_choice == 1){
          motor_state = TURN_LEFT;
        }
      }
      //010
      else if (hasfrontwall() == false && hasleftwall() == true && hasrightwall() == false){
        random_choice = random(millis()) % 2;
        if (random_choice == 0){
          motor_state = GO_ONE_CELL;      
        }
        else if (random_choice == 1){
          motor_state = TURN_RIGHT;
        }
      }
      
      //011
      else if (hasfrontwall() == false && hasleftwall() == true && hasrightwall() == true){
        motor_state = GO_ONE_CELL;
      }
      //100
      else if (hasfrontwall() == true && hasleftwall() == false && hasrightwall() == false){
        random_choice = random(millis()) % 2;
        if (random_choice == 0){
          motor_state = TURN_LEFT;
        }
        else if (random_choice == 1){
          motor_state = TURN_RIGHT;
        }
      }
      //101
      else if (hasfrontwall() == true && hasleftwall() == false && hasrightwall() == true){
        motor_state = TURN_LEFT;
      }
      //110
      else if (hasfrontwall() == true && hasleftwall() == true && hasrightwall() == false){
        motor_state = TURN_RIGHT;
      }

      
      //111
      else if (hasfrontwall() == true && hasleftwall() == true && hasrightwall() == true){
        motor_state = TURN_REVERSE;
      }

      

      
      
      
      

      

     
       
      


      
      //nothing else
      else{
        motor_state = GO_ONE_CELL;
      }
      
      //motor_state = REVERSE;
      break;
    
    case TURN_RIGHT:
      motor_state = CHOOSE_MOVE;
      break;
    case TURN_LEFT:
      motor_state = CHOOSE_MOVE;
      break;
    case TURN_REVERSE:
      motor_state = CHOOSE_MOVE;    
      break;
    default:
      motor_state = GO_ONE_CELL;
      break;
  }
  switch(motor_state){//actions
    case MOTOR_INIT:
      break;
    case GO_ONE_CELL:
      go_one_cell();//this calls pid inside of it
      Serial.println("GO_ONE_CELL");
      break;
    case CHOOSE_MOVE:
      //nothing it just chooses move
      break;
    case TURN_REVERSE:
      reverse_turn_until();
      Serial.println("REVERSE");
      break;
    case TURN_LEFT:
      left_turn_until();
      break;
    case TURN_RIGHT:
      right_turn_until();
      break;
  }
  
  
}









