#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <Eigen/Dense>

class Node {
  
 public:

  Node( const int i , const int j );
  Node( const int i , const int j , std::vector<int>& last_ij );
  ~Node( );
  std::vector<int> calculate_valid_next_move( const Eigen::MatrixXi& M );
  
 private:

  int i_ , j_;
  std::vector<int> last_ij_;
  std::vector<int> next_index_;
  std::vector< std::vector<int> > valid_next_moves_;
  
};


#endif
