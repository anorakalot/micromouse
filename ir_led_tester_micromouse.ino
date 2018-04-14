//992 tr 1000 left
//181 tr 350 middle
//85 tr 150 right(0LD)
//200 tr 350 right

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


void setup() {
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
}
void loop(){
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
