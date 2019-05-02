

//HAS functions should be checked before every single comp
bool hasfrontwall() {       //200,360
  if (sensorReading_middle > 360 ) { //300 , 350,370,400,275,330,360,500
    return true;//408
  }
  return false;
}

bool hasleftwall() {     //220,450,430,450,430,420 ,320                               //350 maybe a bit too high
  if (sensorReading_left > 525 ) { //100 ,500,300,250,275,400,350,310,320,343,410,420,550,500,600,500,420
    return true;
  }
  return false;
}


bool hasrightwall() {     //220,340,330.300,420,320,330
  if (sensorReading_right > 367 ) { //350 ,500,300,250,275 ,280,320,344,350
    return true;
  }
  return false;
}


//Reads Ir sensors but with no mapped values
void readIR() {

  digitalWrite(sensor_left_power,HIGH);
  digitalWrite(sensor_right_power,HIGH);
  digitalWrite(sensor_middle_power,HIGH);
  
  digitalWrite(sensor_45_right_power,LOW);
  digitalWrite(sensor_45_left_power,LOW);



  delay(50);
  sensorReading_left = analogRead(sensor_left);
  sensorReading_middle = analogRead(sensor_middle);
  sensorReading_right = analogRead(sensor_right);

  
  digitalWrite(sensor_left_power,LOW);
  digitalWrite(sensor_right_power,LOW);
  digitalWrite(sensor_middle_power,LOW);
  
  digitalWrite(sensor_45_right_power,HIGH);
  digitalWrite(sensor_45_left_power,HIGH);

  delay(50);
  sensorReading_45_left = analogRead(sensor_45_left);
  sensorReading_45_right = analogRead(sensor_45_right);
  
  digitalWrite(sensor_left_power,LOW);
  digitalWrite(sensor_right_power,LOW);
  digitalWrite(sensor_middle_power,LOW);
  
  digitalWrite(sensor_45_right_power,LOW);
  digitalWrite(sensor_45_left_power,LOW);
  

  Serial.print("Sensor Reading: ");
  Serial.print( "LEFT : ");
  Serial.println(sensorReading_left);
  Serial.print( "MIDDLE : ");
  Serial.println(sensorReading_middle);
  Serial.print( "RIGHT : ");
  Serial.println(sensorReading_right);

  
  Serial.print( "45_LEFT : ");
  Serial.println(sensorReading_45_left);
  
  Serial.print( "45_RIGHT : ");
  Serial.println(sensorReading_45_right);
  //*/
  //Serial.println();
}



