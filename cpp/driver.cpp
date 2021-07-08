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
  
  vector<int> ij_0 = exits[0];
  vector<int> ij_f = exits[1];
  
  cout << "maze size: " << M.rows() << "x" << M.cols() << endl;
  
  cout << "entrance: (";
  cout << ij_0[0] << "," << ij_0[1];
  cout << ")" << endl;
  
  cout << "exit: (";
  cout << ij_f[0] << "," << ij_f[1];
  cout << ")" << endl;
  
  auto [ soln_nodes , soln_IJ ]  = DepthFirstSearch().depth_first_solve( M , ij_0 , ij_f );
    
  ofstream outfile_ij( "soln_ij.csv" );
  for ( int i=0; i<soln_IJ.size(); i++ ) {
    for ( int j=0; j<soln_IJ[i].size(); j++ ) {
      outfile_ij << soln_IJ[i][j][0] << "," << soln_IJ[i][j][1] << endl;
    }
  }
  outfile_ij << ij_f[0] << "," << ij_f[1];
  outfile_ij.close();
  
  return 0;
}
