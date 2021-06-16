#include "search_test.h"
#include "../utils.h"
#include "../examplemaze.h"
#include "../Node.h"
#include "../search.h"
#include <algorithm>

using namespace Eigen;
using namespace std;

TEST_F( SearchTest , depth_first_search ) {
  
  MatrixXi M = make_maze_32x32();
  
  vector<vector<int>> exits = find_exit_points_of_maze( M );
  
  vector<int> ij_0 = exits[0];
  vector<int> ij_f = exits[1];
  
  vector<Node> soln_nodes;
  vector<vector<vector<int>>> soln_IJ;
  
  depth_first_solve( M , ij_0 , ij_f , soln_nodes , soln_IJ );

  vector<vector<int>> soln_nodes_ij;
  
  for ( int i=0; i<soln_nodes.size(); i++ )
    soln_nodes_ij.push_back( { soln_nodes[i].get_i() , soln_nodes[i].get_j() } );
  
  ASSERT_TRUE( soln_nodes_ij.size() == correct_nodes_.size() );
  
  for ( auto vi : correct_nodes_ )
    ASSERT_TRUE( find( soln_nodes_ij.begin() , soln_nodes_ij.end() , vi ) != soln_nodes_ij.end() );
    
}