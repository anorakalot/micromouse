//LEFT
int sensor_1 = A2;
int sensorReading_1;

//MIDDLE
int sensor_2 =A4 ;
int sensorReading_2;

//RIGHT
int sensor_3 = A1;
int sensorReading_3;


int motor_1_logic_1 = 3;
int motor_1_logic_2 = 4;

int motor_2_logic_1 = 5;
int motor_2_logic_2 = 10;


int turn_on_en_1 = 22;
int turn_on_en_2 = 23;


int val;


void setup() {
//irled
Serial.begin(9600);
pinMode(sensor_1,INPUT);
pinMode(sensor_2,INPUT);
pinMode(sensor_3,INPUT);

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

void loop() {
}

void printIR(){
  // put your main code here, to run repeatedly:
sensorReading_1 = analogRead(sensor_1);
sensorReading_2 = analogRead(sensor_2);
sensorReading_3 = analogRead(sensor_3);

Serial.print("Sensor Reading: ");
Serial.println(sensorReading_1);
Serial.println(sensorReading_2);
Serial.println(sensorReading_3);
Serial.println();
delay(500);
}

void left_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  digitalWrite(motor_1_logic_1,HIGH);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,HIGH);
  
  
}


void right_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  digitalWrite(motor_1_logic_1,LOW);
  digitalWrite(motor_1_logic_2,HIGH);
  digitalWrite(motor_2_logic_1,HIGH);
  digitalWrite(motor_2_logic_2,LOW);
  
  
}


void forward(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  digitalWrite(motor_1_logic_1,HIGH);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,HIGH);
  digitalWrite(motor_2_logic_2,LOW);
  
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

