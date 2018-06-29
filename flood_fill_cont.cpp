//find out how to implement wallmaze in loop
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
using namespace std;

// struct pair {
//    int first;
//    int second;
// };
//
//
//    struct pair pair1;        /* Declare pair1 of type pair */
//    struct pair pair2;        /* Declare pair2 of type pair */


// struct coord {
	// int x;
	// int y;
// }

// struct entry {
	// int distance;
	// int walls;
// }


//in each movement update walls struct at each location
	struct walls{
		bool hasleftwall;
		bool hasrightwall;
		bool hastopwall;
		bool hasbottomwall;
	}


int main(){
  //struct pair goals;
  //initialize variables
  int distmaze[8][8];
  
  //int wallmaze[8][8];
  walls wallmaze[8][8];
  pair<int,int> goal (3,3);
  pair<int,int> start(8,0);
  stack<pair<int,int> > checks;
  pair<int,int> cellcheck;

  //set all walls to zero
  // for(int height = 0;height < 8; ++height){
    // for(int width = 0; width < 8; ++width){
      // wallmaze[height][width] = 0;
    // }
  // }
	
  for(int height = 0;height < 8; ++height){
    for(int width = 0; width < 8; ++width){
      wallmaze[height][width].hasleftwall = false;
	  wallmaze[height][width].hasrightwall = false;
	  wallmaze[height][width].hastopwall = false;
	  wallmaze[height][width].hasbottomwall = false;
	  
    }
  }
  
  
  //FIXME find way to assign each cell with distance away from center
  //Fixed this 
  int counter = 8;
  for(int height = 0; height < 8; ++height){
    for(int width = 0; width < 8; ++width){
      distmaze[height][width] = abs(goal.first - height) + abs(goal.second - width);
    }
    //counter--;
  }

  //output the distmaze object;
  for(int height = 0;height < 8; ++height){
    for(int width = 0; width < 8; ++width){
      cout << distmaze[height][width] << " ";
    }
    cout << endl;
  }

  checks.push(start);
  while(start != goal){
    while(!checks.empty()){
      cellcheck = checks.top();
      checks.pop();
      bool check_if_one_off = true;

	  //left
      if (cellcheck.second -1  >= 0){
		if (wallmaze[cellcheck.first][cellcheck.second-1].leftwall != false){
        if (distmaze[cellcheck.first][cellcheck.second] !=
          distmaze[cellcheck.first][cellcheck.second-1]+ 1  ){
            check_if_one_off = false;
			}
          }
        }

	  //top
      if (cellcheck.first -1 >=0){
		if (wallmaze[cellcheck.first-1][cellcheck.second].topwall !=false){
        if (distmaze[cellcheck.first][cellcheck.second]!=
          distmaze[cellcheck.first-1][cellcheck.second] + 1){
            check_if_one_off = false;
			}
          }
        }

	  //right
      if (cellcheck.second + 1 <= 7){
		 if (wallmaze[cellcheck.first][cellcheck.second+1].rightwall != false){ 
        if (distmaze[cellcheck.first][cellcheck.second]!=
          distmaze[cellcheck.first][cellcheck.second+1] + 1){
            check_if_one_off = false;
		  }
          }
        }
		
	  //bottom
      if (cellcheck.first + 1 <= 7){
        if (wallmaze[cellcheck.first+1][cellcheck.second].bottomwall!= false){
		if (distmaze[cellcheck.first][cellcheck.second]!=
          distmaze[cellcheck.first+1][cellcheck.second] + 1){
            check_if_one_off = false;
          }
        }
	  }
		
		
	  	
      if (check_if_one_off == false){
        int minval=100000;
		pair<int, int> next_ideal_pos;
		
		//left
        if (cellcheck.second -1  >= 0){
		  if (wallmaze[cellcheck.first][cellcheck.second-1].leftwall!= false){
		  if (distmaze[cellcheck.first][cellcheck.second-1] < minval){
          minval = distmaze[cellcheck.first][cellcheck.second-1];
		  next_ideal_pos.first = cellcheck.first;
		  next_ideal_pos.second = cellcheck.second-1;
          }
        }
		}
		
		//top 
        if (cellcheck.first -1 >= 0){
		  if (wallmaze[cellcheck.first-1][cellcheck.second].topwall!= false){
          if (distmaze[cellcheck.first-1][cellcheck.second] < minval){
			minval = distmaze[cellcheck.first-1][cellcheck.second];
		  next_ideal_pos.first = cellcheck.first-1;
		  next_ideal_pos.second = cellcheck.second;
          }
        }
		}
		
		//right
		if (cellcheck.second + 1 <= 7){
			if (wallmaze[cellcheck.first][cellcheck.second+1].rightwall!= false){
			if (distmaze[cellcheck.first][cellcheck.second+1] < minval) {
				minval = distmaze[cellcheck.first][cellcheck.second+1];
		  next_ideal_pos.first = cellcheck.first;
		  next_ideal_pos.second = cellcheck.second+1;
			}
		}
		
		//bottom 
		if (cellcheck.first + 1 <= 7){
			if (wallmaze[cellcheck.first+1][cellcheck.second].bottomwall!= false){
			if (distmaze[cellcheck.first + 1][cellcheck.second] < minval) {
				minval = distmaze[cellcheck.first+1][cellcheck.second];
		  next_ideal_pos.first = cellcheck.first+1;
		  next_ideal_pos.second = cellcheck.second;
			}
			}
		}
		
		
		distmaze[cellcheck.first][cellcheck.second] = minval ++;
		
		pair<int, int> pair_to_push;
		
		//left
		if (cellcheck.second -1  >= 0){
          if (wallmaze[cellcheck.first][cellcheck.second-1].leftwall!= false){
		  pair_to_push.first = cellcheck.first;
		  pair_to_push.second = cellcheck.second-1;
		  checks.push(pair_to_push);
        }
		}
		//top
        if (cellcheck.first -1 >= 0){
		if (wallmaze[cellcheck.first-1][cellcheck.second].topwall!= false){
		  pair_to_push.first = cellcheck.first-1;
		  pair_to_push.second = cellcheck.second;
		  checks.push(pair_to_push);
        }
		}
		//right 
		if (cellcheck.second + 1 <= 7){
		if (wallmaze[cellcheck.first][cellcheck.second+1].rightwall!= false){
		  pair_to_push.first = cellcheck.first;
		  pair_to_push.second = cellcheck.second+1;
		  checks.push(pair_to_push);
		}
		}
		//bottom
		if (cellcheck.first + 1 <= 7){
		if (wallmaze[cellcheck.first+1][cellcheck.second].bottomwall!= false){
		  pair_to_push.first = cellcheck.first + 1;
		  pair_to_push.second = cellcheck.second;
		  checks.push(pair_to_push);
		}
		}
		
		start.first = next_ideal_pos.first;
		start.second = next_ideal_pos.second;
		


		

              // if (distmaze[cellcheck.first][cellcheck.second] !=
              //    distmaze[cellcheck.first + 1][cellcheck.second + 2] + 1 ){
              //
              // }
            }
            //cout << "CDCDCDCDCD" << endl;
          }

        }
		
		//make class for walls
		

        //
        // testing
        //
        // for(int height = 0;height < 8; ++height){
        //   for(int width = 0; width < 8; ++width){
        //     distmaze[height][width] = 1;
        //   }
        // }
        //
        // for(int height = 0;height < 8; ++height){
        //   for(int width = 0; width < 8; ++width){
        //     cout << distmaze[height][width] << " ";
        //   }
        //
        //   cout << endl;
        // }