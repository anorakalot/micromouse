#include <iostream>
#include <stack>
#include <utility>
using namespace std;

struct cell{
	bool light_wall;
	bool right_wall;
	bool top_wall;
	bool bottom_wall;
};

int main(){
stack <int> s;

pair <int,int> goal_coord;
int maze[4][4];

for (int x =0; x <4; ++x){
	
	for(int y = 0; y < 4; ++y) {
		maze[x][y] = 1;
	}
}

for (int x =0; x <4; ++x){
	
	for(int y = 0; y < 4; ++y) {
		cout << maze[x][y]<< " ";
	}
	cout << endl;
}



	
	
return 0;	
}