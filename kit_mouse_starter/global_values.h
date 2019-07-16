//file for all global variables

unsigned long halt_delay = 400;//350,300


unsigned long prev_encoder_tick;
unsigned long curr_timer;
bool error_check;
unsigned long prev_timer = 0;
const long error_check_interval = 8000;//12000


bool first_check = true;



//GLOBAL FOR PID


int random_choice = 0;


double base_speed =95 ; // 200,150,125,150,200,150,125,100,80,90,88
double kp = 0.10;//0.50,0.030,0.50, 0.90,0.40,0.36,0.30,0.20
double kd = 0.10;//0.40,030
double ki = 0.00001;
double error = 0;
double prev_error = 0;
double p_control = 0;
double d_control = 0;
double i_control = 0;

unsigned long error_buildup;

double reset_error = 0;


int middle_point_l = 42;//31,34,36,34,40,37
int middle_point_90_l = 40;
//double base_speed = 200; // 200,150,125,150
double kp_l = 0.20;//0.40,0.30,0.40,0.30
double kd_l = 0.20;//0.40,0.30
double ki_l = 0.00001;
double error_l = 0;
double prev_error_l = 0;
double p_control_l = 0;
double d_control_l = 0;
double i_control_l = 0;
unsigned long error_buildup_l;
double reset_error_l = 0;


int middle_point_r = 48;//38,40,50,45
int middle_point_90_r = 40;

double kp_r = 0.50;//0.40,0.30
double kd_r = 0.20;//0.40 0.30
double ki_r = 0.00001;
double error_r = 0;
double prev_error_r = 0;
double p_control_r = 0;
double d_control_r = 0;
double i_control_r = 0;
unsigned long error_buildup_r;
double reset_error_r = 0;


///////////////////////////////////
//double motor_left = 125;
//double motor_right = 125;
double motor_left = base_speed;
double motor_right = base_speed;


//Motor
int motor_1_logic_1 = 20;
int motor_1_logic_2 = 21;

int motor_2_logic_1 = 5;
int motor_2_logic_2 = 6;

int turn_on_en_1 = 12;
int turn_on_en_2 = 13;


//encoder
int RH_ENCODER_A = 9;
int RH_ENCODER_B = 8;

int LH_ENCODER_A = 10;
int LH_ENCODER_B = 11;

unsigned long left_count = 0;
//long left_count_pid = 0;
unsigned long right_count = 0;
//long right_count_pid = 0;
//unsigned long reverse_count = 0;


//IRLED
int left_offset = 20; // last value was 15 , 5 , 30, 10

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







//prev led values
int prev_sensorReading_right;
int prev_sensorReading_middle;
int prev_sensorReading_left;


int error_left;
int error_middle;
int error_back;
int error_right;
int error_45_left;
int error_45_right;



//correct variable
bool can_correct = 0;

//gryo values 

LSM6 gyro;
double gyro_dps; //degrees per second
double gyro_raw_data;
signed long gyro_sum = 0;
signed long gyro_angle = 0;
double gyro_raw_dps_conversion_factor = 8.75;
double gyro_reset_limit = 1000;

//accelerometer values
double accel_raw_data;
double accel_force_conversion_factor = 0.061;
double accel_force_data;



//accelerometer distance values
double accel_raw_dist_data;
double accel_dist_conversion_factor = 0.061;
double accel_dist_data;
double accel_velocity;
double accel_distance;
double g_conv_factor= 9.81;








