
//DO NOW
//TO DO CALIBRATE GO ONE CELL
//TEST RANDOM MOVE CASES

//MAKE PID MORE ACCURATE
//FIX LED RANGE FOR HAS FUNCTIONS


//MAKE PID ON AND OFF

//STATE MACHINES 
//ENUM

//CALIBRATION PID DOESNT HELP


bool first_check = true;
int left_offset = 20; // last value was 15 , 5 , 30, 10

//GLOBAL for pid
int permReading_left;
int permReading_middle;
int permReading_right;
int base_speed =125;// 200,150
double kp = 0.25;//0.50

double prev_motor_left = 125;
double prev_motor_right = 125;

//Motor 
int motor_1_logic_1 = 3;
int motor_1_logic_2 = 4;

int motor_2_logic_1 = 5;
int motor_2_logic_2 = 10;

int turn_on_en_1 = 22;
int turn_on_en_2 = 23;


//encoder
int RH_ENCODER_A = 20; 
int RH_ENCODER_B = 21;

int LH_ENCODER_A = 0;
int LH_ENCODER_B = 1;

unsigned long left_count=0;
unsigned long right_count=0;



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
  
  calibrate_pid();


  while(first_check){
  //readIR();
  readIR_map();
  //delay(500);

  if (sensorReading_middle > 300){
    first_check = false;
    //delay(300);
    ////*
    unsigned long curr = millis();
    while (millis() - curr < 500){
    //nothing (just waiting for 500 seconds to pass
    }
   }
   //*/
   //delay(300);
  }

  //}
}

//encoder and turns
void left_encoder_event() {
left_count ++;
}

 
// encoder event for the interrupt call
void right_encoder_event() {
right_count ++;
}



void print_encoder_count(){
  
  Serial.print("left_count");
  Serial.println(left_count);
  Serial.print("right_count");
  Serial.println(right_count);
}

void left_turn_until(){
  unsigned long curr = left_count;
  while( left_count - curr < 300){//380 330 ,280,290
    left_turn();
  }
}
//use left_count
void right_turn_until(){
  unsigned long curr = left_count;
  while( left_count - curr < 260){ //320,340, 370,300,290,280,270
    right_turn();
  }
}



void reverse_turn_until(){
  unsigned long curr_l = left_count;
  //use left_count instead of right_count
  unsigned long curr_r = left_count;
  
 if (sensorReading_left < sensorReading_right){
  while( left_count - curr_l < 790){ //800,830, 860,870
    left_turn();
 }
 
}

  else{//use left_count instead of right_count
    while( left_count - curr_r < 790){ //800,830, 860,870
      right_turn();
    }
       
  }
 
}

void go_one_cell(){
  unsigned long curr = left_count;
  while(left_count-curr < 950){ // 450,600, 800,950,900
    pid_control();
    //forward(150,150);
  }
}


void halt_until(int stop_time ){
 unsigned long curr = millis();
  while (millis() - curr < stop_time){
    halt();
  } 
}

//CALIBRATION
void calibrate_pid(){
/*
permReading_left = analogRead(sensor_left);
permReading_middle= analogRead(sensor_middle);
permReading_right= analogRead(sensor_right);

//map left and right
permReading_left = map(permReading_left,993,1009,0,200);
permReading_right = map(permReading_right,180,820,0,200);
*/
///*
permReading_left = 0;
permReading_middle= 0;
permReading_right= 0;
//*/

//trying to get readings to be the same 

//permReading_left -= left_offset;


}



//CHOICES
bool hasfrontwall(){
  if (sensorReading_middle >370){ //300 , 350,370,400,275,330,360
    return true;
  }
  return false;
}

bool hasleftwall(){
  if (sensorReading_left >350){ //100 ,500,300,250,275,400
      return true;
  }
  return false;
}


bool hasrightwall(){
  if (sensorReading_right >275){//350 ,500,300,250 
      return true;
  }
  return false;
}

