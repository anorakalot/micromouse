//FIX EVERYTHING IN MICROMOUSE_CODE 
//ESPECIALLY THE IRLED READINGS

bool first_check = true;


//GLOBAL for pid
int permReading_left;
int permReading_middle;
int permReading_right;
int base_speed = 250;
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



void calibrate_pid(){
permReading_left = analogRead(sensor_left);
permReading_middle= analogRead(sensor_middle);
permReading_right= analogRead(sensor_right);


}



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





void loop(){
  
while(first_check){
  readIR();
  //delay(500);

  if (sensorReading_middle > 350){
    first_check = false;
  }
}
/*
readIR();
 //delay(500);

forward();
delay(500);
reverse();
delay(500);
*/

left_turn();

  //pid_control();


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
  if (sensorReading_left > sensorReading_right){
    forward(base_speed,base_speed - (( sensorReading_left - sensorReading_right) * kp));
  }
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
  delay(100);
  
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
  delay(140);
  
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
