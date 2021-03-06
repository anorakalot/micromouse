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
