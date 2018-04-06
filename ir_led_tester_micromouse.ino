//LEFT
int sensor_left = A2;
int sensorReading_left;

//MIDDLE
int sensor_middle =A4 ;
int sensorReading_middle;

//RIGHT
int sensor_right = A1;
int sensorReading_right;

void setup() {
Serial.begin(9600);
pinMode(sensor_left,INPUT);
pinMode(sensor_middle,INPUT);
pinMode(sensor_right,INPUT);
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
