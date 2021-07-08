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
    
  auto dfs = DepthFirstSearch( M , ij_0 , ij_f );
  ASSERT_TRUE( dfs.solutionLength() == correct_nodes_.size() );

  auto& soln_nodes_ij = dfs.getSolutionNodes();
  
  for ( auto vi : correct_nodes_ )
    ASSERT_TRUE( find( soln_nodes_ij.begin() , soln_nodes_ij.end() , vi ) != soln_nodes_ij.end() );
}
