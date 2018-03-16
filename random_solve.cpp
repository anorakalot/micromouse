#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

std::vector<std::vector<int> > maze;
int random_move;


void fill_maze(int,int);
void print_maze();
void random_solve(int start_x,int start_y,int finish_x,int finish_y);

int main(){

std::cout << "Start (0,0) " <<"End at (6,6)" << std::endl;
fill_maze(10,10);
print_maze();


random_solve (0,0,5,6);

}

void random_solve(int pos_x,int pos_y,int finish_x,int finish_y){
  int delay_sec = 1000000;

  srand(time(0));

  maze.at(pos_x).at(pos_y) = 1;

  while(pos_x != finish_x && pos_y != finish_y){
    random_move = rand() %(4-1+1) + 1;
    if (random_move == 1){
      //get rid of
      maze.at(pos_x).at(pos_y) = 0;
      if (pos_y + 1 >= 10){
        //continue;
      }
      else{
      pos_y +=1;
      }
      maze.at(pos_x).at(pos_y) = 1;
      print_maze();
      std::cout <<std::endl;
      usleep(delay_sec);
    }
    else if (random_move ==2){

      maze.at(pos_x).at(pos_y) = 0;
      if (pos_y - 1 < 0){
        continue;
      }
      else{
      pos_y -=1;
      }
      maze.at(pos_x).at(pos_y) = 1;
      print_maze();
      std::cout << std::endl;
      usleep(delay_sec);
    }
    else if (random_move ==3){

      maze.at(pos_x).at(pos_y) = 0;
      if (pos_x + 1 >= 10){
        continue;
      }
      else{
      pos_x +=1;
      }
      maze.at(pos_x).at(pos_y) = 1;
      print_maze();
      std::cout << std::endl;
      usleep(delay_sec);
    }
    else if (random_move ==4){

      maze.at(pos_x).at(pos_y) = 0;
      if (pos_x - 1 < 0){
        continue;
      }
      else{
        pos_x -=1;
      }
      maze.at(pos_x).at(pos_y) = 1;
      print_maze();
      std::cout << std::endl;
      usleep(delay_sec);
    }

  }
}












void fill_maze(int y_size,int x_size){//, int y_size){
  std::vector<int> temp;
  for (int x = 0; x < x_size; ++x){
    temp.push_back(0);
  }

  for (unsigned y = 0; y < y_size; ++y){
    //for(unsigned y = 0; y <y_size; ++y){
      //maze.at(x).at(y).push_back(0);
    //}
    maze.push_back(temp);
  }
}


void print_maze(){
  for (int x = 0; x < maze.size(); ++x){
    for(int y = 0; y < maze.at(x).size(); ++y){
      std::cout << maze.at(x).at(y) << " ";
    }
    std::cout << std::endl;
  }
}
