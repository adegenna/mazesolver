#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <Eigen/Dense>

class Node {
  
 public:

  Node( const int i , const int j );
  Node( const int i , const int j , const std::vector<int>& last_ij );
  Node();
  ~Node( );
  std::vector<int> calculate_valid_next_move( const Eigen::MatrixXi& M );
  int get_i() const { return i_; };
  int get_j() const { return j_; };
  void increment_next_index( ) { next_index_ += 1; };
  int get_next_index() const { return next_index_; };
  std::vector<std::vector<int>> get_valid_next_moves() const { return valid_next_moves_; };
  
 private:

  const int i_ , j_;
  std::vector<int> last_ij_;
  int next_index_;
  std::vector< std::vector<int> > valid_next_moves_;
  
};

std::vector< std::vector<int> > get_all_node_ij( const std::vector<Node>& stack_nodes );


#endif
