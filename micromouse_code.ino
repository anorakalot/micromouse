//TO DO DO PID  
//CHANGE FORWARD TO ANALOG WRITE (WITH TWO PARAMETERS)

//GLOBAL for pid
int permReading_left;
int permReading_middle;
int permReading_right;
int base_speed = 250;
double kp = 0.25;


//LEFT
int sensor_left = A2;
int sensorReading_left;

//MIDDLE
int sensor_middle =A4 ;
int sensorReading_middle;

//RIGHT
int sensor_right = A1;
int sensorReading_right;


int motor_1_logic_1 = 3;
int motor_1_logic_2 = 4;

int motor_2_logic_1 = 5;
int motor_2_logic_2 = 10;


int turn_on_en_1 = 22;
int turn_on_en_2 = 23;


int val;


void calibrate_pid(){
permReading_left = analogRead(sensor_left);
permReading_middle= analogRead(sensor_middle);
permReading_right= analogRead(sensor_right);


}



void setup() {
 calibrate_pid();
 //calibrate
//irled
Serial.begin(9600);
pinMode(sensor_left,INPUT);
pinMode(sensor_middle,INPUT);
pinMode(sensor_right,INPUT);

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

}

bool hasfrontwall(){
  if (sensorReading_middle >50){ //100){
    return true;
  }
  return false;
}

bool hasleftwall(){
  if (sensorReading_left >910){ //100) {
      return true;
  }
  return false;
}


bool hasrightwall(){
  if (sensorReading_right >50){ //100) {
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
  if (sensorReading_left > sensorReading_right){
    forward(base_speed,base_speed - (( sensorReading_left - sensorReading_right) * kp));
  }
  if (sensorReading_right > sensorReading_left){
    forward(base_speed - (( sensorReading_left - sensorReading_right) * kp),base_speed);
  }
}


/*
void loop() {
  printIR();
  delay(1000);
}
*/

void readIR(){
sensorReading_left = analogRead(sensor_left);
sensorReading_middle = analogRead(sensor_middle);
sensorReading_right = analogRead(sensor_right);
  
}




void printIR(){
  // put your main code here, to run repeatedly:
sensorReading_left = analogRead(sensor_left);
sensorReading_middle = analogRead(sensor_middle);
sensorReading_right = analogRead(sensor_right);

Serial.print("Sensor Reading: ");
Serial.println(sensorReading_left);
Serial.println(sensorReading_middle);
Serial.println(sensorReading_right);
Serial.println();
delay(500);
}

void reverse_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  halt();
  delay(50);
  
  analogWrite(motor_1_logic_1,100);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,100);
  delay(100);
  
}


void left_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  halt();
  delay(50);
  
  analogWrite(motor_1_logic_1,100);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,100);
  delay(50);
  
}


void right_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  halt();
  delay(50);
  
  digitalWrite(motor_1_logic_1,LOW);
  analogWrite(motor_1_logic_2,100);
  analogWrite(motor_2_logic_1,100);
  digitalWrite(motor_2_logic_2,LOW);
  delay(50);
  
}




void forward(int left_speed,int right_speed){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  analogWrite(motor_1_logic_2,left_speed);
  digitalWrite(motor_1_logic_1,LOW);
  analogWrite(motor_2_logic_2,right_speed);
  digitalWrite(motor_2_logic_1,LOW);
  
}
void loop (){
  ///testing
  //forward(200,200);


  pid_control();

  if (hasfrontwall()){
    random_move();
  }

  readIR();
}

void halt(){
  digitalWrite(turn_on_en_1,LOW);
  digitalWrite(turn_on_en_2,LOW);
  
  digitalWrite(motor_1_logic_1,LOW);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,LOW);
    

}


void reverse(){
  
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  digitalWrite(motor_1_logic_1,LOW);
  digitalWrite(motor_1_logic_2,HIGH);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,HIGH);
  
}


//testing loop
/*
void loop() {
 
forward();
delay(500);
reverse();
delay(500);


}
*/



