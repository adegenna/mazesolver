#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <random>
#include <cmath>
#include <Eigen/Dense>
//#include <boost/program_options.hpp>
#include "utils.h"
#include "Node.h"
#include "search.h"
#include "examplemaze.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
  
  printf("*********** DRIVER PROGRAM FOR MAZE SOLVER ***********\n\n");

  MatrixXi M = make_maze_32x32();
  
  vector<vector<int>> exits = find_exit_points_of_maze( M );
  
  vector<int> ij_0 = exits[0];
  vector<int> ij_f = exits[1];
  
  vector<Node> soln_nodes;
  vector<vector<vector<int>>> soln_IJ;
  
  depth_first_solve( M ,
		     ij_0 , ij_f ,
		     soln_nodes , soln_IJ );
  
  
  
  return 0;
}
