int halt_delay = 300;//350,300


unsigned long prev_encoder_tick;
unsigned long curr_timer;
bool error_check;
unsigned long prev_timer = 0;
const long error_check_interval = 8000;//12000


bool first_check = true;

//GLOBAL for pid
int permReading_left;
int permReading_middle;
int permReading_right;
int base_speed = 150; // 200,150,125,150
double kp = 0.50;//0.50,0.25,0.30,0.50,0.60
double kd = 0.40;//0.30,0.50,0.30,0.40
double ki = 0.0001;
double error;
double prev_error;
double d_control;

unsigned long error_buildup;
double i_control;
double reset_error = 0;
double motor_left = 125;
double motor_right = 125;

int left_ir_low_bound = 995;
int left_ir_high_bound = 1009;

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

unsigned long left_count = 0;
unsigned long right_count = 0;



//IRLED
int left_offset = 20; // last value was 15 , 5 , 30, 10

//LEFT
int sensor_left = A2;
int sensorReading_left;
int sensor_left_power = 2;


//MIDDLE
int sensor_middle = A4 ;
int sensorReading_middle;
int sensor_middle_power = 7;


//RIGHT
int sensor_right = A1;
int sensorReading_right;
int sensor_right_power = 12;

//prev led values
int prev_sensorReading_right;
int prev_sensorReading_middle;
int prev_sensorReading_left;

int reading_for_no_left;
int reading_for_no_right;

int error_left;
int error_middle;
int error_right;


//int val;


//error catching
//enum catch_states {INIT_CATCH,ON_1,OFF_1} catch_states;

//void catch_init(){
//  catch_states = INIT_CATCH;
//}
//Timer t;

