#include "utils.h"

std::vector< std::vector<int> > find_possible_moves( const int i ,
						     const int j ,
						     const Eigen::MatrixXi& M ) {
  
  std::vector< std::vector<int> > moves;

  if ( i-1 >= 0 ) {
    if ( M(i-1,j) == 0 )
      moves.push_back( { i-1 , j } );
  }

  if ( i+1 < M.rows() ) {
    if ( M(i+1,j) == 0 )
      moves.push_back( { i+1 , j } );
  }

  if ( j-1 >= 0 ) {
    if ( M(i,j-1) == 0 )
      moves.push_back( { i , j-1 } );
  }

  if ( j+1 < M.cols() ) {
    if ( M(i,j+1) == 0 )
      moves.push_back( { i , j+1 } );
  }
  
  return moves;
  
}
