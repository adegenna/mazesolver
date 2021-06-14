#include "search.h"
#include "utils.h"
#include "Node.h"
#include <iostream>

using namespace std;
using namespace Eigen;

void depth_first_solve( const MatrixXi& M ,
			const vector<int> ij_0 ,
			const vector<int> ij_f ,
			vector<Node>& soln_nodes ,
			vector<vector<vector<int>>>& soln_IJ ) {
  
  soln_nodes.clear();
  soln_nodes.push_back( Node( ij_0[0] , ij_0[1] ) );
  
  auto first_moves = find_possible_moves( ij_0[0] , ij_0[1] , M );
  assert( first_moves.size() == 1 ); // assuming entrance is not a split...
  auto first_move = first_moves[0];
  
  auto ij = first_move;
  auto last_ij = ij_0;
  
  soln_IJ.clear();
  soln_IJ[0].push_back( last_ij );
  soln_IJ.resize( soln_IJ.size() + 1 );
  
  while ( ij != ij_f ) {
    
    soln_IJ[soln_IJ.size()-1].push_back( ij );

    if ( check_if_ij_is_maze_node( M , ij[0] , ij[1] , last_ij ) ) {
      
      soln_nodes.push_back( Node( ij[0] , ij[1] , last_ij ) );
      
      last_ij = { soln_nodes[soln_nodes.size()-1].get_i() ,
		  soln_nodes[soln_nodes.size()-1].get_j() };
      ij      = soln_nodes[soln_nodes.size()-1].calculate_valid_next_move( M );
      
      soln_IJ.resize( soln_IJ.size() );
      
    }
    
    else {
      
      auto moves = find_possible_moves( ij[0] , ij[1] , M );
      
      if ( moves.size() == 2 ) {    // not a dead end...
	
	auto ij_save = ij;

	if ( moves[0] == last_ij )
	  ij = moves[1];
	else
	  ij = moves[0];
	
	last_ij = ij_save;
	
      }
      
      else if ( moves.size() == 1 ) {    // dead end case...
	
	soln_nodes[soln_nodes.size()-1].increment_next_index();
	soln_IJ.pop_back();
	soln_IJ.resize( soln_IJ.size() );
	
	while( true ) {
	  
	  if ( soln_nodes[soln_nodes.size()-1].get_next_index() >=
	      (soln_nodes[soln_nodes.size()-1].get_valid_next_moves()).size() ) {
	    
	    soln_nodes.pop_back();
	    soln_nodes[soln_nodes.size()-1].increment_next_index();
	    soln_IJ.pop_back();
	    
	    soln_IJ.pop_back();
	    soln_IJ.resize( soln_IJ.size() );
	    
	  }
	  
	  else
	    break;
	  
	}
	
	last_ij = { soln_nodes[soln_nodes.size()-1].get_i() ,
	            soln_nodes[soln_nodes.size()-1].get_j() };
	ij = soln_nodes[soln_nodes.size()-1].calculate_valid_next_move(M);
	
      }

      else {
	
	cout << "error" << endl;
	break;
	
      }
      
    }
    
  }

  return;

}
