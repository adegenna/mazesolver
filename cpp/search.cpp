#include "search.h"
#include "utils.h"
#include "Node.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace Eigen;

vector<vector<int>> back_track_and_mark_dead_end_nodes( vector<Node>& stack_nodes ,
							vector<vector<vector<int>>>& list_IJ ) {
  
  vector<vector<int>> dead_end_IJ;
  
  stack_nodes[stack_nodes.size()-1].increment_next_index();
  
  if ( stack_nodes[stack_nodes.size()-1].get_next_index() >=
       (stack_nodes[stack_nodes.size()-1].get_valid_next_moves()).size() ) {
    dead_end_IJ.push_back( { stack_nodes[stack_nodes.size()-1].get_i() , 
	  stack_nodes[stack_nodes.size()-1].get_j() } );
  }
  
  list_IJ.pop_back();
  list_IJ.resize( list_IJ.size()+1 );
  
  while( true ) {
    
    if ( stack_nodes.size() == 1 )
      return { {-1,-1} };
    
    bool flag;
    
    if ( stack_nodes[stack_nodes.size()-1].get_valid_next_moves().empty() )
      flag = true;
    else {
      flag = ( stack_nodes[stack_nodes.size()-1].get_next_index() >=
	     ( stack_nodes[stack_nodes.size()-1].get_valid_next_moves() ).size() );
    }
    
    if ( ( stack_nodes[stack_nodes.size()-1].get_next_index() >=
	   (stack_nodes[stack_nodes.size()-1].get_valid_next_moves()).size() ) || flag ) {
      
      dead_end_IJ.push_back( { stack_nodes[stack_nodes.size()-1].get_i() , 
	    stack_nodes[stack_nodes.size()-1].get_j() } );
      
      stack_nodes.pop_back();
      stack_nodes[stack_nodes.size()-1].increment_next_index();
      list_IJ.pop_back();
      
      list_IJ.pop_back();
      list_IJ.resize( list_IJ.size()+1 );
      
    }
    
    else
      break;
    
  }
  
  return dead_end_IJ;
  
}


tuple< vector<Node> , vector<vector<vector<int>>> > depth_first_solve(
			const MatrixXi& M ,
			const vector<int>& ij_0 ,
			const vector<int>& ij_f ) {
  
  vector<Node> soln_nodes;
  vector<vector<vector<int>>> soln_IJ;
  vector<vector<int>> dead_end_IJ;
  
  soln_nodes.clear();
  soln_nodes.push_back( Node( ij_0[0] , ij_0[1] ) );
  
  auto first_moves = find_possible_moves( ij_0[0] , ij_0[1] , M );
  assert( first_moves.size() == 1 ); // assuming entrance is not a split...
  auto first_move = first_moves[0];
  
  auto ij = first_move;
  auto last_ij = ij_0;
  
  soln_IJ.resize(1);
  soln_IJ[0].push_back( last_ij );
  soln_IJ.resize( soln_IJ.size() + 1 );
  
  while ( ij != ij_f ) {
    
    soln_IJ[soln_IJ.size()-1].push_back( ij );
    
    if ( check_if_ij_is_maze_node( M , ij[0] , ij[1] , last_ij ) ) {
      
      auto node_ij = get_all_node_ij( soln_nodes );
      
      if ( ( find( node_ij.begin() , node_ij.end() , ij ) != node_ij.end() ) ||
	   ( find( dead_end_IJ.begin() , dead_end_IJ.end() , ij ) != dead_end_IJ.end() ) ) { // you have been to this node before, so it's a loop...
	
	auto tmp = back_track_and_mark_dead_end_nodes( soln_nodes , soln_IJ );
	dead_end_IJ.insert( dead_end_IJ.end(), tmp.begin(), tmp.end() );
	
	last_ij = { soln_nodes[soln_nodes.size()-1].get_i() ,
	            soln_nodes[soln_nodes.size()-1].get_j() };
	ij = soln_nodes[soln_nodes.size()-1].calculate_valid_next_move(M);
	
      }

      else { // you haven't been to this node before...
	
	soln_nodes.push_back( Node( ij[0] , ij[1] , last_ij ) );
	
	last_ij = { soln_nodes[soln_nodes.size()-1].get_i() ,
		    soln_nodes[soln_nodes.size()-1].get_j() };
	ij      = soln_nodes[soln_nodes.size()-1].calculate_valid_next_move( M );
	
	soln_IJ.resize( soln_IJ.size()+1 );
      }
      
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
	
	auto tmp = back_track_and_mark_dead_end_nodes( soln_nodes , soln_IJ );
	dead_end_IJ.insert( dead_end_IJ.end(), tmp.begin(), tmp.end() );
	
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

  return make_tuple( soln_nodes , soln_IJ );

}
