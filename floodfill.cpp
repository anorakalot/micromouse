#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int main(){
  //initialize variables
  int distmaze[8][8];
  int wallmaze[8][8];
  pair<int,int> goal (3,3);
  pair<int,int> start(8,1);
  stack<int> checks;

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
      distmaze[height][width] = counter;
    }
    counter--;
  }

  //output the distmaze object;
  for(int height = 0;height < 8; ++height){
    for(int width = 0; width < 8; ++width){
      cout << distmaze[height][width] << " ";
    }
    cout << endl;
  }



}

//testing
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
//   cout << endl;
// }
