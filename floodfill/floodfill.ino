#include <StackArray.h>
#include <cmath>
 


#include <Wire.h>
#include <L3G.h>
#include "global_values.h"
#include "gyro_func.h"
#include "ir_func.h"
#include "motor_func.h"



//FLOODFILL VARIABLES
struct pair{
  int y_pos;
  int x_pos;
};

//floodfill variables
struct cell{
  bool left_wall;
  bool right_wall;
  bool top_wall;
  bool bottom_wall;
  int value;
  pair coord;
  //this bool is so the mouse doesn't go to places it already has been
  //implement into algorithm later after 
  bool visited;
};

int min_val;

//typedef struct Cell cell;
//stack pair checks;

//pair checks [18];
//Stack below compiles but i think doing an array would be better
StackArray <pair> checks;
struct pair goal_coord;

//pair <int,int> goal_coord(4,4);
struct pair mouse_pos;

struct pair cell_check;
struct pair neighbor_to_push;
//pair <int,int> mouse_pos (8,0);

const int maze_x_length = 16;
const int maze_y_length = 16;
int index_x_max = 15;
int index_y_max = 15;

struct cell maze[maze_y_length][maze_x_length];



                                                                                          //FLOODFILL_MOVE_TO_NEXT_SPACE        
enum FLOODFILL_STATES{FLOODFILL_INIT,FLOODFILL_START,FLOODFILL_POS_CHECK,FLOODFILL_STACK_CHECK,FLOODFILL_MOVE_TO_NEXT_SPACE,FLOODFILL_END} floodfill_state;
void floodfill_init(){
  floodfill_state = FLOODFILL_INIT;
}

//stack operations assume the stack works just like a standard c++ stack
void floodfill_tick(){
  switch(floodfill_state){//transitions
    case FLOODFILL_INIT:
      floodfill_state = FLOODFILL_START;
      break;
    case FLOODFILL_START:
      break;
    case FLOODFILL_POS_CHECK:
      if ((mouse_pos.y_pos == goal_coord.y_pos) &&  (mouse_pos.y_pos == goal_coord.y_pos)){
        floodfill_state = FLOODFILL_END;
      }
      else {
        floodfill_state = FLOODFILL_STACK_CHECK;
        //SHOULD PUSH STARTING MOUSE_POS IN FLOODFILL_START INSTEAD SO IT DOESN'T KEEP HAPPENING
        //NEVERMIND THIS NEEDS TO HAPPEN EACH TIME BECAUSE OF HOW IT POPS THE CELL TO CHECK FROM THE CHECKS STACK
        //NEVERMIND TO ABOVE NEVERMIND BECAUSE THE ALGORITHM SAYS DIFFERENTLY
        //NEVERMIND TO ABOVE NEVERMIND BECAUSE DOING IT ON PAPER SAYS DIFFERENTLY
        checks.push(mouse_pos);
        //set minval to -10 so if it stays -10 then we know the cellcheck was correct at first;
        min_val = -10;
      }
      break;
    case FLOODFILL_STACK_CHECK:
      if (checks.count() != 0){
         floodfill_state = FLOODFILL_STACK_CHECK;
         //floodfill_state = FLOODFILL_MOVE_TO_NEXT_SPACE;
      }
      else {
        floodfill_state = FLOODFILL_MOVE_TO_NEXT_SPACE;
        //floodfill_state = FLOODFILL_POS_CHECK;
      }
      break;
    case FLOODFILL_MOVE_TO_NEXT_SPACE:
      floodfill_state = FLOODFILL_POS_CHECK;
      break;
    case FLOODFILL_END:
      break;
    default:
      break;
  }
  switch(floodfill_state){//actions
    case FLOODFILL_INIT:
      break;
     case FLOODFILL_START:
      goal_coord.y_pos = 4;
      goal_coord.x_pos = 4;

      mouse_pos.y_pos = 8;
      mouse_pos.x_pos = 0;

      for (int x = 0; x < maze_x_length; ++x){
        for (int y = 0; y < maze_y_length; ++y){
          //maze[y][x].value = abs(goal_coord.y_pos - mouse_pos.y_pos) + abs(goal_coord.y_pos - mouse_pos.y_pos);
          maze[y][x].value = abs(goal_coord.y_pos - y) + abs(goal_coord.x_pos - x);
        }
      }
      //checks.push(mouse_pos);
      //checks.push(mouse_pos);
      break;
    case FLOODFILL_POS_CHECK:
      break;
    case FLOODFILL_STACK_CHECK:
      cell_check = checks.pop(); // pretty sure this gets and removes from top of stack 
      //if pop doesn't do both does things do checks.peek and the line after do checks.pop

      
      //if left wall is open
      if (hasleftwall() == false){
        //if cell_check is not 1 greater 
        if (maze[cell_check.y_pos][cell_check.x_pos].value  != maze[cell_check.y_pos][cell_check.x_pos-1].value +1  ){
          if (min_val == -10){
             min_val = maze[cell_check.y_pos][cell_check.x_pos-1].value;
          }
          else{
            if (maze[cell_check.y_pos][cell_check.x_pos-1].value < min_val){
              min_val = maze[cell_check.y_pos][cell_check.x_pos-1].value;
            }
          }
          neighbor_to_push.y_pos = cell_check.y_pos;
          neighbor_to_push.x_pos = cell_check.x_pos - 1;
          checks.push(neighbor_to_push);
        }
      }
      
      break;
    case FLOODFILL_END:
      break;
  }
  
}













void setup(){
  //
}

void loop(){
  //
}

