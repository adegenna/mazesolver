#include "utils_test.h"
#include "../utils.h"
#include <algorithm>

using namespace Eigen;
using namespace std;

TEST_F(UtilsTest, findmoves) {
  
  vector<vector<int>> moves = find_possible_moves( 2 , 2 , M_ );

  vector<int> move1 = {1,2};
  vector<int> move2 = {2,1};
  
  ASSERT_TRUE( find( moves.begin() , moves.end() , move1 ) != moves.end() );
  ASSERT_TRUE( find( moves.begin() , moves.end() , move2 ) != moves.end() );
  
}

TEST_F( UtilsTest , findexits ) {
  
  vector<vector<int>> exits = find_exit_points_of_maze( M_ );
  
  vector<int> exit1 = { 0 , 2 };
  vector<int> exit2 = { 3 , 1 };
  
  ASSERT_TRUE( find( exits.begin() , exits.end() , exit1 ) != exits.end() );
  ASSERT_TRUE( find( exits.begin() , exits.end() , exit2 ) != exits.end() );
  
}

TEST_F( UtilsTest , checkifnode ) {
  
  ASSERT_TRUE( check_if_ij_is_maze_node( M_ , 2 , 2 , { 1 , 2 } ) );

}
