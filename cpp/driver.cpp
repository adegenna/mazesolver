#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <random>
#include <cmath>
#include <Eigen/Dense>
#include "utils.h"
#include "Node.h"
#include "search.h"
#include "examplemaze.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
  
  cout << "*********** DRIVER PROGRAM FOR MAZE SOLVER ***********\n\n";
  
  MatrixXi M = make_maze_32x32_with_loops();
  
  vector<vector<int>> exits = find_exit_points_of_maze( M );

  const Node ij_0(exits[0][0], exits[0][1]);
  const Node ij_f(exits[1][0], exits[1][1]);

  
  cout << "maze size: " << M.rows() << "x" << M.cols() << endl;
  
  cout << "entrance: (";
  cout << ij_0.get_i() << "," << ij_0.get_j();
  cout << ")" << endl;
  
  cout << "exit: (";
  cout << ij_f.get_i() << "," << ij_f.get_j();
  cout << ")" << endl;
  

  DepthFirstSearch( M , ij_0 , ij_f ).writeSolutionToCSV("soln_ij.csv");
  
  return 0;
}
