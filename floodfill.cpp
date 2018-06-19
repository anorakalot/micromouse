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



int main(){
  //struct pair goals;
  //initialize variables
  int distmaze[8][8];
  int wallmaze[8][8];
  pair<int,int> goal (3,3);
  pair<int,int> start(8,0);
  stack<pair<int,int> > checks;
  pair<int,int> cellcheck;

  //set all walls to zero
  for(int height = 0;height < 8; ++height){
    for(int width = 0; width < 8; ++width){
      wallmaze[height][width] = 0;
    }
  }

  //FIXME find way to assign each cell with distance away from center
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


      if (cellcheck.second -1  >= 0){
        if (distmaze[cellcheck.first][cellcheck.second] !=
          distmaze[cellcheck.first][cellcheck.second-1]+ 1  ){
            check_if_one_off = false;
          }
        }


      if (cellcheck.first -1 >=0){
        if (distmaze[cellcheck.first][cellcheck.second]!=
          distmaze[cellcheck.first-1][cellcheck.second] + 1){
            check_if_one_off = false;
          }
        }


      if (cellcheck.second + 1 <= 7){
        if (distmaze[cellcheck.first][cellcheck.second]!=
          distmaze[cellcheck.first][cellcheck.second+1] + 1){
            check_if_one_off = false;
          }
        }

      if (cellcheck.first + 1 <= 7){
        if (distmaze[cellcheck.first][cellcheck.second]!=
          distmaze[cellcheck.first+1][cellcheck.second] + 1){
            check_if_one_off = false;
          }
        }

		
		
		
      if (check_if_one_off == false){
        int minval;
		pair<int, int> next_ideal_pos;
		
        if (cellcheck.second -1  >= 0){
          minval = distmaze[cellcheck.first][cellcheck.second-1];
		  next_ideal_pos.first = cellcheck.first;
		  next_ideal_pos.second = cellcheck.second-1;
          }
        }
        if (cellcheck.first -1 >= 0){
          if (distmaze[cellcheck.first-1][cellcheck.second] < minval){
			minval = distmaze[cellcheck.first-1][cellcheck.second];
		  next_ideal_pos.first = cellcheck.first-1;
		  next_ideal_pos.second = cellcheck.second;
          }
        }
		
		if (cellcheck.second + 1 <= 7){
			if (distmaze[cellcheck.first][cellcheck.second+1] < minval) {
				minval = distmaze[cellcheck.first][cellcheck.second+1];
		  next_ideal_pos.first = cellcheck.first;
		  next_ideal_pos.second = cellcheck.second+1;
			}
		}
		
		if (cellcheck.first + 1 <= 7){
			if (distmaze[cellcheck.first + 1][cellcheck.second] < minval) {
				minval = distmaze[cellcheck.first+1][cellcheck.second];
		  next_ideal_pos.first = cellcheck.first+1;
		  next_ideal_pos.second = cellcheck.second;
			}
		}
		
		
		distmaze[cellcheck.first][cellcheck.second] = minval ++;
		
		pair<int, int> pair_to_push;
		
		
		if (cellcheck.second -1  >= 0){
          pair_to_push.first = cellcheck.first;
		  pair_to_push.second = cellcheck.second-1;
		  checks.push(pair_to_push);
        }
				
        if (cellcheck.first -1 >= 0){
		  pair_to_push.first = cellcheck.first-1;
		  pair_to_push.second = cellcheck.second;
		  checks.push(pair_to_push);
        }
		
		if (cellcheck.second + 1 <= 7){
		  pair_to_push.first = cellcheck.first;
		  pair_to_push.second = cellcheck.second+1;
		  checks.push(pair_to_push);
		}
		
		if (cellcheck.first + 1 <= 7){
		  pair_to_push.first = cellcheck.first + 1;
		  pair_to_push.second = cellcheck.second;
		  checks.push(pair_to_push);
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