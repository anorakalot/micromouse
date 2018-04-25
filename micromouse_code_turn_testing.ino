bool first_check = true;
int left_offset = 15; // maybe change to 5

//GLOBAL for pid
int permReading_left;
int permReading_middle;
int permReading_right;
int base_speed =150;// 200;
double kp = 0.25;//0.50

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
int sensor_left_power = 2; 


//MIDDLE
int sensor_middle =A4 ;
int sensorReading_middle;
int sensor_middle_power = 7;


//RIGHT
int sensor_right = A1;
int sensorReading_right;
int sensor_right_power = 12;


//int val;




//encoder
int RH_ENCODER_A = 20; 
int RH_ENCODER_B = 21;

int LH_ENCODER_A = 0;
int LH_ENCODER_B = 1;

unsigned long left_count=0;
unsigned long right_count=0;



void setup() {
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_A),left_encoder_event,CHANGE);
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_B),left_encoder_event,CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_A),right_encoder_event,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_B),right_encoder_event,CHANGE);
  
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
  
  //calibrate_pid();
  
}


void loop(){
  print_encoder_count();

/*
  forward();
  //left_turn();
  delay(1000);
  //right_turn();
  halt();
  delay(1000);
  //reverse();
  //delay(1000);
  //halt();
  //delay(1000);
*/

//left_turn();
right_turn();
}

void left_encoder_event() {
  /*
  if (digitalRead(LH_ENCODER_A) == HIGH) {
    if (digitalRead(LH_ENCODER_B) == LOW) {
      left_count++;
    } else {
      left_count--;
    }
  } else {
    if (digitalRead(LH_ENCODER_B) == LOW) {
      left_count--;
    } else {
      left_count++;
    }
  }
  */
  left_count ++;
}

 
// encoder event for the interrupt call
void right_encoder_event() {
  //Serial.println("ASKLHDLAKSJDASLDJ");
   /*
  if (digitalRead(RH_ENCODER_A) == HIGH) {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      right_count++;
    } else {
      right_count--;
    }
  } else {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      right_count--;
    } else {
      right_count++;
    }
  }
  */
  right_count ++;
}


void print_encoder_count(){
  
  Serial.print("left_count");
  Serial.println(left_count);
  Serial.print("right_count");
  Serial.println(right_count);
}





//MOTOR
  

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

void reverse(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);
  
  digitalWrite(motor_1_logic_1,HIGH);
  digitalWrite(motor_1_logic_2,LOW);
  
  digitalWrite(motor_2_logic_1,HIGH);
  digitalWrite(motor_2_logic_2,LOW);
  
} 


void left_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  //halt();
  //delay(50);
  
  analogWrite(motor_1_logic_1,100);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  analogWrite(motor_2_logic_2,100);
  //delay(420);
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
//  delay(860);
  //NOT ON POINT AS MUCH
}

