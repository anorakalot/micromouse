//Assume dimensions are both equal for the rest of the code
//put into brackets of the number of cells in the maze
//using 5 * 5 for testing



//FIXME the color problem maybe use chars instead

int dim_1 = 5;
int dim_2 = 5;
int maze [dim_1][dim_2];

int target = 1;
int replacement = 0;
int node = 13;


//FIXME make it doable for mazes of different dimensions

void floodfill(node,target,replacement){
  if (target == replacement){
    return;
  }
  if (node != target){
    return;
  }
  node = replacement;
//1
  floodfill(node-1,target,replacement)
//2
  floodfill(node+1,target,replacement)
//3
  floodfill(node+dim_1,target,replacement)
//4
  floodfill(node-dim_1,target,replacement)

  return;

}
