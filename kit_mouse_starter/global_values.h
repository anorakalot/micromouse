

//GLOBAL FOR PID





double base_speed =100 ; // 200,150,125,150,200,150,125,100,80,90,88
//made two extra base speeds in order to see if base speeds not being straight enough with equal readings causes pid to fail
double base_speed_l = 100;
double base_speed_r =90 ; // based off testing to see which base_speeds go straightest ,93,94

double kp = 0.12;//0.50,0.030,0.50, 0.90,0.40,0.36,0.30,0.20,0.10,0.05,0.20,0.10,0.20,0.15,0.10,0.12(good)
double kd = 0.12;//0.40,0.30,0.05,0.10,005,0.08,0.06,0.08,0.10(good)
double ki = 0;//0.00001,0.00001
double error = 0;
double prev_error = 0;
double p_control = 0;
double d_control = 0;
double i_control = 0;

unsigned long error_buildup;

double reset_error = 0;







//Motor
int motor_1_logic_1 = 20;
int motor_1_logic_2 = 21;

int motor_2_logic_1 = 5;
int motor_2_logic_2 = 6;

int turn_on_en_1 = 12;
int turn_on_en_2 = 13;


//encoder
//int RH_ENCODER_A = 9;
//int RH_ENCODER_B = 8;
//
//int LH_ENCODER_A = 10;
//int LH_ENCODER_B = 11;

int RH_ENCODER_A = 10;
int RH_ENCODER_B = 11;

int LH_ENCODER_A = 9;
int LH_ENCODER_B = 8;


volatile unsigned long left_count = 0;
volatile unsigned long right_count = 0;




//IRLED VARS

//LEFT
int sensor_left = A2;
int sensorReading_left;
int sensor_left_power = 0;


//MIDDLE
int sensor_middle = A1 ;
int sensorReading_middle;
int sensor_middle_power = 1;

//BACK
int sensor_back = A3 ;
int sensorReading_back;
int sensor_back_power = 7;

//RIGHT
int sensor_right = A0;
int sensorReading_right;
int sensor_right_power = 2;


//45_DEGREE_LEFT
int sensor_45_left = A9;
int sensorReading_45_left;
int sensor_45_left_power = 4;



//45_DEGREE_RIGHT
int sensor_45_right = A8;
int sensorReading_45_right;
int sensor_45_right_power = 3;










