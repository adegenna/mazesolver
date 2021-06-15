#ifndef __EXAMPLE_MAZE_H__
#define __EXAMPLE_MAZE_H__

#include <Eigen/Dense>

Eigen::MatrixXi make_maze_32x32( );

// implement this function
Eigen::MatrixXi translate_maze_to_adjacency_matrix(const Eigen::MatrixXi& maze);

#endif
