#include "mazesolver.h"
#include <iterator>

using namespace std;
using namespace Eigen;

Node::Node( const int i , const int j )
  : i_(i), j_(j)
  
{
  
  last_ij_    = { -1 , -1 };
  next_index_ = 0;
  
}

Node::Node( const int i , const int j , std::vector<int>& last_ij )
  : i_(i) , j_(j) , last_ij_(last_ij)
  
{ }

Node::~Node( ) {

}

std::vector<int> Node::calculate_valid_next_move( const Eigen::MatrixXi& M ) {
  
  vector<int>::iterator ptr;
  
  if ( valid_next_moves_.empty() ) {
    
    moves = find_possible_moves( i_ , j_ , M );
    
    for ( ptr = moves.begin(); ptr < moves.end(); ptr++ ) {
      
      if ( *ptr ~= last_ij_ )
	valid_next_moves_.push_back( *ptr );
      
    }
    
  }
  
  return valid_next_moves_[ next_index_ ]; 
  
}

