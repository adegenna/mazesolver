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
  
  for (int i=0; i<M.cols(); i++) {
    
    if ( M(0,i) == 0 )
      exits.push_back( {0,i} );
    
    if ( M(M.rows()-1,i) == 0 )
      exits.push_back( {M.rows()-1,i} );
    
  }
  
  for (int i=0; i<M.rows(); i++) {
    
    if ( M(i,0) == 0 )
      exits.push_back( {i,0} );
    
    if ( M(i,M.cols()-1) == 0 )
      exits.push_back( {i,M.cols()-1} );
    
  }
  
  return exits;
  
}


bool check_if_ij_is_maze_node( const MatrixXi& M ,
			       const int i , const int j ,
			       const vector<int> last_ij ) {
  
  // Boundary
  
  if ( (i==0) || (i==M.rows()-1) | (j==0) | (j==M.cols()-1) ) {
    
    if ( M(i,j) == 0 )
      return true;
    else
      return false;
    
  }
  
  // Interior

  else {
    
    vector<vector<int>> moves_ij = find_possible_moves( i , j , M );
    vector<vector<int>> moves_ij_nolast( moves_ij.size() );
    
    auto it = copy_if ( moves_ij.begin(), moves_ij.end(), moves_ij_nolast.begin(),
			[last_ij](vector<int> mi){ return !( mi == last_ij ); } );
    moves_ij_nolast.resize( distance( moves_ij_nolast.begin() , it ) );
    
    if ( moves_ij_nolast.size() > 1 )
      return true;
    else
      return false;
    
  }
  
}


void print_vector_vector_int( const vector<vector<int>>& list_IJ ) {
  
  for ( int i=0; i<list_IJ.size(); i++ ) {
    for ( int j=0; j<list_IJ[i].size(); j++ ) {
      cout << list_IJ[i][j] << ",";
    }
    cout << endl;
  }
  cout << endl;

}
