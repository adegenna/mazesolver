#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>
#include <Eigen/Dense>

class Node;

std::tuple< std::vector<Node> , std::vector<std::vector<std::vector<int>>> > depth_first_solve(
			const Eigen::MatrixXi& M ,
			const std::vector<int>& ij_0 ,
			const std::vector<int>& ij_f );

void back_track( std::vector<Node>& stack_nodes ,
		 std::vector<std::vector<std::vector<int>>>& list_IJ );



#endif