//possibly change so in main loop this only runs if hasfrontwall returns true 
void random_move(){
  int random_move;
  //has to turn cases
    if (hasleftwall() && hasrightwall() && hasfrontwall()){
      reverse_turn_until();
      return;
    }
    else if (hasleftwall() && !hasrightwall() && hasfrontwall()){
      right_turn_until();
      return;
    }
    //this isnt running 
    else if (hasrightwall()  && hasfrontwall()&& !hasleftwall()){//
      left_turn_until();
      return;
    }

    //random choice cases 

    // 
    
    else if (!hasleftwall()&& !hasfrontwall() && hasrightwall())  {
      random_move = random(millis()) % 2;
      if (random_move = 1){
        left_turn_until();
        return;
      }
      else{
      //goes straight
        return;
        
      }
    } 

    
    else if (hasleftwall()&& !hasfrontwall() && !hasrightwall() ) {
      random_move = random(millis()) % 2;
      if (random_move = 1){
        right_turn_until();
        return;
      }
      else{
      //goes straight
        return;
        
      }
    } 

    else if (!hasleftwall()&& hasfrontwall() && !hasrightwall())  {
      random_move = random(millis()) % 2;
      if (random_move = 1){
        right_turn_until();
        return;
      }
      else{
        left_turn_until();
        return;
        
      }
    }

    return;
  
}
  
  
  
  
void loop(){
  /*
 
  reverse_turn();
  halt();
  delay(500);
  */
  
///*




//forward(100,100);
  pid_control();
  //go_one_cell();
  //halt_until(700);
  //go one cell now uses pid control too   

//  readIR();
  
  readIR_map();
  //delay(500);

  //NEW LOOP
  //go up one cell
  //go_one_cell
  //if wall / opening
  //random_move(); 

  
  if (hasfrontwall()){
   halt_until(1000);
   //right_turn_until();
   //left_turn_until();
   random_move(); 
   //reverse_turn_until();
   halt_until(1000);
    
  }
  //*/
 

/*
readIR_map();
//readIR();
delay(500);
//forward(base_speed, base_speed);;
*/
/*
go_one_cell();
//delay(1000);
halt_until(1000);
*/
/*
right_turn_until();
halt_until(1000);
*/
//pid_control();
//forward(200,200);
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
//sensorReading_left = map(sensorReading_left, 993,1009,0,100);
//sensorReading_right = map(sensorReading_left, 194,820,0,100);
  
  
/*
  Serial.println(map(sensorReading_left,993,1008,0,100));
  Serial.println(map(sensorReading_right,194,820,0,100));
*/

//right on point 
//left not as on point 
  
  //sensorReading_left = map(sensorReading_left,993,1009,0,200);

  //CURRENT TRY TO MAP LEFT READING TO RIGHT SENSOR READING RANGE (180 - 820)
  sensorReading_left = map(sensorReading_left,991,1005,180,820);
                                             //991,992
  sensorReading_left -= left_offset;
  
  //sensorReading_right = map(sensorReading_right,180,820,0,200);


  Serial.print("Sensor Reading: ");
  Serial.print( "LEFT : ");
  Serial.println(sensorReading_left);
  Serial.print( "MIDDLE : ");
  Serial.println(sensorReading_middle);
  Serial.print( "RIGHT : ");
  Serial.println(sensorReading_right);
  Serial.println();

}



//PID

void regulateSensorL(){
  /*
    
   readIR_map();
  if (!hasleftwall || !hasrightwall){
    forward(prev_motor_left,prev_motor_right);
    return;
  }
  */
  sensorReading_left = analogRead(sensor_left);
  
  //sensorReading_left = map(sensorReading_left,993,1009,0,200);
  sensorReading_left = map(sensorReading_left,991,1005,0,200);
  sensorReading_left -= left_offset;
  
  sensorReading_left = sensorReading_left- permReading_left;
  if (analogRead(sensor_left) - permReading_left < 0){
    sensorReading_left = ~sensorReading_left + 1;
  }  
  
} 

void regulateSensorR(){
  /*
  readIR_map();
  if (!hasleftwall || !hasrightwall){
    forward(prev_motor_left,prev_motor_right);
    return;
  }
  */
  sensorReading_right = analogRead(sensor_right);
  
  sensorReading_right = map(sensorReading_right,180,820,0,200);
  
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
    prev_motor_left = base_speed;
    prev_motor_right = base_speed - (( sensorReading_left - sensorReading_right) * kp);
    return;
  }
  
  //too close right
  if (sensorReading_right > sensorReading_left){
    forward(base_speed - ((sensorReading_right - sensorReading_left) * kp),base_speed);
    prev_motor_left = base_speed - ((sensorReading_right - sensorReading_left) * kp);
    prev_motor_right = base_speed;
    return;
  }
  //( sensorReading_left - sensorReading_right)
//(sensorReading_right - sensorReading_left)
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
  
  digitalWrite(motor_1_logic_1,100);
  digitalWrite(motor_1_logic_2,LOW);
  digitalWrite(motor_2_logic_1,LOW);
  digitalWrite(motor_2_logic_2,100);
  //delay(840);
  //840
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
  //delay(420);
  //DELAY ON POINT
}


void right_turn(){
  digitalWrite(turn_on_en_1,HIGH);
  digitalWrite(turn_on_en_2,HIGH);

  //analogWrite(motor_1_logic_2,100);
  //analogWrite(motor_2_logic_1,100);
  
  ///halt();
  //delay(50);
  digitalWrite(motor_1_logic_2,HIGH);
  digitalWrite(motor_2_logic_1,HIGH);
  digitalWrite(motor_1_logic_1,LOW);
  digitalWrite(motor_2_logic_2,LOW);
  //delay(860);
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

