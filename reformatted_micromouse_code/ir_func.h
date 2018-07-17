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


//IR
void readIR() {
  //
  //    digitalWrite(sensor_left_power, LOW);
  //    digitalWrite(sensor_middle_power, LOW);
  //    digitalWrite(sensor_right_power, LOW);
  //    delay(1);
  //    error_left = analogRead(sensor_left);
  //    error_middle = analogRead(sensor_middle);
  //    error_right = analogRead(sensor_right);
  //
  //    digitalWrite(sensor_left_power, HIGH);
  //    digitalWrite(sensor_middle_power, HIGH);
  //    digitalWrite(sensor_right_power, HIGH);
  //    delay(1);
  //    Serial.println("ERRORS");
  //    Serial.println(error_left);
  //    Serial.println(error_middle);
  //    Serial.println(error_right);

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

  digitalWrite(sensor_left_power, LOW);
  digitalWrite(sensor_middle_power, LOW);
  digitalWrite(sensor_right_power, LOW);
  delay(3);
  //    //delay(1000);

  //    int errors_left= 0;
  //    int errors_middle = 0 ;
  //    int errors_right = 0;

  error_left = analogRead(sensor_left);
  error_middle = analogRead(sensor_middle);
  error_right = analogRead(sensor_right);
  error_left -= 921 ;
  //error_left = map(error_left, left_ir_low_bound, left_ir_high_bound, 352, 860 );

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
  delay(3);



  sensorReading_left = analogRead(sensor_left);
  sensorReading_middle = analogRead(sensor_middle);
  sensorReading_right = analogRead(sensor_right);
  //
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

