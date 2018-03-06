//Assume dimensions are both equal for the rest of the code
//put into brackets of the number of cells in the maze
//using 5 * 5 for testing



//FIXME the color problem

int dim_1 = 5;
int dim_2 = 5;
int maze [dim_1][dim_2];

int target_color = 1;
int replacement_color = 0;
int node = 13;


//FIXME make it doable for mazes of different dimensions

void floodfill(node,target_color,replacement_color){
  if (target_color == replacement_color){
    return;
  }
  if (node != target_color){
    return;
  }
  node = replacement_color;
//1
  floodfill(node-1,target_color,replacement_color)
//2
  floodfill(node+1,target_color,replacement_color)
//3
  floodfill(node+dim_1,target_color,replacement_color
//4
  floodfill(node-dim_1,target_color,replacement_color

  return;

}
