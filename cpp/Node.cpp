#include "Node.h"
#include "utils.h"
#include <iterator>

using namespace std;
using namespace Eigen;

Node::Node( const int i , const int j )
  : i_(i), j_(j)
  
{
  
  last_ij_    = { -1 , -1 };
  next_index_ = 0;
  
}

Node::Node( const int i , const int j , vector<int>& last_ij )
  : i_(i) , j_(j) , last_ij_(last_ij)
  
{
  next_index_ = 0;
}

Node::Node( ) {
  i_ = -1; j_ = -1;
  last_ij_    = {-1,-1};
  next_index_ = 0;
}

Node::~Node( ) {

}

vector<int> Node::calculate_valid_next_move( const MatrixXi& M ) {
  
  vector<vector<int>>::iterator ptr;
  
  if ( valid_next_moves_.empty() ) {
    
    vector<vector<int>> moves = find_possible_moves( i_ , j_ , M );
    
    for ( auto vi : moves ) {
      
      if ( vi != last_ij_ )
	valid_next_moves_.push_back( vi );
      
    }
    
  }
  
  return valid_next_moves_[ next_index_ ]; 
  
}

