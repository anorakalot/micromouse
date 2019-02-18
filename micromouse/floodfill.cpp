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
};

void display_maze();


int main(){
stack <int> s;

pair <int,int> goal_coord(4,4);
pair <int,int> mouse_pos (8,0);


int maze_x_length = 9;
int maze_y_length = 9;
int index_x_max = 8;
int index_y_max = 8;

cell maze[maze_y_length][maze_x_length];

///*
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




	
	
return 0;	
}



void display_maze(){

	
	
}