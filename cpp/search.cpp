#include "search.h"
#include "Node.h"
#include "utils.h"
#include "path.h"
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;
using namespace Eigen;

namespace{
    std::vector<int> node_to_vec(const Node& n){
        return std::vector<int>{n.get_i(), n.get_j()};
    }
}

DepthFirstSearch::DepthFirstSearch(const Eigen::MatrixXi &M_in,
                                   const Node &ij_0_in,
                                   const Node &ij_f_in)
    : DepthFirstSearch(M_in, node_to_vec(ij_0_in), node_to_vec(ij_f_in))
{
}

DepthFirstSearch::DepthFirstSearch(const Eigen::MatrixXi &M_in,
                                   const std::vector<int> &ij_0_in,
                                   const std::vector<int> &ij_f_in)
        : ij_f(ij_f_in) {
    depth_first_solve(M_in, ij_0_in, ij_f_in, soln_nodes, path_ );
}

vector<vector<int>> DepthFirstSearch::back_track_and_mark_dead_end_nodes(
    vector<Node> &stack_nodes, Path& path ) {
  
  vector<vector<int>> dead_end_IJ;

  stack_nodes[stack_nodes.size() - 1].increment_next_index();

  if (stack_nodes[stack_nodes.size() - 1].get_next_index() >=
      (stack_nodes[stack_nodes.size() - 1].get_valid_next_moves()).size()) {
    dead_end_IJ.push_back({stack_nodes[stack_nodes.size() - 1].get_i(),
                           stack_nodes[stack_nodes.size() - 1].get_j()});
  }
  
  path.pop_last_candidate_path();
  path.add_new_empty_candidate_path();

  while (true) {

    if (stack_nodes.size() == 1)
      return {{-1, -1}};

    bool flag;

    if (stack_nodes[stack_nodes.size() - 1].get_valid_next_moves().empty())
      flag = true;
    else {
      flag =
          (stack_nodes[stack_nodes.size() - 1].get_next_index() >=
           (stack_nodes[stack_nodes.size() - 1].get_valid_next_moves()).size());
    }

    if ((stack_nodes[stack_nodes.size() - 1].get_valid_next_moves().empty()) ||
        flag) {

      dead_end_IJ.push_back({stack_nodes[stack_nodes.size() - 1].get_i(),
                             stack_nodes[stack_nodes.size() - 1].get_j()});

      stack_nodes.pop_back();
      stack_nodes[stack_nodes.size() - 1].increment_next_index();
      path.pop_last_candidate_path();
      
      path.pop_last_candidate_path();
      path.add_new_empty_candidate_path();
    }

    else
      break;
  }

  return dead_end_IJ;
}

void DepthFirstSearch::depth_first_solve(
    const Eigen::MatrixXi &M, const std::vector<int> &ij_0,
    const std::vector<int> &ij_f, std::vector<Node> &soln_nodes,
    Path& path ) {
  vector<vector<int>> dead_end_IJ;

  soln_nodes.clear();
  soln_nodes.push_back(Node(ij_0[0], ij_0[1]));

  auto first_moves = find_possible_moves(ij_0[0], ij_0[1], M);
  assert(first_moves.size() == 1); // assuming entrance is not a split...
  auto first_move = first_moves[0];

  auto ij = first_move;
  auto last_ij = ij_0;

  path.push( last_ij );
  path.add_new_empty_candidate_path();
  
  vector<vector<int>> no_soln = {
      {-1, -1}}; // returned by backtracking if no soln

  while (ij != ij_f) {
    
    path.push( ij );
 
    if (check_if_ij_is_maze_node(M, ij[0], ij[1], last_ij)) {

      auto node_ij = get_all_node_ij(soln_nodes);

      if ((find(node_ij.begin(), node_ij.end(), ij) != node_ij.end()) ||
          (find(dead_end_IJ.begin(), dead_end_IJ.end(), ij) !=
           dead_end_IJ.end())) { // you have been to this node before, so it's a
                                 // loop...

        auto tmp = back_track_and_mark_dead_end_nodes( soln_nodes , path );

        if (tmp == no_soln) {
          cout << "no soln found" << endl;
          break;
        }

        dead_end_IJ.insert(dead_end_IJ.end(), tmp.begin(), tmp.end());

        last_ij = {soln_nodes[soln_nodes.size() - 1].get_i(),
                   soln_nodes[soln_nodes.size() - 1].get_j()};
        ij = soln_nodes[soln_nodes.size() - 1].calculate_valid_next_move(M);
      }

      else { // you haven't been to this node before...

        soln_nodes.push_back(Node(ij[0], ij[1], last_ij));

        last_ij = {soln_nodes[soln_nodes.size() - 1].get_i(),
                   soln_nodes[soln_nodes.size() - 1].get_j()};
        ij = soln_nodes[soln_nodes.size() - 1].calculate_valid_next_move(M);
	
	path.add_new_empty_candidate_path();
      }
    }

    else {

      auto moves = find_possible_moves(ij[0], ij[1], M);

      if (moves.size() == 2) { // not a dead end...

        auto ij_save = ij;

        if (moves[0] == last_ij)
          ij = moves[1];
        else
          ij = moves[0];

        last_ij = ij_save;
      }

      else if (moves.size() == 1) { // dead end case...

        auto tmp = back_track_and_mark_dead_end_nodes( soln_nodes , path );

        if (tmp == no_soln) {
          cout << "no soln found" << endl;
          break;
        }

        dead_end_IJ.insert(dead_end_IJ.end(), tmp.begin(), tmp.end());

        last_ij = {soln_nodes[soln_nodes.size() - 1].get_i(),
                   soln_nodes[soln_nodes.size() - 1].get_j()};
        ij = soln_nodes[soln_nodes.size() - 1].calculate_valid_next_move(M);
      }

      else {

        cout << "error" << endl;
        break;
      }
    }
  }
}

void DepthFirstSearch::writeSolutionToCSV(const std::string &filename) const {
  
  path_.writeToCSV( filename );
  
  ofstream outfile( filename , std::ios_base::app);
  
  outfile << ij_f[0] << "," << ij_f[1];
  
  outfile.close();
  
}
