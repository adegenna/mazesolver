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
  
  MatrixXi M = make_maze_32x32();
  
  vector<vector<int>> exits = find_exit_points_of_maze( M );
  
  vector<int> ij_0 = exits[0];
  vector<int> ij_f = exits[1];
  
  cout << "maze size: " << M.rows() << "x" << M.cols() << endl;
  
  cout << "entrance: (";
  cout << ij_0[0] << "," << ij_0[1];
  cout << ")" << endl;
  
  cout << "exit: (";
  cout << ij_f[0] << "," << ij_f[1];
  cout << ")" << endl;
  
  auto [ soln_nodes , soln_IJ ]  = depth_first_solve( M , ij_0 , ij_f );
  
  cout << "computed nodal solution:" << endl;
  for ( int i=0; i<soln_nodes.size(); i++ )
    cout << "( " << soln_nodes[i].get_i() << " , " << soln_nodes[i].get_j() << " )" << endl; 
  
  return 0;
}
