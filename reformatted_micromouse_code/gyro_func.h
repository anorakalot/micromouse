

void setup_gyro(){
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
}




void read_angle(){
  gyro.read();
  gyro_raw_data = ((int)gyro.g.z);
  gyro_dps = (gyro_raw_data * gyro_raw_dps_conversion_factor) / 1000;
  gyro_sum += (gyro_dps /100);
  gyro_angle = gyro_sum; 
  
  
  //Serial.print("G ");
  //Serial.print("X: ");
  //Serial.print((int)gyro.g.x);
  //Serial.print(" Y: ");
  //Serial.print((int)gyro.g.y);
  Serial.print("gyro Reading");
  Serial.print(" Z Raw Data: ");
  Serial.println(gyro_raw_data);
  Serial.println(" Z dps: ");
  Serial.println(gyro_dps);
  Serial.println("gyro angle");
  Serial.println(gyro_angle);
  
  
  delay(100);
}
//*/


enum GYRO_STATES {GYRO_INIT,GYRO_START, GYRO_READ_ANGLE} gyro_state;

void gyro_init(){
  gyro_state = GYRO_INIT;
}
void gyro_tick(){
   switch(gyro_state){
      case GYRO_INIT:
        gyro_state = GYRO_START;
        break;
      case GYRO_START:
        gyro_state = GYRO_READ_ANGLE;
        break;
       case GYRO_READ_ANGLE:
        gyro_state = GYRO_READ_ANGLE;
        break;
       default:
        gyro_state = GYRO_INIT;
        break;

    
   }
   switch(gyro_state){
      case GYRO_INIT:
        break;
      case GYRO_START:
        setup_gyro();
        break;
      case GYRO_READ_ANGLE:
        read_angle();
        break;
   }
}

