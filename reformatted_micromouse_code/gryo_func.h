
void setup_gryo(){
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
  gryo_raw_data = ((int)gryo.g.z);
  gryo_dps = (gryo_raw_data * gryo_raw_dps_conv_factor) / 1000;
  
  
  //Serial.print("G ");
  //Serial.print("X: ");
  //Serial.print((int)gyro.g.x);
  //Serial.print(" Y: ");
  //Serial.print((int)gyro.g.y);
  Serial.print("Gryo Reading");
  Serial.print(" Z Raw Data: ");
  Serial.println(gryo_raw_data);
  Serial.println(" Z dps: ");
  
  delay(100);
}
