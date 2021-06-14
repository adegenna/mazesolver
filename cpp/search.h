#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>
#include <Eigen/Dense>

class Node;

void depth_first_solve( const Eigen::MatrixXi& M ,
			const std::vector<int> ij_0 ,
			const std::vector<int> ij_f ,
			std::vector<Node>& soln_nodes ,
			std::vector<std::vector<std::vector<int>>>& soln_IJ );



#endif
