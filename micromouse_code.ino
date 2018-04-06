//TO DO DO PID  
//CHANGE FORWARD TO ANALOG WRITE (WITH TWO PARAMETERS)

//GLOBAL
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





void setup() {
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

void calibrate(){
permReading_left = analogRead(sensor_left);
permReading_middle= analogRead(sensor_middle);
permReading_right= analogRead(sensor_right);


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



void loop() {
}
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


void forward(int left_speed,int right_speed){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  analogWrite(motor_1_logic_1,left_speed);
  digitalWrite(motor_1_logic_2,LOW);
  analogWrite(motor_2_logic_1,right_speed);
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


/*
//Global variables;
int left_reciever = A0;
int right_reciever = A1;
int front_reciever = A2;
int leftSensor;
int rightSensor;
int frontSensor;
int errorP;
int errorD;

void setup(){
pinMode(left_reciever,INPUT);
pinMode(right_reciever,INPUT);
pinMode(front_reciever,INPUT);

}

void readSensor(){
    leftSensor = analogRead(left_reciever);
    rightSensor = analogRead(right_reciever);
    frontSensor = analogRead(front_reciever);
    
}

void PID(void)
{
    if((leftSensor > hasLeftWall && rightSensor > hasRightWall))//has both walls
    {  //ccw direction is positive
        errorP = rightSensor – leftSensor – 63;//63 is the offset between left and right sensor when mouse in the middle of cell
        errorD = errorP – oldErrorP;
    }
    else if((leftSensor > hasLeftWall))//only has left wall
    {
        errorP = 2 * (leftMiddleValue – leftSensor);
        errorD = errorP – oldErrorP;
    }
    else if((rightSensor > hasRightWall))//only has right wall
    {
        errorP = 2 * (rightSensor – rightMiddleValue);
        errorD = errorP – oldErrorP;
    }
    else if((leftSensor < hasLeftWall && rightSensor <hasRightWall))//no wall, use encoder or gyro
    {
        errorP = 0;//(leftEncoder – rightEncoder*1005/1000)*3;
        errorD = 0;
    }
    totalError = P * errorP + D * errorD;
    oldErrorP = errorP;
    setLeftPwm(leftBaseSpeed – totalError);
    setRightPwm(rightBaseSpeed + totalError);
}

*/

