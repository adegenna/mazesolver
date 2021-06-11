#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <Eigen/Dense>

std::vector< std::vector<int> > find_possible_moves( const int i ,
						     const int j ,
						     const Eigen::MatrixXi& M );

std::vector< std::vector<int> > find_exit_points_of_maze( const Eigen::MatrixXi& M );

bool check_if_ij_is_maze_node( const Eigen::MatrixXi& M ,
			       const int i , const int j ,
			       const std::vector<int> last_ij );


#endif
