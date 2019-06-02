

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
  gyro_dps = (gyro_raw_data * gyro_raw_dps_conversion_factor) / 1000; //divided by 1000 because if not it's in mdps
  gyro_sum += (gyro_dps /50); // divided / multipled by 0.05 because thats the sampling period of 50 ms delay
  gyro_angle = gyro_sum; 

  
  //accerlerometer reading
//  accel_raw_data = ((int)gyro.a.z);
//  accel_force_data = (accel_raw_data * accel_force_conversion_factor) / 1000 ;// divided by 1000 because its in mg not g

  //complementary filter
 // gyro_angle = (0.97 * gyro_angle) + (0.03 * accel_force_data);
 
  
  //Serial.print("G ");
  //Serial.print("X: ");
  //Serial.print((int)gyro.g.x);
  //Serial.print(" Y: ");
  //Serial.print((int)gyro.g.y);
  
//  Serial.print("gyro Reading");
//  Serial.print(" Z Raw Data: ");
//  Serial.println(gyro_raw_data);
//  Serial.println(" Z dps: ");
//  Serial.println(gyro_dps);
//  Serial.println("gyro angle");
  Serial.println(gyro_angle);
  //Serial.println("accel force");
  //Serial.println(accel_force_data);  
  
  delay(5);
  //delay(1);
}
//*/


void read_distance(){
  accel_raw_dist_data = ((int)gyro.a.y);
  accel_dist_data = (accel_raw_dist_data * accel_dist_conversion_factor) / 1000; //so it comes to be in g's
  //accel_dist_data *= g_conv_factor; // times 9.81 to turn g's into m/s^2 
  //accel_velocity+= (accel_dist_data); //turns into m/s since its integrated 
  //accel_distance += (accel_velocity ); // turns into m since its integrated

  Serial.println(accel_dist_data);
  //Serial.println(accel_velocity);
  //Serial.println(accel_distance);
  //delay(5);
//    
}


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

