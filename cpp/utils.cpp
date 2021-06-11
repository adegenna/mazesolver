#include "utils.h"
#include <iostream>

using namespace std;
using namespace Eigen;

vector< vector<int> > find_possible_moves( const int i ,
					   const int j ,
					   const MatrixXi& M ) {
  
  vector< vector<int> > moves;

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

vector< vector<int> > find_exit_points_of_maze( const MatrixXi& M ) {
  
  vector<vector<int>> exits;
  
  for (int i=0; i<M.rows(); i++) {
    
    if ( M(0,i) == 0 )
      exits.push_back( {0,i} );
    
    if ( M(M.rows()-1,i) == 0 )
      exits.push_back( {M.rows()-1,i} );
    
  }
  
  for (int i=0; i<M.cols(); i++) {
    
    if ( M(i,0) == 0 )
      exits.push_back( {i,0} );
    
    if ( M(i,M.cols()-1) == 0 )
      exits.push_back( {i,M.cols()-1} );
    
  }
  
  return exits;
  
}
