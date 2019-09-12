//Reads Ir sensors but with no mapped values
void readIR(){

  digitalWrite(sensor_left_power,LOW);
  digitalWrite(sensor_right_power,LOW);
  digitalWrite(sensor_middle_power,LOW);
  //digitalWrite(sensor_middle_right_power,LOW);
  
  
  digitalWrite(sensor_45_right_power,LOW);
  digitalWrite(sensor_45_left_power,LOW);
  delay(50);
  error_left = analogRead(sensor_left);
  error_middle = analogRead(sensor_middle);
  error_back = analogRead(sensor_back);
  error_right = analogRead(sensor_right);
 
  error_45_left = analogRead(sensor_45_left);
  error_45_right = analogRead(sensor_45_right);

  digitalWrite(sensor_left_power,HIGH);
  digitalWrite(sensor_right_power,HIGH);
  digitalWrite(sensor_middle_power,HIGH);
  digitalWrite(sensor_back_power,HIGH);
  
  digitalWrite(sensor_45_right_power,LOW);
  digitalWrite(sensor_45_left_power,LOW);



  delay(50);
  sensorReading_left = analogRead(sensor_left);
  sensorReading_middle = analogRead(sensor_middle);
  sensorReading_back = analogRead(sensor_back);
  sensorReading_right = analogRead(sensor_right);
  
  
  digitalWrite(sensor_left_power,LOW);
  digitalWrite(sensor_right_power,LOW);
  digitalWrite(sensor_middle_power,LOW);
  digitalWrite(sensor_back_power,LOW);
  
  digitalWrite(sensor_45_right_power,HIGH);
  digitalWrite(sensor_45_left_power,HIGH);

  delay(50);
  sensorReading_45_left = analogRead(sensor_45_left);
  sensorReading_45_right = analogRead(sensor_45_right);
//  
  digitalWrite(sensor_left_power,LOW);
  digitalWrite(sensor_right_power,LOW);
  digitalWrite(sensor_middle_power,LOW);
  digitalWrite(sensor_back_power,LOW);
  
  
  digitalWrite(sensor_45_right_power,LOW);
  digitalWrite(sensor_45_left_power,LOW);
//  

  Serial.print("Sensor Reading without Minus Errors: ");
  Serial.println( "LEFT : ");
  Serial.println(sensorReading_left);
  Serial.print( "MIDDLE : ");
  Serial.println(sensorReading_middle);
  Serial.print( "BACK : ");
  Serial.println(sensorReading_back);
  
  Serial.print( "RIGHT : ");
  Serial.println(sensorReading_right);

  
  Serial.print( "45_LEFT : ");
  Serial.println(sensorReading_45_left);
  
  Serial.print( "45_RIGHT : ");
  Serial.println(sensorReading_45_right);

  sensorReading_left -= error_left;
  sensorReading_middle -= error_middle;
  sensorReading_back -= error_back;
  sensorReading_right -= error_right;
  
  sensorReading_45_left -= error_45_left;
  sensorReading_45_right -= error_45_right;


  Serial.println("Sensor Reading with Minus Errors: ");
  Serial.print( "LEFT : ");
  Serial.println(sensorReading_left);
  Serial.print( "MIDDLE : ");
  Serial.println(sensorReading_middle);
  Serial.print( "BACK : ");
  Serial.println(sensorReading_back);
  Serial.print( "RIGHT : ");
  Serial.println(sensorReading_right);
  
  //sensorReading_45_right -= 20;
  Serial.print( "45_LEFT : ");
  Serial.println(sensorReading_45_left);
  
  Serial.print( "45_RIGHT : ");
  Serial.println(sensorReading_45_right);


// 
//  Serial.println("ERRORS");
//  Serial.println(error_left);
//  Serial.println(error_middle);
//  Serial.println(error_right);
//  Serial.println(error_45_right);
//  Serial.println(error_45_left);
//    
  //*/
  //Serial.println();
}



//HAS functions should be checked before every single comp
//has functions are changed so they take multiple readings and take 
// the avg of them to make sure the readings are as accurate as possible

//NEW HAS FUNCTION THAT DOES ALL OF THEM IN ONE FUNCTION TO SAVE TIME

void has_walls(){

for(int x = 0; x < 10; x++){
  readIR();
  avg_front_wall_reading += sensorReading_middle;  
  avg_left_wall_reading += sensorReading_left;
  avg_right_wall_reading += sensorReading_right; 
  avg_45_left_wall_reading += sensorReading_45_left;  
  avg_45_right_wall_reading += sensorReading_45_right;  
  avg_back_wall_reading += sensorReading_back;  
  
  }
  avg_front_wall_reading /= 10;
  avg_left_wall_reading /= 10;
  avg_right_wall_reading /= 10;
  avg_45_left_wall_reading /= 10;
  avg_45_right_wall_reading /= 10;
  avg_back_wall_reading /= 10;

  
//front_wall         
  if (avg_front_wall_reading > 80 ) { //  
    front_wall = true;
    
  }
  else{
    front_wall = false;
  }

//left_wall
  if (avg_left_wall_reading > 80 ) { //
    left_wall = true;
    
  }
  else{
    left_wall = false;
  }

//right_wall
  if (avg_right_wall_reading > 80 ) { //
    right_wall = true;
    
  }
  else{
    right_wall = false;
  }
  

//45_left_wall
  if (avg_45_left_wall_reading > 80 ) { //32
    left_45_wall = true;
    
  }
  else{
    left_45_wall = false;
  } 
  
//45_back_wall
  if (avg_45_right_wall_reading > 80) { //32 
    right_45_wall = true;
    
  }
  else{
    right_45_wall = false;
  }

//back_wall
  if (avg_back_wall_reading > 80){
    back_wall = true;
    
  }
  else{
    back_wall = false;
  }

  
}



void testIR(){
//  digitalWrite(sensor_left_power,HIGH);
//  sensorReading_left = analogRead(sensor_left);
// // Serial.println("SensorReading");
//  Serial.println(sensorReading_left);
////  Serial.print("HELLOOOO");
// // delay(2000);

  digitalWrite(sensor_back_power,HIGH);
  sensorReading_back = analogRead(sensor_back);
  Serial.println("SensorReading");
  Serial.println(sensorReading_back);
  delay(2000);
}




//code to show to not start until hand is shown
//modified it because of accuracy changes to has wall functions
void wait_until_start_hand(){

  while (first_check) {
    readIR();
    //readIR_map();
    //delay(500);
    //has_front_wall();
    
    if (sensorReading_middle > 100) {
      first_check = false;
      delay(500);
      Serial.println(sensorReading_middle);
      prev_sensorReading_left = sensorReading_left;
      prev_sensorReading_middle = sensorReading_middle;
      prev_sensorReading_right = sensorReading_right;
      prev_encoder_tick = left_count;
      prev_timer = millis();
    }
  }
  return;
}




