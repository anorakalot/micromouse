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
	pair<int,int> coord;
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
bool not_1_greater;
pair<int,int> min_accessible;
//start of floodfill algorithm
checks.push(mouse_pos);
while(mouse_pos != goal_coord){
	1_greater = false;
	minval = -1;
	while(!checks.empty()){
		cellcheck = checks.top();
		checks.pop();
		//assume making maze puts walls for all boundaries 
		if (maze[cellcheck.first][cellcheck.second].left_wall != 1 && 1_greater == false){
			if (maze[cellcheck.first][cellcheck.second -1].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				1_greater = true;
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
		if (maze[cellcheck.first][cellcheck.second].right_wall != 1 && 1_greater== false){
			if (maze[cellcheck.first][cellcheck.second +1].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				1_greater = true;
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
		if (maze[cellcheck.first][cellcheck.second].top_wall != 1 && 1_greater== false){
			if (maze[cellcheck.first-1][cellcheck.second ].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				1_greater = true;
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
		if (maze[cellcheck.first][cellcheck.second].bottom_wall != 1 && 1_greater== false){
			if (maze[cellcheck.first+1][cellcheck.second ].value +1 ==  maze[mouse_pos.first][mouse_pos.second].value){
				1_greater = true;
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
		if (1_greater == false){
			maze[cellcheck.first][cellcheck.second+1].value += 1;
				
		}
		
		
			
			
		}
		
	}
	
}






	
	
return 0;	
}



void display_maze(){

	
	
}