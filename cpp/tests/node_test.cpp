#include "node_test.h"
#include "../utils.h"
#include "../Node.h"
#include <algorithm>

using namespace Eigen;
using namespace std;

TEST_F(NodeTest, calcNextMove) {
  
  vector<int> last_ij = { 1 , 2 };
  
  auto testnode = Node( 2 , 2 , last_ij );
  
  auto nextmove = testnode.calculate_valid_next_move( M_ );
  
  vector<int> move = {2,1};
  
  ASSERT_TRUE( nextmove == move );
  
}
