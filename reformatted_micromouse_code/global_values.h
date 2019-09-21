
unsigned long halt_delay = 200;//350,300,400


unsigned long prev_encoder_tick;
unsigned long curr_timer;
bool error_check;
unsigned long prev_timer = 0;
const long error_check_interval = 8000;//12000


bool first_check = true;



//GLOBAL FOR PID

//probably wont use these 
//int permReading_left;
//int permReading_middle;
//int permReading_right;

int random_choice = 0;


double base_speed =100 ; // 200,150,125,150,200,150,125,100,80,90,88
//made two extra base speeds in order to see if base speeds not being straight enough with equal readings causes pid to fail
double base_speed_l = 100;
double base_speed_r =90 ; // based off testing to see which base_speeds go straightest ,93,94

double kp = 0.10;//0.50,0.030,0.50, 0.90,0.40,0.36,0.30,0.20,0.10,0.05,0.20,
double kd = 0.05;//0.40,0.30,0.05
double ki = 0.00001;
double error = 0;
double prev_error = 0;
double p_control = 0;
double d_control = 0;
double i_control = 0;

unsigned long error_buildup;

double reset_error = 0;


int middle_point_l = 130;//31,34,36,34,40,37,42
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


int middle_point_r = 120;//38,40,50,45,48
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
double motor_left = base_speed_l;
double motor_right = base_speed_r;

///////////////////////////////////
//


//FOR PID ENCODERS
unsigned long curr_left_count;
unsigned long curr_right_count;
//long expec_left_count = 1500;
//long expec_right_count = 1500;

unsigned long curr_left_speed;
unsigned long curr_right_speed;


//need to set these speeds for encoder pid
//test the values to get ones that work best
unsigned long left_wanted_speed = 200;
unsigned long right_wanted_speed = 400;//200

double kp_enc = 0.20;//0.50
double kd_enc = 0.20;//0.30
double ki_enc = 0.0001;

double error_l_enc = 0;
double error_r_enc = 0;

//to keep track of prev count so i can get curr speed
double prev_left_count;
double prev_right_count;

double prev_error_l_enc = 0;
double prev_error_r_enc = 0;

double p_control_enc_l = 0;
double p_control_enc_r = 0;
//
double d_control_enc_l = 0;
double d_control_enc_r = 0;

//Haven't implemented i control in yet
//double i_control_enc_l = 0;
//double i_control_enc_r = 0;
//
//unsigned long error_buildup_enc;
//double reset_error_enc = 0;


//may not need these
//int left_ir_low_bound = 995;
//int left_ir_high_bound = 1009;



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

volatile unsigned long left_count = 0;
//long left_count_pid = 0;
volatile unsigned long right_count = 0;
//long right_count_pid = 0;
//unsigned long reverse_count = 0;

//for go one cell
volatile unsigned long curr_count_cell = 0;


// Motor  Tick Enum States
enum  MOTOR_STATES   {  MOTOR_INIT  ,  GO_ONE_CELL , CHOOSE_MOVE, TURN_REVERSE_L, TURN_REVERSE_R, TURN_LEFT, TURN_RIGHT } motor_state;

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

//Bool for Ir has_wall functions
bool front_wall = 0;
bool left_wall = 0;
bool right_wall = 0;
bool back_wall = 0;
bool left_45_wall = 0;
bool right_45_wall = 0;


//bool for Ir has_wall functions
double avg_front_wall_reading;
double avg_left_wall_reading;
double avg_right_wall_reading;
double avg_back_wall_reading;
double avg_45_left_wall_reading;
double avg_45_right_wall_reading;



////Strings for printing in ir_tick
//String left_side_string = "LEFT:"; 
//String middle_side_string = "MIDDLE:"; 
//String right_side_string = "RIGHT:"; 
//String left_45_side_string = "45_LEFT:"; 
//String right_45_side_string = "45_RIGHT:"; 


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
//I PUT GRYO VARIABLES IN GRYO_FUNC DUE TO ERRORS

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





//bool go_one_cell_happening = 0;


//timer variable
//Timer t;

//FLOODFILL VARIABLES
struct pair{
  int y_pos;
  int x_pos;
};

//floodfill variables
struct cell{
  bool left_wall;
  bool right_wall;
  bool front_wall;
  bool back_wall;
  int value;
  pair coord;
};

//stack pair checks;


pair goal_coord = {8,8};

pair mouse_pos = {0,0};

pair neighbor_to_push;

pair cell_check;

//imagine seeing maze normally from the bottom
//0 for going left
//1 for going to the top
//2 for going to the right
//3 for going to the bottom
int orientation;
int min_val;

const int maze_x_length = 9;
const int maze_y_length = 9;
//idk why this is here but it makes sense since maze is a 2d array
int index_x_max = 8;
int index_y_max = 8;

cell maze[maze_y_length][maze_x_length];

StackArray<pair> checks;