//Reads Ir sensors but with mapped values
void readIR_map() {


  digitalWrite(sensor_left_power, LOW);
  digitalWrite(sensor_middle_power, LOW);
  digitalWrite(sensor_right_power, LOW);
  delay(3);

  error_left = analogRead(sensor_left);
  error_middle = analogRead(sensor_middle);
  error_right = analogRead(sensor_right);
  
  
  
  //probably not use this should probably only use this if anywhere in the calibrate ir func
  //    for(int x = 0; x < 100; ++x){
  //      error_left += analogRead(sensor_left);
  //      error_middle += analogRead(sensor_middle);
  //      error_right += analogRead(sensor_right);
  //    }
  //    error_left = errors_left /100;
  //    error_middle = errors_middle / 100;
  //    error_right = errors_right / 100;


  //PROBABLY NOT USE THIS//error_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 180, 820);
  //PROBABLY NOT USE THIS//error_left -= left_offset;
  //delay(1000);

  digitalWrite(sensor_left_power, HIGH);

  digitalWrite(sensor_middle_power, HIGH);

  digitalWrite(sensor_right_power, HIGH);
  delay(10);



  sensorReading_left = analogRead(sensor_left);
  sensorReading_middle = analogRead(sensor_middle);
  sensorReading_right = analogRead(sensor_right);
  
  //don't know why its not subtracting the error
  //
  //  sensorReading_left -= error_left;
  //  sensorReading_middle -= error_middle;
  //  sensorReading_right -= error_right;




  //991,992                                                                               //820
  sensorReading_left = map(sensorReading_left, left_ir_low_bound, left_ir_high_bound, 352, 860 );
  //sensorReading_left -= left_offset;


  sensorReading_left = abs(sensorReading_left);
  sensorReading_right = abs(sensorReading_right);
  sensorReading_middle = abs(sensorReading_middle);


  Serial.println("ERRORS");
  Serial.println(error_left);
  Serial.println(error_middle);
  Serial.println(error_right);

  Serial.print("Sensor Reading: ");
  Serial.print( "LEFT : ");
  Serial.println(sensorReading_left);
  Serial.print( "MIDDLE : ");
  Serial.println(sensorReading_middle);
  Serial.print( "RIGHT : ");
  Serial.println(sensorReading_right);
  Serial.println();


}
//code to show to not start until hand is shown
void wait_until_start_hand() {

  while (first_check) {
    //readIR();
    //readIR_map();
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



void ir_start_func(){
  for(int x = 0; x < 10; ++x){
        digitalWrite(sensor_left_power,LOW);
        digitalWrite(sensor_right_power,LOW);
        digitalWrite(sensor_middle_power,LOW);
  
        digitalWrite(sensor_45_right_power,LOW);
        digitalWrite(sensor_45_left_power,LOW);
        delay(90);
        error_left = analogRead(sensor_left);
        error_middle = analogRead(sensor_middle);
        error_right = analogRead(sensor_right);
        error_45_left = analogRead(sensor_45_left);
        error_45_right = analogRead(sensor_45_right);

        Serial.println("ERRORS");
        Serial.println(error_left);
        Serial.println(error_middle);
        Serial.println(error_right);
  }
}

//try having more of a delay between digital write high and analog reading the sensor
//putting digital write high power in previous state action 
void read_one_ir(int sensor_power, int sensorReading, int sensor, int error_val,String side_on){
        //digitalWrite(sensor_power,HIGH);
        sensorReading = analogRead(sensor);
        Serial.print("Sensor Reading ");
        Serial.println(side_on);
        Serial.println(sensorReading);

        Serial.print("Error val ");
        Serial.println(side_on);
        Serial.println(error_val);
        
        sensorReading -= error_val;
        digitalWrite(sensor_power,LOW);
        

  
}

//just use readIR for now
//making into a state machine could just overcomplicate things
/*
enum IR_STATES {IR_INIT,IR_START, LEFT_SENSOR,RIGHT_SENSOR,MIDDLE_SENSOR,LEFT_45_SENSOR,RIGHT_45_SENSOR} ir_state; 

void ir_init(){
  ir_state = IR_INIT;
}
void ir_tick(){
    switch(ir_state){ // transitions
      case IR_INIT:
        ir_state = IR_START;
        break;
      case IR_START:
        ir_state = LEFT_SENSOR;
        break;
       case LEFT_SENSOR:
        //ir_state = MIDDLE_SENSOR;
        ir_state = LEFT_SENSOR;
        break;
       case MIDDLE_SENSOR:
        ir_state = RIGHT_SENSOR;
        break;
       case RIGHT_SENSOR:
        ir_state = LEFT_45_SENSOR;
        break;
       case LEFT_45_SENSOR:
        ir_state = RIGHT_45_SENSOR;
        break;
       case RIGHT_45_SENSOR:
        ir_state = LEFT_SENSOR; 
        break;
       default:
        ir_state = IR_INIT;
        break;
       
    }
    //maybe put in for left sensor onwards 
    //turn off power in next state
    switch(ir_state){ // actions
      case IR_INIT:
        break; 
      case IR_START:
        ir_start_func();
        sensor_left_power = HIGH;
       case LEFT_SENSOR:
        read_one_ir(sensor_left_power, sensorReading_left, sensor_left, error_left,left_side_string);
        sensor_left_power = HIGH;
        break;
       case MIDDLE_SENSOR:
        read_one_ir(sensor_middle_power, sensorReading_middle, sensor_middle, error_middle,middle_side_string);
        break;
       case RIGHT_SENSOR:
        read_one_ir(sensor_right_power, sensorReading_right, sensor_right, error_right,right_side_string);
        break;
       case LEFT_45_SENSOR:
        read_one_ir(sensor_45_left_power, sensorReading_45_left, sensor_45_left, error_45_left,left_45_side_string);
        break;
       case RIGHT_45_SENSOR:
        read_one_ir(sensor_45_right_power, sensorReading_45_right, sensor_45_right,error_45_right,right_45_side_string);
        break;
        
    }



}
*/

