//next thing to do is code in test mazes using the cell struct below
#include <iostream>
#include <stack>
#include <utility>
#include <cmath>
using namespace std;

struct cell{
	bool left_wall;
	bool right_wall;
	bool top_wall;
	bool bottom_wall;
	int value;
	//pair<int,int> coord;
};

void display_maze();


int main(){
stack <pair<int,int>> checks;

pair <int,int> goal_coord(4,4);
pair <int,int> mouse_pos (8,0);


int maze_x_length = 9;
int maze_y_length = 9;
int index_x_max = 8;
int index_y_max = 8;

cell maze[maze_y_length][maze_x_length];

//set up starting cell values
for (int y =0; y <index_y_max; ++y){
	
	for(int x = 0; x < index_x_max; ++x) {
		maze[y][x].value = abs(goal_coord.first - y) + abs(goal_coord.second-x);
	}
}

for (int y =0; y <index_y_max; ++y){
	
	for(int x = 0; x < index_x_max; ++x) {
		cout << maze[y][x].value<< " ";
	}
	cout << endl;
}

pair<int,int> cellcheck;
bool one_greater;
int minval;
pair<int,int> pair_to_push_to_checks;
bool changed_mouse_pos;

//start of floodfill algorithm
//checks.push(mouse_pos);
while(mouse_pos != goal_coord){
	checks.push(mouse_pos);
	one_greater = false;
	minval = -1;
	changed_mouse_pos = false;
	while(!checks.empty()){
		cellcheck = checks.top();
		checks.pop();
		//assume making maze puts walls for all boundaries 
		if (maze[cellcheck.first][cellcheck.second].left_wall != 1 && one_greater == false){
			if (maze[cellcheck.first][cellcheck.second -1].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				one_greater = true;
			}
			if (minval == -1){
				
				minval = maze[cellcheck.first][cellcheck.second-1].value;
			}
			else{
				if ( maze[cellcheck.first][cellcheck.second-1].value < minval){
					minval =  maze[cellcheck.first][cellcheck.second-1].value;
				}
			}
		}
		if (maze[cellcheck.first][cellcheck.second].right_wall != 1 && one_greater== false){
			if (maze[cellcheck.first][cellcheck.second +1].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				one_greater = true;
			}
			if (minval == -1){
				minval = maze[cellcheck.first][cellcheck.second+1].value;
			}
			else{
				if ( maze[cellcheck.first][cellcheck.second+1].value < minval){
					minval =  maze[cellcheck.first][cellcheck.second+1].value;
				}
			}			
		}
		if (maze[cellcheck.first][cellcheck.second].top_wall != 1 && one_greater== false){
			if (maze[cellcheck.first-1][cellcheck.second ].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				one_greater = true;
			}		
			if (minval == -1){
				minval = maze[cellcheck.first-1][cellcheck.second].value;
			}
			else{
				if ( maze[cellcheck.first-1][cellcheck.second].value < minval){
					minval =  maze[cellcheck.first][cellcheck.second+1].value;
				}
			}			
		}
		
		if (maze[cellcheck.first][cellcheck.second].bottom_wall != 1 && one_greater== false){
			if (maze[cellcheck.first+1][cellcheck.second ].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				one_greater = true;
			}
			if (minval == -1){
				minval = maze[cellcheck.first+1][cellcheck.second].value;
			}
			else{
				if ( maze[cellcheck.first+1][cellcheck.second].value < minval){
					minval =  maze[cellcheck.first][cellcheck.second+1].value;
				}
			}		
		}		
		//if cell check value isnt one greater than accessible neighbors
		if (one_greater == false){
			//cellcheck = minval + 1
			maze[cellcheck.first][cellcheck.second].value = minval + 1;
			//checks.push (neighbors)
			if (maze[cellcheck.first][cellcheck.second].left_wall != 1){
				pair_to_push_to_checks.first = cellcheck.first;
				pair_to_push_to_checks.second = cellcheck.second -1;
				checks.push(pair_to_push_to_checks);
			}
			if (maze[cellcheck.first][cellcheck.second].right_wall != 1){
				pair_to_push_to_checks.first = cellcheck.first;
				pair_to_push_to_checks.second = cellcheck.second +1;
				checks.push(pair_to_push_to_checks);
			}
			if (maze[cellcheck.first][cellcheck.second].top_wall != 1){
				pair_to_push_to_checks.first = cellcheck.first-1;
				pair_to_push_to_checks.second = cellcheck.second;
				checks.push(pair_to_push_to_checks);
			}
			if (maze[cellcheck.first][cellcheck.second].bottom_wall != 1){
				pair_to_push_to_checks.first = cellcheck.first+1;
				pair_to_push_to_checks.second = cellcheck.second;
				checks.push(pair_to_push_to_checks);
			}			
			
		}
		
		
			
			
		}
		//advance to ideal neighbor
		if (maze[mouse_pos.first][mouse_pos.second].left_wall != 1){
			if(maze[mouse_pos.first][mouse_pos.second-1].value+1 == maze[mouse_pos.first][mouse_pos.second].value){
				mouse_pos.first = mouse_pos.first;
				mouse_pos.second = mouse_pos.second -1;
				changed_mouse_pos = true;
			}
		}
		if (maze[mouse_pos.first][mouse_pos.second].right_wall != 1 && changed_mouse_pos == false){
			if(maze[mouse_pos.first][mouse_pos.second+1].value+1 == maze[mouse_pos.first][mouse_pos.second].value){
				mouse_pos.first = mouse_pos.first;
				mouse_pos.second = mouse_pos.second +1;
				changed_mouse_pos = true;
			}
		}
		if (maze[mouse_pos.first][mouse_pos.second].top_wall != 1 && changed_mouse_pos == false){
			if(maze[mouse_pos.first-1][mouse_pos.second].value+1 == maze[mouse_pos.first][mouse_pos.second].value){
				mouse_pos.first = mouse_pos.first-1;
				mouse_pos.second = mouse_pos.second ;
				changed_mouse_pos = true;
			}
		}
		if (maze[mouse_pos.first][mouse_pos.second].bottom_wall != 1 && changed_mouse_pos == false){
			if(maze[mouse_pos.first+1][mouse_pos.second].value+1 == maze[mouse_pos.first][mouse_pos.second].value){
				mouse_pos.first = mouse_pos.first+1;
				mouse_pos.second = mouse_pos.second ;
				changed_mouse_pos = true;
			}
		}
		//done going to next ideal position
	}//while (mouse_pos != goal)
	
	return 0;	
}






	
	



void display_maze(){

	
	
}