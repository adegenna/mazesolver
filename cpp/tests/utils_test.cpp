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
