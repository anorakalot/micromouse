//FIX TURNS (possibly do while loop until IR read right/ have other functions that call turn until right) 
//FIX PID (possibly map IR values)


bool first_check = true;


//GLOBAL for pid
int permReading_left;
int permReading_middle;
int permReading_right;
int base_speed = 200;
double kp = 0.25;


//Motor 
int motor_1_logic_1 = 3;
int motor_1_logic_2 = 4;

int motor_2_logic_1 = 5;
int motor_2_logic_2 = 10;


int turn_on_en_1 = 22;
int turn_on_en_2 = 23;



//IRLED

//LEFT
int sensor_left = A2;
int sensorReading_left;
int sensor_left_power =2; 


//MIDDLE
int sensor_middle =A4 ;
int sensorReading_middle;
int sensor_middle_power = 7;


//RIGHT
int sensor_right = A1;
int sensorReading_right;
int sensor_right_power = 12;


//int val;




void setup() {
  Serial.begin(9600);
   //calibrate

   
  //irled
  //Serial.begin(9600);
   
  Serial.begin(9600);
  pinMode(sensor_left,INPUT);
  pinMode(sensor_middle,INPUT);
  pinMode(sensor_right,INPUT);
  
  pinMode(sensor_left_power,OUTPUT);
  pinMode(sensor_middle_power,OUTPUT);
  pinMode(sensor_right_power,OUTPUT);
  digitalWrite(sensor_left_power, HIGH);
  
  digitalWrite(sensor_middle_power, HIGH);
  
  digitalWrite(sensor_right_power, HIGH);

  //motors
  // pinMode(turn_on_en_input,INPUT);
  pinMode(turn_on_en_1,OUTPUT);
  pinMode(turn_on_en_2,OUTPUT);
  
  pinMode(motor_1_logic_1,OUTPUT);
  
  pinMode(motor_1_logic_2,OUTPUT);
  
  pinMode(motor_2_logic_1,OUTPUT);
  
  pinMode(motor_2_logic_2,OUTPUT);
  
  digitalWrite(turn_on_en_1,LOW);
  digitalWrite(turn_on_en_2,LOW);



  //sensorReading_middle = 0;
  //readIR();
  
  calibrate_pid();
  
}
//CALIBRATION
void calibrate_pid(){
permReading_left = analogRead(sensor_left);
permReading_middle= analogRead(sensor_middle);
permReading_right= analogRead(sensor_right);


}



//CHOICES
bool hasfrontwall(){
  if (sensorReading_middle >300){ //300){
    return true;
  }
  return false;
}

bool hasleftwall(){
  if (sensorReading_left >1000){ //100) {
      return true;
  }
  return false;
}


bool hasrightwall(){
  if (sensorReading_right >350){ 
      return true;
  }
  return false;
}

//possibly change so in main loop this only runs if hasfrontwall returns true 
void random_move(){
  int random_move;
  //if (hasfrontwall()){
    if (hasleftwall() && hasrightwall()){
      reverse_turn();
    }
    if (hasleftwall() && !hasrightwall()){
      right_turn();
    }
    if (hasrightwall() && !hasleftwall()){
      left_turn();
    }
    else{
      random_move = random(millis()) % 2;
      if (random_move = 1){
        left_turn();
      }
      else{
        right_turn();
      }
    }
  //}


  
}




void loop(){
  /*
 
  reverse_turn();
  halt();
  delay(500);
  */
  
/*
while(first_check){
  readIR();
  //delay(500);

  if (sensorReading_middle > 300){
    first_check = false;
    //delay(300);
  }
}


  pid_control();
  readIR();

  if (hasfrontwall()){
   //halt();
   //delay(1000);
  // delay(3000);
   //right_turn(); 
   //random_move();
    //left_turn();
    //halt();
    //delay(1000);  
  }
*/

readIR_map();
//readIR();
delay(500);

}



//IR 
void readIR(){
  
sensorReading_left = analogRead(sensor_left);
sensorReading_middle = analogRead(sensor_middle);
sensorReading_right = analogRead(sensor_right);

Serial.print("Sensor Reading: ");
Serial.println(sensorReading_left);
Serial.println(sensorReading_middle);
Serial.println(sensorReading_right);
Serial.println();
}


void readIR_map(){
    
sensorReading_left = analogRead(sensor_left);
sensorReading_middle = analogRead(sensor_middle);
sensorReading_right = analogRead(sensor_right);

//sensorReading_left = map(sensorReading_left s
sensorReading_left = map(sensorReading_left, 993,1008,0,100);
sensorReading_right = map(sensorReading_left, 194,820,0,100);


Serial.print("Sensor Reading: ");
Serial.println(sensorReading_left);
Serial.println(sensorReading_middle);
Serial.println(sensorReading_right);
Serial.println();

}



//PID

void regulateSensorL(){
  sensorReading_left = analogRead(sensor_left);
  sensorReading_left = sensorReading_left- permReading_left;
  if (analogRead(sensor_left) - permReading_left < 0){
    sensorReading_left = ~sensorReading_left + 1;
  }  
}
void regulateSensorR(){
  sensorReading_right = analogRead(sensor_right);
  sensorReading_right = sensorReading_right- permReading_right;
  if (analogRead(sensor_right) - permReading_right < 0){
    sensorReading_right = ~sensorReading_right + 1;
  }
}



void pid_control(){
  regulateSensorL();
  regulateSensorR();
  //too close left
  if (sensorReading_left > sensorReading_right){
    forward(base_speed,base_speed - (( sensorReading_left - sensorReading_right) * kp));
  }
  //too close right
  if (sensorReading_right > sensorReading_left){
    forward(base_speed - (( sensorReading_left - sensorReading_right) * kp),base_speed);
  }
}


//MOTORS

void reverse(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  digitalWrite(motor_1_logic_1,HIGH);
  digitalWrite(motor_1_logic_2,LOW);
  
  digitalWrite(motor_2_logic_1,HIGH);
  digitalWrite(motor_2_logic_2,LOW);
  
}

void forward(){
  
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  digitalWrite(motor_1_logic_1,LOW);
  digitalWrite(motor_1_logic_2,HIGH);
  
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,HIGH);
  
}


void halt(){
  digitalWrite(turn_on_en_1,LOW);
  digitalWrite(turn_on_en_2,LOW);
  
  digitalWrite(motor_1_logic_1,LOW);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,LOW);
    

}





void reverse_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  //halt();
  //delay(50);
  
  analogWrite(motor_1_logic_1,100);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,100);
  delay(840);
  
}


void left_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  //halt();
  //delay(50);
  
  digitalWrite(motor_1_logic_1,100);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,100);
  delay(420);
  //DELAY ON POINT
}


void right_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  ///halt();
  //delay(50);
  
  digitalWrite(motor_1_logic_1,LOW);
  analogWrite(motor_1_logic_2,100);
  analogWrite(motor_2_logic_1,100);
  digitalWrite(motor_2_logic_2,LOW);
  delay(860);
  //NOT ON POINT AS MUCH
}


void forward(int left_speed,int right_speed){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  analogWrite(motor_1_logic_2,left_speed);
  digitalWrite(motor_1_logic_1,LOW);
  analogWrite(motor_2_logic_2,right_speed);
  digitalWrite(motor_2_logic_1,LOW);
}
